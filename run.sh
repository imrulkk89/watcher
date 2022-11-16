#!/bin/bash

# change directory to the directory of this script
cd "$(dirname "$0")"

# create a new directory "build" if it does not exist
mkdir -p build

# change directory to the "build" directory
cd build

# run cmake
cmake ..

# run make
make

# run the executable
./main
