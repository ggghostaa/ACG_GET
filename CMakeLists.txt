#cmake version
cmake_minimum_required(VERSION 3.30)
project(ACG_GET)
#c++ VERSION
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#source code and tests dir
add_subdirectory(src)
add_subdirectory(tests)

#third_party lib
add_subdirectory(third_party/googletest)

