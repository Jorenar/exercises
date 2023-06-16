#ifndef SET_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif

#include <exception>

#define IPP_TPL template<typename T>

IPP_TPL void Set<T>::insert(T v)
{
    if (!this->search(v)) {
        Base::insert(v);
    }
}

IPP_TPL bool Set<T>::isMember(T v) const
{
    return this->search(v);
}

IPP_TPL T Set<T>::pop()
{
    if (this->isEmpty()) {
        throw std::out_of_range{"Set is empty!"};
    }
    auto v = this->root->value;
    this->remove(v);
    return v;
}

IPP_TPL Set<T>* Set<T>::intersection(Set<T>* set2) const
{
    auto ret = new Set<T>{};

    if (this->isEmpty() || set2->isEmpty()) {
        return ret;
    }

    auto add = [&](Node* n, auto& add) {
                   if (n == this->guard) {
                       return;
                   }
                   auto v = n->value;
                   if (set2->isMember(v)) {
                       ret->insert(v);
                   }
                   add(n->left, add);
                   add(n->right, add);
               };
    add(this->root, add);

    return ret;
}

IPP_TPL Set<T>* Set<T>::difference(Set* set2) const
{
    auto ret = new Set{};

    auto add = [&](Node* n, auto& add) {
                   if (n == this->guard) {
                       return;
                   }
                   auto v = n->value;
                   if (!set2->isMember(v)) {
                       ret->insert(v);
                   }
                   add(n->left, add);
                   add(n->right, add);
               };
    add(this->root, add);

    return ret;
}

IPP_TPL Set<T>* Set<T>::unionWith(Set* set2) const
{
    auto ret = new Set{};

    auto add = [&](const Node* const g, Node* n, auto& add) {
                   if (n == g) {
                       return;
                   }
                   ret->insert(n->value);
                   add(g, n->left, add);
                   add(g, n->right, add);
               };
    add(this->guard, this->root, add);
    add(set2->guard, set2->root, add);

    return ret;
}

#undef IPP_TPL
