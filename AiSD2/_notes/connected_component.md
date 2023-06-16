GRAPH COMPONENT
---------------

To compute components of non-directed graph, we just need to "color" differently
every non-recursive call to DFS_visit()

visited := []
colors := []

DFS_visit(G, s, k):
    visited[s] := TRUE
    colors[s] := k

    for v in G.V:
        if ((s,v) in G.E) and (not visited[v]):
            DFS_visit(G, v, k)

components(G):
    k := 0
    for v in G.V:
        k := k + 1
        DFS_visit(G, v, k)


If graph is directed, we need to use Kosaraju's algorithm:

visited := []
colors := []
S := {Stack}

DFS_visit(G, s):
    visited[s] := TRUE
    for v in G.V:
        if ((s,v) in G.E) and (not visited[v]):
            DFS_visit(G, v)
    push(S, s)

DFS_visit(T, s, k):
    colors[s] := k
    for v in T.V:
        if ((s,v) in T.E) and (not colors[v]):
            DFS_visit(T, v, k)

Kosaraju(G):
    for v in G.V:
        if not visited[v]:
            DFS_visit(G, v)

    T := transpose(G)

    k := 1
    while not empty(S):
        v := pop(S)
        if not colors[v]:
            DFS_visit(T, v, k)
            k := k + 1
