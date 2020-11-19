#! /bin/bash
if [ ! -d "build/iOS" ]; then
    mkdir -p build/iOS
fi
cd build/iOS
cmake ../../ -G "Xcode" -DTarget=iOS
cd ../../
