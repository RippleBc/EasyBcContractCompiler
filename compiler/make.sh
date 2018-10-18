#!/bin/bash
as --gstabs -o $1.o $1.s
as --gstabs -o x86rtllinux.o ../x86rtllinux.asm
ld -o $1 $1.o x86rtllinux.o
