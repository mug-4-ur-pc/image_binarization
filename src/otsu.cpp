#include <binarization_basic.hpp>
#include <otsu.hpp>

#include <cmath>

unsigned char otsu(std::vector<unsigned char> &pixels) {
  unsigned char threshold = 0;
  std::size_t n = pixels.size();
  constexpr int64_t N_COLORS = 256;

  auto hist = make_histogram(pixels);

  double weighted_sum_total = 0;
  for (std::size_t i = 0; i < N_COLORS; ++i) {
    weighted_sum_total += (i + 1) * hist[i];
  }

  double mass_0 = 0;
  double weighted_sum_0 = 0;
  double variance_between = -1;

  for (std::size_t i = 0; i < N_COLORS; ++i) {
    mass_0 += hist[i];
    double mass_1 = n - mass_0;
    if (mass_0 <= 0 || mass_1 <= 0) {
      continue;
    }

    weighted_sum_0 += (i + 1) * hist[i];
    double expect_0 = weighted_sum_0 / mass_0;
    double expect_1 = (weighted_sum_total - weighted_sum_0) / mass_1;

    double tmp = expect_0 - expect_1;
    double variance_between_local = mass_0 * mass_1 * tmp * tmp;

    if (variance_between < variance_between_local) {
      variance_between = variance_between_local;
      threshold = i;
    }
  }

  separate_by_threshold(pixels, [threshold](unsigned char color) {
    return color > threshold ? 255 : 0;
  });

  return threshold;
}
