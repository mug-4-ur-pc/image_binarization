# image_binarization
This repo contains three simple image binarization algorithms:
- [Otsu method](src/otsu.cpp)
- [Unbalanced Otsu method](src/unbalanced_otsu.cpp)
- [Kittler-Illingworth method](kittler.cpp)

# Requirements
- OpenMP
- Magick++

# Build
``` sh
mkdir build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

# Run
To run program you must give 3 arguments:
1) threshold finding algorithm (otsu, unbalanced_otsu, kittler)
2) input image file name
3) output image file name

# Examples
The pictures were taken from [here](http://vc.ee.duth.gr/h-dibco2018/benchmark/dibco2018_Dataset.zip).

Picture are shown in next order:
1) original
2) Otsu
3) unbalanced Otsu
4) Kittler-Illingworth

## Image 1
![Image 1](img/1.bmp)
![Image 1](img/otsu_1.bmp)
![Image 1](img/unbalanced_otsu_1.bmp)
![Image 1](img/kittler_1.bmp)

## Image 2
![Image 2](img/2.bmp)
![Image 2](img/otsu_2.bmp)
![Image 2](img/unbalanced_otsu_2.bmp)
![Image 2](img/kittler_2.bmp)

## Image 3
![Image 3](img/3.bmp)
![Image 3](img/otsu_3.bmp)
![Image 3](img/unbalanced_otsu_3.bmp)
![Image 3](img/kittler_3.bmp)

## Image 4
![Image 4](img/4.bmp)
![Image 4](img/otsu_4.bmp)
![Image 4](img/unbalanced_otsu_4.bmp)
![Image 4](img/kittler_4.bmp)

## Image 5
![Image 5](img/5.bmp)
![Image 5](img/otsu_5.bmp)
![Image 5](img/unbalanced_otsu_5.bmp)
![Image 5](img/kittler_5.bmp)

## Image 6
![Image 6](img/2.bmp)
![Image 6](img/otsu_2.bmp)
![Image 6](img/unbalanced_otsu_2.bmp)
![Image 6](img/kittler_2.bmp)

## Image 7
![Image 7](img/7.bmp)
![Image 7](img/otsu_7.bmp)
![Image 7](img/unbalanced_otsu_7.bmp)
![Image 7](img/kittler_7.bmp)

## Image 8
![Image 8](img/8.bmp)
![Image 8](img/otsu_8.bmp)
![Image 8](img/unbalanced_otsu_8.bmp)
![Image 8](img/kittler_8.bmp)

## Image 9
![Image 9](img/2.bmp)
![Image 9](img/otsu_2.bmp)
![Image 9](img/unbalanced_otsu_2.bmp)
![Image 9](img/kittler_2.bmp)

## Image 10
![Image 10](img/10.bmp)
![Image 10](img/otsu_10.bmp)
![Image 10](img/unbalanced_otsu_10.bmp)
![Image 10](img/kittler_10.bmp)
