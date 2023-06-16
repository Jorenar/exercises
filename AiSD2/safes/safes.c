#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void dfs_visit(size_t v, size_t n, bool visited[n], bool graph[n][n])
{
    visited[v] = true;
    for (size_t w = 0; w < n; ++w) {
        if (graph[v][w] && !visited[w]) {
            dfs_visit(w, n, visited, graph);
        }
    }
}

int main(void)
{
    size_t n;
    scanf("%zu", &n);

    if (n == 0) {
        puts("0");
        return 0;
    }

    bool (*visited)[n] = calloc(1, sizeof *visited);
    bool (*graph)[n][n] = calloc(1, sizeof *graph);

    for (size_t v = 0; v < n; ++v) {
        size_t u;
        scanf("%zu[ \n]", &u);
        --u; // index correction
        (*graph)[v][u] = (*graph)[u][v] = true;
    }

    size_t count = 0;

    for (size_t v = 0; v < n; ++v) {
        if (! (*visited)[v]) {
            ++count;
            dfs_visit(v, n, *visited, *graph);
        }
    }

    printf("%zu\n", count);

    free(graph);
    free(visited);

    return 0;
}
