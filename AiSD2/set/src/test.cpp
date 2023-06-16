#include <iostream>
#include "RedBlackTree.hpp"
#include "Set.hpp"

int main()
{
    Set<int> t1;
    Set<int> t2;

    t1.insert(1);
    t2.insert(2);
    t1.insert(3);
    t2.insert(4);

    std::cout << "T1: "; t1.inorder();
    std::cout << "T2: "; t2.inorder();

    auto t3 = t1.unionWith(&t2);
    std::cout << "T3: "; t3->inorder();

    auto t4 = t1.intersection(t3);
    std::cout << "T4: "; t4->inorder();

    auto t5 = t3->difference(&t1);
    std::cout << "T5: "; t5->inorder();

    std::cout << '\n';
    t3->insert(0);
    std::cout << "T3.insert(5): "; t3->inorder();

    std::cout << "\n[3x] T3.pop(): "
              << t3->pop() << " "
              << t3->pop() << " "
              << t3->pop() << " "
              << std::endl;
    std::cout << "T3: "; t3->inorder();

    delete t3;
    delete t4;
    delete t5;

    return 0;
}
