#include <iostream>
#include <vector>

int main(void)
{
    std::size_t n;
    std::cin >> n;

    if (n == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }

    std::vector<std::vector<std::size_t>> graph(n);
    std::vector<bool> visited(n, false);

    for (std::size_t v = 0; v < n; ++v) {
        std::size_t u;
        std::cin >> u;
        --u; // index correction
        graph[v].push_back(u);
        graph[u].push_back(v);
    }

    std::size_t count = 0;

    auto dfs_visit = [&](std::size_t v, auto& dfs_visit) -> void
    {
        visited[v] = true;
        for (auto w: graph[v]) {
            if (!visited[w]) {
                dfs_visit(w, dfs_visit);
            }
        }
    };

    for (std::size_t v = 0; v < n; ++v) {
        if (!visited[v]) {
            ++count;
            dfs_visit(v, dfs_visit);
        }
    }

    std::cout << count << std::endl;

    return 0;
}
