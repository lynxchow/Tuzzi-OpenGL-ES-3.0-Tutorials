#! /bin/bash
if [ ! -d "tuzzi/build/macOS" ]; then
    mkdir -p tuzzi/build/macOS
fi
cd tuzzi/build/macOS
cmake ../../ -G "Xcode" -DTarget=macOS
cd ../../../
