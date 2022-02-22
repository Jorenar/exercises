#!/usr/bin/env python3
# -*- coding: UTF-8 -*-


class Graph:
    def __init__(self, *args):
        self.E = [edge for edge in args]
        self.V = set([u[0] for u in args] + [v[1] for v in args])


class UnionFind:
    def __init__(self, G):
        self.rank = [0]
        self.parent = [0]

        for node in G.V:
            self.parent.append(node)
            self.rank.append(0)

    def find(self, v):
        return self.parent[v]

    def union(self, u, v):
        u_root = self.find(u)
        v_root = self.find(v)
        if self.rank[u_root] < self.rank[v_root]:
            self.parent[u_root] = v_root
        elif self.rank[u_root] > self.rank[v_root]:
            self.parent[v_root] = u_root
        else:
            self.parent[v_root] = u_root
            self.rank[u_root] += 1


def kruskal(G):
    F = []  # forest

    uf = UnionFind(G)

    for u, v, weight in sorted(G.E, key=lambda item: item[2]):
        if uf.find(u) != uf.find(v):
            F.append([u, v, weight])
            uf.union(u, v)

    return F


def printMST(G):
    for u, v, weight in kruskal(G):
        print("({:>2}, {:>2}); {}".format(u, v, weight))


g = Graph([1, 2, 6], [1, 3, 6], [1, 7, 3],
        [2, 3, 5], [2, 4, 4], [2, 5, 4],
        [3, 5, 2], [3, 6, 3], [3, 7, 4],
        [4, 5, 3],
        [5, 6, 3], [5, 9, 2],
        [6, 7, 4], [6, 12, 1],
        [7, 8, 3],
        [8, 10, 7],
        [9, 12, 2],
        [10, 11, 4],
        [11, 12, 3])

printMST(g)
