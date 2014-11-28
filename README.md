cpp-starter-kit
===============

Starter kit for Monkey Music Challenge 2

OS X
====
    brew install openssl boost

Debian/Ubuntu Linux
===================
    sudo apt-get install libssl-dev libboost-dev

Building
========
    git submodule update --init --recursive
    mkdir build
    cd build
    cmake ..
    make monkeymusic

If cmake complains about OpenSSL on OS X, try this:
    brew link openssl --force

Building with ninja for maximum awesomeness
===========================================
    brew install ninja
or
    sudo apt-get install ninja-build
then
    cmake -GNinja ..
    ninja monkeymusic

Running
=======
    ./build/monkeymusic <your-team-name> <your-api-key>

Debugging
=========
You might want to run cmake with
    -DCMAKE_BUILD_TYPE=Debug
or
    -DCMAKE_BUILD_TYPE=RelWithDebInfo