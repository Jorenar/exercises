#!/usr/bin/env python
# -*- coding: UTF-8 -*-

import sys

mem = [ 0, 1 ]

def fib(n):
    if n < len(mem):
        return mem[n]
    mem.append(fib(n-1) + fib(n-2))
    return mem[n]

print(fib(int(sys.argv[1])))
