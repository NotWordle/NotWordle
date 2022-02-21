#!/bin/bash

# create build directory for generated cmake files
mkdir -p build/
cd build/

# configure cmake
cmake ..

# build executable
make -j 5