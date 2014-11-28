# C++ starter kit

<img src="http://monkeymusicchallenge.com/images/monkey.png" align="right">

### Prerequisites

First of all, go to http://monkeymusicchallenge.com, sign up and get your API key.

For this starter kit, you will need basic knowledge of:

* [C++](http://cppreference.com/)

### Getting started

Start by [forking](https://github.com/parbo/cpp-starter-kit/fork)
this repository to your own GitHub user.

#### Installing dependencies
##### OS X
    brew install openssl boost

##### Debian/Ubuntu Linux
    sudo apt-get install libssl-dev libboost-dev

#### C++ REST SDK
This starter kit uses the [Casablanca C++ REST SDK](https://casablanca.codeplex.com/), which is a cross platform HTTP library by Microsoft that uses modern C++ features. It also uses pplx for concurrency, which might come in handy in general for this challenge.. :)

#### Building
    git clone git@github.com:<username>/cpp-starter-kit.git
    cd cpp-starter-kit
    git submodule update --init --recursive
    mkdir build
    cd build
    cmake ..
    make monkeymusic

If cmake complains about OpenSSL on OS X, try this:

    brew link openssl --force

#### Building with ninja for maximum awesomeness
    brew install ninja

or

    sudo apt-get install ninja-build

then

    cmake -GNinja ..
    ninja monkeymusic

#### Debugging
You might want to run cmake with

    -DCMAKE_BUILD_TYPE=Debug

or

    -DCMAKE_BUILD_TYPE=RelWithDebInfo

#### What to do
`main.cpp` contains the boilerplate needed to communicate with the server. You should not need to change anything in here unless we have done something wrong.

We suggest you go straight to `ai.cpp` and start playing around with the code.

#### Running
From inside the build folder:

    ./monkeymusic <your-team-name> <your-api-key> <game-id>

Game ids are acquired through each of the different game pages. Log in to Monkey Music through your browser to get started!

Make sure to surf to your team page before running the above commands...

Your monkey is waiting for you!

### Bugs

When you find bugs in our code, please submit an issue or pull request to our [original starter kit repository](https://github.com/parbo/cpp-starter-kit).
