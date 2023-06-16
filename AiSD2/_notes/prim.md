PRIM
----

1. Initialize a tree with a single vertex, chosen arbitrarily from the graph
2. Add to the tree edge _(u,v)_ which intersects the section _(Vᴀ, V-Vᴀ)_
3. Mark _u_ as parent of _v_
4. Repeat steps 2. and 3. until all vertices are in the tree
5. Return the tree (an array of parents)


Prim(G, s):
    p := []
    Q := {PriorityQueue}

    for v in G.V:
        p[v] := NIL
        enqueue(Q, INF)

    decreaseKey(Q, s, 0)

    while not empty(Q):
        v := extractMin(Q)

        for u in G.V:
            if (v,u) in G.E:
                if conatins(Q, u) and w(v,u) < key(Q,u):
                    p[u] = v
                    decreaseKey(Q, u, w(v,u))

    return p
