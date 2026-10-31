@echo off

cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_RC_COMPILER="C:/msys64/mingw64/bin/windres.exe"
if errorlevel 1 exit /b 1

cmake --build build --parallel
if errorlevel 1 exit /b 1

echo Build successful!