#include <vector>
#include "Graph.hpp"

template<typename T>
class GraphCycles : public Graph<T> {
public:
    bool hasCycles(Graph<T> G) const
    {
        std::vector<bool> visited(G.size(), false);
        std::vector<bool> finished(G.size(), false);

        auto visit = [&](auto& visit, std::size_t v) -> bool {
                         visited[v] = true;
                         for (auto u: G.outConnections(v)) {
                             if (!finished[u] && (visited[u] || visit(u))) {
                                 return true;
                             }
                         }
                         finished[v] = true;
                         return false;
                     };

        for (auto v: G.verticles) {
            if (!visited[v] && visit(visit, v)) {
                return true;
            }
        }

        return false;
    }
}
