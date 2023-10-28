#include <binarization_basic.hpp>

std::vector<double> make_histogram(const std::vector<unsigned char> &pixels) {
  std::size_t n = pixels.size();

  auto result = std::vector<double>(n, 0);
#pragma omp for schedule(static)
  for (std::size_t i = 0; i < n; ++i) {
    result[pixels[i]] += 1;
  }

  return result;
}
