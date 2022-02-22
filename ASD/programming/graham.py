#!/usr/bin/env python
# -*- coding: UTF-8 -*-

from functools import cmp_to_key

INF = float("inf")


def alfa(p):
    x = p[0]
    y = p[1]

    if x == y == 0:
        return -INF

    d = abs(x) + abs(y)

    if x >= 0 and y >= 0:
        return y/d
    if x <= 0 and y >= 0:
        return 2 - y/d
    if x <= 0 and y <= 0:
        return 2 + abs(y) / d
    if x >= 0 and y < 0:
        return 4 - abs(y) / d


def cmp(A, B):
    a = alfa(A)
    b = alfa(B)
    return (a - b) if (a != b) else (A[0]**2 + A[1]**2) - (B[0]**2 + B[1]**2)


def det(A, B, C):
    xA, xB, xC = A[0], B[0], C[0]
    yA, yB, yC = A[1], B[1], C[1]
    return xA*yB + yA*xC + xB*yC - yB*xC - yC*xA - yA*xB


def graham(points):
    S = (INF, INF)

    for p in points:
        if p[1] < S[1] or (p[1] == S[1] and p[0] < S[0]):
            S = p

    hull = []
    for p in points:
        hull.append((p[0] - S[0], p[1] - S[1]))
    hull.sort(key=cmp_to_key(cmp))

    i = 1
    while i < len(hull)-1:
        A = hull[i-1]
        B = hull[i]
        C = hull[i+1]
        if det(A, B, C) < 0:
            hull.pop(i)
            i -= 1
        else:
            i += 1

    for i in range(0, len(hull)):
        p = hull[i]
        hull[i] = ((p[0] + S[0], p[1] + S[1]))

    return hull


print(graham([(3, 2), (2, 5), (5, 6), (4, 4), (6, 4)]))

print(graham([(0, 0), (10, 3), (11, 8), (2, 11), (1, 8), (8, 5), (9, 13),
              (-2, 15), (5, 14), (-8, 6), (8, 10), (-1, 10), (-4, 9)]))
