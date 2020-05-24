#!/bin/bash

set -e

export PREFIX=/opt/gcc-cross
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

export DISPLAY=:0