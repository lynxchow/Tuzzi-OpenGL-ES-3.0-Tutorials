#! /bin/bash
if [ ! -d "tuzzi/build/iOS" ]; then
    mkdir -p tuzzi/build/iOS
fi
cd tuzzi/build/iOS
cmake ../../ -G "Xcode" -DTarget=iOS
cd ../../../
