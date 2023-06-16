Topological sort
================

Topological sort of acyclic directed graph is a linear ordering of its vertices
such that for every directed edge _(u,v)_ vertex _u_ comes before _v_ in the ordering.

The implementation below assumes graph to be acyclic.
If we don't have such guarantee, we need to color use version of DFS
with white/grey/black coloring and throw error when encountering
vertex being processed (i.e. colored grey) in DFS_visit()

----

G := {Graph}
i := |G.V|
R := []
visited := []

DFS_visit(s):
    visited[s] := TRUE
    for v in G.V:
        if ((s,v) in G.E) and (not visited[v]):
            DFS_visit(v)
    R[i] := v
    i := i - 1

topological_sort():
    for v in G.V:
        if not visited[v]:
            DFS_visit(v)
