#include <binarization_basic.hpp>
#include <kittler.hpp>
#include <omp_config.hpp>

#include <omp.h>

#include <cmath>
#include <cstdint>
#include <limits>

static double get_other_variance(double mass_0, double mass_1, double expect_0,
                                 double expect_1, double variance_0,
                                 double variance_total) {
  double tmp = expect_0 - expect_1;
  double variance_between = mass_0 * mass_1 * tmp * tmp;
  double variance_within = variance_total - variance_between;

  return (variance_within - mass_0 * variance_0) / mass_1;
}

static unsigned char get_threshold(const std::vector<unsigned char> &pixels,
                                  std::vector<double> &hist) {
  unsigned char threshold = 0;
  std::size_t n = pixels.size();
  constexpr int64_t N_COLORS = 256;

  double expect_total = 0;
  for (std::size_t i = 0; i < N_COLORS; ++i) {
    hist[i] /= n;
    expect_total += (i + 1) * hist[i];
  }

  double variance_total = 0;
  for (std::size_t i = 0; i < N_COLORS; ++i) {
    double tmp = (i + 1) - expect_total;
    variance_total += tmp * tmp * hist[i];
  }

  struct {
    double goodness;
    unsigned char threshold;
    char padding[128];
  } best[OMP_MAX_THREADS];

#pragma omp parallel shared(best, threshold)
  {
    int id = omp_get_thread_num();
    best[id].threshold = 0;
    best[id].goodness = std::numeric_limits<double>::max();

#pragma omp for schedule(guided)
    for (int k = 0; k < N_COLORS - 1; ++k) {
      int begin = 0;
      int end = k + 1;
      if (k > N_COLORS / 2) {
        begin = k + 1;
        end = N_COLORS;
      }

      double mass_0 = 0;
      double expect_0 = 0;
      for (int i = begin; i < end; ++i) {
        mass_0 += hist[i];
        expect_0 += (i + 1) * hist[i];
      }

      double variance_0 = 0;
      for (int i = begin; i < end; ++i) {
        double tmp = (i + 1) - expect_0;
        variance_0 += tmp * tmp * hist[i];
      }

      double mass_1 = 1 - mass_0;
      double expect_1 = (expect_total - expect_0) / mass_1;
      expect_0 /= mass_0;
      variance_0 /= mass_0;
      double variance_1 = get_other_variance(mass_0, mass_1, expect_0, expect_1,
                                             variance_0, variance_total);

      double goodness_local = mass_0 * log(variance_0 / mass_0) * 0.5 +
                              mass_1 * log(variance_1 / mass_1) * 0.5;

      if (goodness_local < best[id].goodness) {
        best[id].goodness = goodness_local;
        best[id].threshold = k;
      }
    }

#pragma omp flush(best)
#pragma omp master
    {
      size_t n_threads = omp_get_num_threads();
      auto goodness = best[0].goodness;
      threshold = best[0].threshold;
      for (size_t thread = 1; thread < n_threads; ++thread) {
        if (best[thread].goodness < goodness) {
          goodness = best[thread].goodness;
          threshold = best[thread].threshold;
        }
      }
    }
  }

  return threshold;
}

unsigned char kittler_illingworth(std::vector<unsigned char> &pixels) {
  auto hist = make_histogram(pixels);

  auto threshold = get_threshold(pixels, hist);
  separate_by_threshold(pixels, [threshold](unsigned char color) {
    return color > threshold ? 255 : 0;
  });

  return threshold;
}
