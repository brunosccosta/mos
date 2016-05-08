#!/bin/bash

# Building the libk
cd libc
make
mv libk.a ..
cd -

# Building the kernel
cd kernel
make
cd -

# Building the CDRom
mkdir -p isodir/boot/grub
cp kernel/mos.bin isodir/boot/mos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub2-mkrescue -o mos.iso isodir

