@echo off
setlocal

set "PATH=C:\msys64\ucrt64\bin;%PATH%"

cmake -S . -B build-ucrt64 -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ^
    -DCMAKE_PREFIX_PATH=C:/msys64/ucrt64 ^
    -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe ^
    -DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe ^
    -DCMAKE_RC_COMPILER=C:/msys64/ucrt64/bin/windres.exe ^
    -DCMAKE_MAKE_PROGRAM=C:/msys64/ucrt64/bin/mingw32-make.exe

if errorlevel 1 exit /b 1

cmake --build build-ucrt64 --parallel
if errorlevel 1 exit /b 1

echo Build successful!