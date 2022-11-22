:: change path to the directory where the script is located
cd %~dp0

:: create a "build" directory if it doesn't exist
if not exist build mkdir build

:: change path to the "build" directory
cd build

:: run cmake
cmake -G "MinGW Makefiles" ..

:: run make
mingw32-make

:: run the executable
./main