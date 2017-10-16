cmake_minimum_required(VERSION 3.8) # ask for cmake >= 3.8
project(kekekbri CXX) # project is c++ based

set (CMAKE_CXX_STANDARD 14) # aim for c++14
if(CMAKE_COMPILER_IS_GNUCXX) # if gcc (not visual c++)
    add_compile_options( -pedantic -Wall -Wextra)
    set (CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
    set (CMAKE_CXX_FLAGS_RELEASE "-O2")
endif()

set(SRCS src/main.cpp)
set(HDRS )

add_executable(kekekbri ${SRCS} ${HDRS})