To check whether graph has cycles we need to execute DFS algorithm with
additional array tracking whether the vertex was already finished processing.

If in `visit()` during iteration over vertexes we encounter one which has
already been visited, but not marked as finished, then graph has cycles.

-----

visited := []
finished := []

visit(G, s):
    visited[s] = TRUE

    for v in G.V:
        if not ((s,v) in G.E):
            continue
        if visited[v]
            if not finished[v]:
                return TRUE
            else:
                continue
        if visit(G, v):
            return TRUE

    finished[s] := TRUE
    return FALSE

hasCycles(G):
    for v in G.V:
        if not visited[v]:
            if visit(G, v):
                return TRUE
    return FALSE
