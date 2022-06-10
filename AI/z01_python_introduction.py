#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Tasks: https://is.gd/S6rhii

import math
import numpy as np
from random import randint


def ex1():
    print("-" * 30 + " Zadanie 1 " + "-" * 30)
    s1 = map(int, input("'x y' of 1st circle:  ").split())
    r1 = int(input("Radius of 1st curcle: "))
    s2 = map(int, input("'x y' of 2st circle:  ").split())
    r2 = int(input("Radius of 2st curcle: "))
    S = math.dist(s1, s2)
    print((r1 - r2) < S and S < (r1 + r2))


def ex2():
    while (True):
        foo = input()
        if foo == "stop":
            break
        print(foo)


def ex3():
    n, m = [int(v) for v in input("Dimensions: ").split()]
    for i in range(0, n):
        for j in range(0, m):
            print((i + j) % 2, end="")
        print()


def ex4():
    l = input("Length: ")
    b = "|---" + "-" * (len(l) - 3)
    l = int(l)
    print(b * l + "|\n0", end='')
    fmt = "{:>" + str(len(b)) + "}"
    print((fmt * l).format(*range(1, l + 1)))


def ex5():
    def func(l):
        return np.sum(l), l[0] - np.sum(l[1:]), np.prod(l)

    # x, y, z = func([ 6, 1, 1, 1, 1, 1 ])
    # print(f"Sum:  {x}")
    # print(f"Diff: {y}")
    # print(f"Prod: {z}")


def ex6():
    txt = input("Input: ")
    txt = " ".join(txt) + " "
    print("Output: " + txt)


def ex7():
    def reverse(s):
        return s[::-1]

    print(reverse("hello"))


def ex8():
    S = 2000000
    r = 700
    r2 = r**2

    rand = lambda: randint(-r, r)

    pts = 0
    for _ in range(S):
        x, y = rand(), rand()
        if x**2 + y**2 <= r2:
            pts += 1

    print("π ≈", 4 * pts / S)
