#include <iostream>
#include "Graph.hpp"

int main()
{
    Graph<int> g(8);
    g.addEdge(1,2); g.addEdge(2,1);
    g.addEdge(1,3); g.addEdge(3,1);
    g.addEdge(1,4); g.addEdge(4,1);
    g.addEdge(2,4); g.addEdge(4,2);
    g.addEdge(2,5); g.addEdge(5,2);
    g.addEdge(4,5); g.addEdge(5,4);
    g.addEdge(6,7); g.addEdge(7,6);
    g.addEdge(8,6);

    std::cout
        << R"(     1 --- 2   6 <--- 8  )" << '\n'
        << R"(    / \   / \   \        )" << '\n'
        << R"(   /   \ /   \   \       )" << '\n'
        << R"(  3     4 --- 5   7      )" << '\n'
        << '\n';


    std::cout << "     [ ";
    for (std::size_t i = 1; i <= g.size(); ++i) {
        std::cout << i << " ";
    }
    std::cout << "]\n";

    auto dist = [g](std::size_t s) {
        std::cout << "[s=" << s << "]  ";
        for (auto e: g.BFS(s)) {
            std::cout << e << " ";
        }
        std::cout << '\n';
    };

    dist(4);
    dist(6);
    dist(8);

    auto outin = [g](std::size_t s) {
        std::cout << s << " --> ";
        for (auto v: g.outConnections(s)) {
            std::cout << v << " ";
        }
        std::cout << '\n';

        std::cout << s << " <-- ";
        for (auto v: g.inConnections(s)) {
            std::cout << v << " ";
        }
        std::cout << '\n';
    };

    std::cout << '\n';
    outin(3);

    std::cout << '\n';
    outin(4);

    std::cout << '\n';
    outin(6);

    std::cout << '\n';
    outin(8);

    return 0;
}
