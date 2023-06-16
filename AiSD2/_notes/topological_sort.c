#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void dfs_visit(size_t v, size_t n,
               size_t result[n], size_t *j,
               bool visited[n], bool graph[n][n])
{
    visited[v] = true;
    for (size_t w = 0; w < n; ++w) {
        if (graph[v][w] && !visited[w]) {
            dfs_visit(w, n, result, j, visited, graph);
        }
    }
    result[*j] = v;
    --(*j);
}

void topological_sort(size_t n, size_t result[n], bool graph[n][n])
{
    size_t j = n-1;
    bool (*visited)[n] = calloc(1, sizeof *visited);
    for (size_t v = 0; v < n; ++v) {
        if (! (*visited)[v]) {
            dfs_visit(v, n, result, &j, *visited, graph);
        }
    }
    free(visited);
}

int main(void)
{
    size_t n = 6;

    // bool (*graph)[n][n] = calloc(1, sizeof *graph);
    bool graph[][6] = {
        /*      0  1  2  3  4  5 */
        [0] = { 0, 0, 1, 0, 0, 0 },
        [1] = { 1, 0, 1, 0, 0, 0 },
        [2] = { 0, 0, 0, 0, 0, 0 },
        [3] = { 1, 1, 0, 0, 1, 0 },
        [4] = { 0, 1, 1, 0, 0, 0 },
        [5] = { 1, 0, 0, 0, 1, 0 },
    };

    size_t (*arr)[n] = malloc(sizeof *arr);
    topological_sort(n, *arr, graph);

    for (size_t i = 0; i < n; ++i) {
        printf("%zu ", (*arr)[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
