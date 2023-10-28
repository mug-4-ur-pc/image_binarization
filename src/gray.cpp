#include <gray.hpp>

void make_gray(std::vector<unsigned char> &pixels, std::size_t n_channels) {
  std::size_t new_size = pixels.size() / n_channels;
  for (std::size_t i_mono = 0, i_color = 0; i_mono < new_size;
       ++i_mono, i_color += n_channels) {
    unsigned int brightness = 0;
    for (std::size_t channel = 0; channel < n_channels; ++channel) {
      brightness += pixels[i_color + channel];
    }

    pixels[i_mono] = brightness / 3;
  }

  pixels.resize(new_size);
}
