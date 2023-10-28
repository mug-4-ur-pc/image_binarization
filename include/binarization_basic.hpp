#pragma once

#include <cstdint>
#include <vector>

std::vector<double> make_histogram(const std::vector<unsigned char> &pixels);

template <typename Separator>
void separate_by_threshold(std::vector<unsigned char> &pixels, Separator &&sep) {
  int64_t n = pixels.size();

#pragma omp for schedule(guided)
  for (int i = 0; i < n; ++i) {
    pixels[i] = sep(pixels[i]);
  }
}
