# Dependencies

## CMake

CMake bundled with Ubuntu 16.04 LTS is quite old (3.5.X). To get all new (nice) features from 3.8+, do :

    sudo apt-get purge cmake
    cd YOUR_DOWNLOAD_DIR/
    wget https://cmake.org/files/v3.9/cmake-3.9.4.tar.gz
    tar -xzvf cmake-3.9.4.tar.gz
    cd cmake-3.9.4/
    ./bootstrap
    make -j4
    sudo make install

To check CMake is correctly installed and where it is located :

    cmake --version
    which cmake
    
Ubuntu 17.10 already has CMake 3.9.1, so Ubuntu 18.04 LTS should be fine too (TODO check in April 2018) :

    sudo apt-get install cmake cmake-curses-gui

## Boost

To install boost under Ubuntu 16.04 LTS, simply

    sudo apt update
    sudo apt-get install libboost-program-options-dev
    
This will only install boost "program_options" submodule. To install everything from boost :

    sudo apt-get install libboost-all-dev
    
Ubuntu 16.04 LTS comes with boost 1.58 libs

# Compile

    cd YOUR_WORKSPACE/
    git clone THIS_GIT_URL
    cd heiafr-baby-bird-problem
    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make -j4
    ./kekekbri --chicks 7 --iters 53 --parents 3 --portion 5 --hunting 30
    
To use in Debug mode (breakpoints, retain symbol names, no code optimizations, debug console prints...), use instead :

    cd build
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    make -j4