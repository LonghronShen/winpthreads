#!/bin/bash

set -x

apt update

apt install -y gcc-mingw-w64-x86-64 \
    g++-mingw-w64-x86-64 \
    binutils-mingw-w64-x86-64 \
    mingw-w64-x86-64-dev \
    gcc-mingw-w64-i686 \
    g++-mingw-w64-i686 \
    binutils-mingw-w64-i686 \
    mingw-w64-i686-dev \
    python3-pip

pip3 install cmake