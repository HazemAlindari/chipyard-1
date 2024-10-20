#!/bin/bash

# Define the build directory
BUILD_DIR=./build

# Create the build directory if it doesn't exist
mkdir -p $BUILD_DIR

# Run CMake to configure the project
cmake -S ./ -B $BUILD_DIR -D CMAKE_BUILD_TYPE=Debug

# Build the specific testSHA3 targets
cmake --build $BUILD_DIR --target testSHA3High32Bit
cmake --build $BUILD_DIR --target testSHA3High64Bit
cmake --build $BUILD_DIR --target testSHA3Low32Bit
cmake --build $BUILD_DIR --target testSHA3Low64Bit
