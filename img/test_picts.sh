#!/bin/bash

rm otsu_* unbalanced_otsu_* kittler_* || true

for file in $(ls *.bmp); do
    ../build/play/binarize otsu $file otsu_$file
    ../build/play/binarize unbalanced_otsu $file unbalanced_otsu_$file
    ../build/play/binarize kittler $file kittler_$file
done

echo
echo
echo "Generation finished!!!"
echo
