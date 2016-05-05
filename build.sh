#!/bin/bash

# Building the libk
cd libc
make
mv libk.a ..
cd -

# Building the kernel
cd kernel
make
mv mos.kernel ..
cd -

