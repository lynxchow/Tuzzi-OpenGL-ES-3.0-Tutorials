#! /bin/bash
if [ ! -d "build/macOS" ]; then
    mkdir -p build/macOS
fi
cd build/macOS
cmake ../../ -G "Xcode" -DTarget=macOS
cd ../../
