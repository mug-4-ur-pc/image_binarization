#include <gray.hpp>
#include <kittler.hpp>
#include <omp_config.hpp>
#include <otsu.hpp>
#include <unbalanced_otsu.hpp>

#include <OpenImageIO/imageio.h>
#include <omp.h>

#include <exception>
#include <iostream>
#include <string_view>

template <typename F> void benchmark(F &&fun) {
  double start = omp_get_wtime();
  fun();
  double stop = omp_get_wtime();
  std::cout << "Elapsed time: " << stop - start << std::endl;
}

bool binarize(std::string_view algorithm, std::vector<unsigned char> &pixels,
              std::size_t height, std::size_t width) {
  (void)height;
  (void)width;

  if (algorithm == "otsu") {
    benchmark([&]() { otsu(pixels); });
  } else if (algorithm == "unbalanced_otsu") {
    benchmark([&]() { unbalanced_otsu(pixels); });
  } else if (algorithm == "kittler") {
    benchmark([&]() { kittler_illingworth(pixels); });
  } else {
    std::cout << "Unknown algorithm" << std::endl;
    std::cout << "Available algorithms: otsu, unbalanced_otsu" << std::endl;
    return false;
  }

  return true;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cout << "Usage: " << argv[0] << " <algorithm> <input> <output>";
    std::cout << std::endl;
    return 1;
  }

  omp_set_num_threads(OMP_MAX_THREADS);
  
  const char *in_fname = argv[2];
  const char *out_fname = argv[3];

  auto in = OIIO::ImageInput::open(in_fname);
  if (!in) {
    std::cout << "Couldn't read image" << std::endl;
    return 1;
  }

  const OIIO::ImageSpec &spec = in->spec();
  std::size_t width = spec.width;
  std::size_t height = spec.height;
  std::size_t n_channels = spec.nchannels;
  auto pixels = std::vector<unsigned char>(width * height * n_channels);
  in->read_image(0, 0, 0, n_channels, OIIO::TypeDesc::UINT8, pixels.data());
  in->close();

  make_gray(pixels, n_channels);
  if (!binarize(argv[1], pixels, height, width)) {
    return 1;
  }

  auto out = OIIO::ImageOutput::create(out_fname);
  if (!out) {
    std::cout << "Couldn't write image" << std::endl;
    return 1;
  }

  OIIO::ImageSpec out_spec(width, height, 1, OIIO::TypeDesc::UINT8);
  out->open(out_fname, out_spec);
  out->write_image(OIIO::TypeDesc::UINT8, pixels.data());
  out->close();

  return 0;
}
