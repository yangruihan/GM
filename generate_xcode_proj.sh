#!/usr/bin/env bash

if [ ! -d "build/MacOS" ]; then
    mkdir -p build/MacOS
fi

cd build/MacOS && cmake -G Xcode ../../