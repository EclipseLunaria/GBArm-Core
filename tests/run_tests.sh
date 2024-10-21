#!/bin/bash

rm -r build
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..


make
./run_tests

cd ..
