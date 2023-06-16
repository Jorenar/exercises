#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <cstddef>
#include <set>
#include <utility>
#include <vector>

template<typename T>
class Graph {
protected:
    std::vector<T> vertices;
    std::vector<std::vector<bool>> edges;

    inline void assert_vertex(std::size_t) const;

public:

    //< inicjalizuje graf o numVert wierzchołkach
    Graph(const std::size_t numVert);

    //< dodaje krawędź pomiędzy wierzchołkami i oraz j
    void addEdge(const std::size_t i, const std::size_t j);

    //< usuwa krawędź pomiędzy wierzchołkami i oraz j
    void removeEdge(const std::size_t i, const std::size_t j);

    //< sprawdza czy krawędź pomiędzy wierzchołkami i oraz j istnieje
    bool hasEdge(const std::size_t i, const std::size_t j) const;

    //< zwraca wszystkie wierzchołki od których istnieją połączenia do wierzchołka v
    std::set<std::size_t> inConnections(const std::size_t v) const;

    //< zwraca wszystkie wierzchołki do których prowadzą krawędzie wychodzące z v
    std::set<std::size_t> outConnections(const std::size_t v) const;

    //< zwraca wszystkie wierzchołki które są połączone z v lub z którymi v jest połączony
    std::set<std::size_t> allConnections(const std::size_t v) const;

    //< zwraca tablicę najmniejszych odległości z wierzchołka s do poszczególnych wierzchołków
    std::vector<size_t> BFS(const std::size_t s) const;

    //< zwraca czasy rozpoczęcia i zakończenia przetwarzania wierzchołków
    std::vector<std::pair<size_t,size_t>> DFS(const std::size_t s) const;


    std::size_t size() const;
};

#include "Graph.ipp"

#endif // GRAPH_HPP_
