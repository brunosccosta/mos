#!/bin/bash

set -e

PREFIX=/opt/gcc-cross
SRC_DIR="$PREFIX/src"

BINUTILS_VER="binutils-2.34"
BINUTILS_TAR="$BINUTILS_VER.tar.gz"
BINUTILS_URL="https://ftp.gnu.org/gnu/binutils/$BINUTILS_TAR"

GCC_VER="gcc-10.1.0"
GCC_TAR="$GCC_VER.tar.gz"
GCC_URL="https://ftp.gnu.org/gnu/gcc/gcc-10.1.0/$GCC_TAR"

GDB_VER="gdb-9.2"
GDB_TAR="$GDB_VER.tar.gz"
GDB_URL="http://ftp.gnu.org/gnu/gdb/$GDB_TAR"

TARGET=i686-elf

# Adding to PATH
export PATH="$PREFIX/bin:$PATH"

function binutils {
    wget -nc -P $SRC_DIR $BINUTILS_URL

    # Building binutils
    cd $SRC_DIR

    tar xvzf $BINUTILS_TAR

    mkdir -p build-binutils
    cd build-binutils
    ../$BINUTILS_VER/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
    make
    make install
}

function gcc {
    wget -nc -P $SRC_DIR $GCC_URL

    # Building gcc
    cd $SRC_DIR

    # The $PREFIX/bin dir _must_ be in the PATH. We did that above.
    which -- $TARGET-as || (echo "$TARGET-as is not in the PATH" && exit 1)

    tar xvzf $GCC_TAR

    mkdir -p build-gcc
    cd build-gcc
    ../$GCC_VER/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
    make all-gcc
    make all-target-libgcc
    make install-gcc
    make install-target-libgcc
}

function gdb {
    wget -nc -P $SRC_DIR $GDB_URL
    
    # Building GDB
    cd $SRC_DIR

    tar xvzf $GDB_TAR
    mkdir -p build-gdb
    cd build-gdb
    ../$GDB_VER/configure --target="$TARGET" --prefix="$PREFIX" --program-prefix="$TARGET-"
    make
    make install
}

# Creating directory structure to build binutils/gcc
mkdir -p $PREFIX
mkdir -p $SRC_DIR
mkdir -p "$PREIX/bin"

# Installing gcc cross compiler dependencies
apt-get install -y build-essential \
                   bison           \
                   flex            \
                   libgmp3-dev     \
                   libmpc-dev      \
                   libmpfr-dev     \
                   texinfo         \
                   grub-pc-bin     \
                   xorriso

binutils
gcc
gdb