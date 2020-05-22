#!/bin/bash

set -e

BASE_DIR=/opt/gcc-cross
DOWNLOAD_DIR="$BASE_DIR/source"

BINUTILS_URL="https://ftp.gnu.org/gnu/binutils/binutils-2.34.tar.gz"
GCC_URL="https://ftp.gnu.org/gnu/gcc/gcc-10.1.0/gcc-10.1.0.tar.gz"

# Creating directory structure to build binutils/gcc
mkdir -p $BASE_DIR
mkdir -p $DOWNLOAD_DIR

# Installing gcc cross compiler dependencies
apt-get install -y build-essential \
                   bison           \
                   flex            \
                   libgmp3-dev     \
                   libmpc-dev      \
                   libmpfr-dev     \
                   texinfo         

# Downloading all the needed source
wget -P $DOWNLOAD_DIR $BINUTILS_URL
wget -P $DOWNLOAD_DIR $GCC_URL

