#!/usr/bin/env bash

if [ ! -d "build/CMake/Debug" ]; then
    mkdir -p build/CMake/Debug
fi

cd build/CMake/Debug && cmake -DCMAKE_BUILD_TYPE=Debug -DDEBUG=ON ../../../ && make