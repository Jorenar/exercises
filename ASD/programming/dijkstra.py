#!/usr/bin/env python
# -*- coding: UTF-8 -*-

from math import inf


def Dijkstra(G, s):
    n = len(G)

    Q = list(range(0, n))

    p = [-1] * n
    d = [inf] * n
    d[s] = 0

    while Q:
        temp = min([d[q] for q in Q])
        indices = [x for x in range(0, len(d)) if d[x] == temp]
        for i in indices:
            Q.remove(i)
            neighbours = [x for x in range(0, len(G[i]))
                          if x != s and G[i][x] < inf]
            for j in neighbours:
                if j < inf and d[j] > d[i] + G[i][j]:
                    d[j] = d[i] + G[i][j]
                    p[j] = i

    print(d)
    print(p)


graph = [
    [0,   3,   inf, inf, 3,   inf],
    [inf, 0,   1,   inf, inf, inf],
    [inf, inf, 0,   3,   inf, 1],
    [inf, 3,   inf, 0,   inf, inf],
    [inf, inf, inf, inf, 0,   2],
    [6,   inf, inf, 1,   inf, 0],
]

# graph = [
#     [0,   2,   inf, 4,   inf],
#     [inf, inf, 3,   3,   inf],
#     [inf, inf, inf, inf, 2],
#     [inf, inf, 3,   inf, 4],
#     [inf, inf, inf, inf, 0],
# ]


Dijkstra(graph, 0)
