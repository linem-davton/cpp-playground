#!/bin/bash
set -e

# ----- Update and Upgrade -----
sudo apt update -y 

#-- wget to download files
sudo apt install wget -y

# --- Install gcc, g++, make, dpkg-dev, libc6-dev, binutils--
sudo apt install build-essential -y

# --- Install strace ---
sudo apt install strace -y

# ----- CMake 3.30.2 -----
wget https://github.com/Kitware/CMake/releases/download/v3.30.2/cmake-3.30.2-linux-x86_64.sh
sudo sh cmake-3.30.2-linux-x86_64.sh --prefix=/usr/local --skip-license
rm cmake-3.30.2-linux-x86_64.sh

# ----- Ninja 1.10.0 -----
sudo apt install ninja-build -y

# ---- Install lcov ----
sudo apt install lcov -y

# --- Install heaptrack
sudo apt install heaptrack -y

# ---- Install perf ---- Fails on WSL
sudo apt install linux-tools-common linux-tools-generic linux-tools-$(uname -r) -y

