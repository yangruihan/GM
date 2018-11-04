#!/usr/bin/env bash

if [ ! -d "build/CMake/Release" ]; then
    mkdir -p build/CMake/Release
fi

cd build/CMake/Release && cmake -DCMAKE_BUILD_TYPE=Release -DDEBUG=OFF ../../../ && make