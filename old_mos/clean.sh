#!/bin/bash

rm -rf libk.a mos.iso isodir

# Cleaning the libk
cd libc
make clean
cd -

# Cleaning the kernel
cd kernel
make clean
cd -
