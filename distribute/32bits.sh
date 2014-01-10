#!/bin/bash
gcc -m32 -Wall -ggdb -o distribute_32bits *.c split_file/*.c -lpthread
scp -P22222 distribute_32bits root@158.108.181.74:/koppae
rm distribute_32bits
