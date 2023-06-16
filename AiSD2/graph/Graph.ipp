#ifndef GRAPH_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif // GRAPH_HPP_

#include <stdexcept>
#include <queue>

#define IPP_TPL template<typename T>

IPP_TPL Graph<T>::Graph(const std::size_t numVert) :
    vertices(numVert), edges(numVert, std::vector<bool>(numVert, false))
{}

IPP_TPL void Graph<T>::assert_vertex(const std::size_t i) const
{
    if (i < 1 || i > vertices.size()) {
        throw std::out_of_range{"There is no vertex with number " + std::to_string(i)};
    }
}

IPP_TPL void Graph<T>::addEdge(const std::size_t i, const std::size_t j)
{
    assert_vertex(i);
    assert_vertex(j);
    edges[i-1][j-1] = true;
}

IPP_TPL void Graph<T>::removeEdge(const std::size_t i, const std::size_t j)
{
    assert_vertex(i);
    assert_vertex(j);
    edges[i-1][j-1] = false;
}

IPP_TPL bool Graph<T>::hasEdge(const std::size_t i, const std::size_t j) const
{
    assert_vertex(i);
    assert_vertex(j);
    return edges[i-1][j-1];
}

IPP_TPL std::set<std::size_t> Graph<T>::inConnections(const std::size_t v) const
{
    assert_vertex(v);
    std::set<std::size_t> ret {};
    for (std::size_t i = 0; i < edges.size(); ++i) {
        if (edges[i][v-1]) {
            ret.insert(i+1);
        }
    }
    return ret;
}

IPP_TPL std::set<std::size_t> Graph<T>::outConnections(const std::size_t v) const
{
    assert_vertex(v);
    std::set<std::size_t> ret {};
    for (std::size_t i = 0; i < edges.size(); ++i) {
        if (edges[v-1][i]) {
            ret.insert(i+1);
        }
    }
    return ret;
}

IPP_TPL std::set<std::size_t> Graph<T>::allConnections(const std::size_t v) const
{
    assert_vertex(v);
    std::set<std::size_t> ret {};
    for (std::size_t i = 0; i < edges.size(); ++i) {
        if (edges[v-1][i] || edges[i-1][v]) {
            ret.insert(i+1);
        }
    }
    return ret;
}

IPP_TPL std::vector<size_t> Graph<T>::BFS(const std::size_t s) const
{
    assert_vertex(s);

    std::vector<std::size_t> dist(vertices.size(), 0);

    std::queue<std::size_t> Q;
    std::vector<bool> explored(vertices.size(), false);

    explored[s-1] = true;
    Q.push(s-1);

    while (!Q.empty()) {
        auto v = Q.front();
        Q.pop();

        for (std::size_t w = 0; w < edges.size(); ++w) {
            if (edges[v][w] && !explored[w]) {
                dist[w] = dist[v] + 1;
                explored[w] = true;
                Q.push(w);
            }
        }
    }

    return dist;
}

IPP_TPL std::vector<std::pair<size_t,size_t>> Graph<T>::DFS(const std::size_t s) const
{
    assert_vertex(s);

    std::size_t time = 0;
    std::vector<std::pair<size_t,size_t>> dist(vertices.size(), { 0, 0 });

    std::vector<bool> explored(vertices.size(), false);

    auto visit = [&](std::size_t v, auto visit) {
                     explored[v] = true;
                     dist[v].first = ++time;
                     for (std::size_t w = 0; w < edges.size(); ++w) {
                         if (edges[v][w] && !explored[w]) {
                             visit(w, visit);
                         }
                     }
                     dist[v].second = ++time;
                 };

    visit(s, visit);

    return dist;
}

IPP_TPL std::size_t Graph<T>::size() const
{
    return vertices.size();
}


#undef IPP_TPL
