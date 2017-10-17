cmake_minimum_required(VERSION 3.8) # ask for cmake >= 3.8
project(kekekbri CXX) # project is c++ based

# boost submodule "program_options" is required by our program
find_package(Boost COMPONENTS program_options REQUIRED)

# find thread library (used for std::thread)
# CMake knowns already how to find it (at least in Linux)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 14) # aim for c++14
if (CMAKE_COMPILER_IS_GNUCXX) # if gcc (not visual c++)
  add_compile_options(-pedantic -Wall -Wextra)
  # add DEBUG symbol when in debug mode and no optimizations
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif ()

set(SRCS src/main.cpp src/Parent.cpp src/Chick.cpp src/Nest.cpp src/PrintThread.cpp)
set(HDRS include/Parent.h include/Chick.h include/Nest.h include/PrintThread.h)
set(kekekbri_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# allow headers in include/ to be included without the full path in src/
include_directories(${kekekbri_INCLUDE_DIR})
add_executable(kekekbri ${SRCS} ${HDRS})
# link our executable with thread library found by cmake
target_link_libraries(kekekbri ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(kekekbri ${Boost_LIBRARIES})