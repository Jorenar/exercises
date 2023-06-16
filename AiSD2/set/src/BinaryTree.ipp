#ifndef BINARYTREE_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif // BINARYTREE_HPP_

#define IPP_TPL template<typename T, class Node>

IPP_TPL BinaryTree<T,Node>::BinaryTree() :
    guard{new Node}, root{guard}, count{0}
{
    guard->parent = guard->left = guard->right = guard;
}

IPP_TPL BinaryTree<T,Node>::~BinaryTree()
{
    deleteAllChildNodes(this->root);
    delete guard;
}

IPP_TPL void BinaryTree<T,Node>::deleteAllChildNodes(Node* t)
{
    if (t != guard) {
        deleteAllChildNodes(t->left);
        deleteAllChildNodes(t->right);
        delete t;
    }
}

IPP_TPL auto BinaryTree<T,Node>::insert(int x) -> Node*
{
    Node* s = new Node(guard, x);

    if (root == guard) {     // insert as first element
        root = s;
    }
    else {       // inser after traversing tree
        Node* t = root;
        Node* p = guard;
        while (t != guard) {     // find right place; one loop - linear complexity
            p = t;
            t = x < t->value ? t->left : t->right;
        }
        s->parent = p;
        if (x < p->value) {
            p->left = s;
        }
        else {
            p->right = s;
        }
    }

    ++count;
    return s;
}

IPP_TPL auto BinaryTree<T,Node>::erase(Node* t, T x) -> Node*
{
    if (t == guard) {     // traverse tree until `null`
        return guard;
    }

    if (x < t->value) {
        t->left = erase(t->left, x);
    }
    else if (x > t->value) {
        t->right = erase(t->right, x);
    }
    else {       // if `x` is same as `t->value`, then this is the node to be deleted

        Node* temp = guard;

        // Node with only one child or no child
        if (t->left == guard) {
            temp = t->right;
        }
        else if (t->right == guard) {
            temp = t->left;
        }

        if (temp != guard) {
            temp->parent = t->parent;
            delete t;
            return temp;
        }
        else {
            // node with two children; get smallest to the right branch
            t->value = findExtremum(t->right, true)->value;
            //                                ^^^^ = search for mininmum

            t->right = erase(t->right, t->value); // remove the inorder successor
        }
    }

    return t;
}

IPP_TPL void BinaryTree<T,Node>::erase(T v)
{
    if (this->search(v)) {
        return;
    }
    root = this->erase(root, v);
    --count;
}

IPP_TPL bool BinaryTree<T,Node>::isEmpty() const
{
    return !count;
}

IPP_TPL std::size_t BinaryTree<T,Node>::size() const
{
    return count;
}

IPP_TPL std::size_t BinaryTree<T,Node>::depth(Node* t) const
{
    if (t == guard) {
        return 0;
    }

    auto ld = depth(t->left);
    auto rd = depth(t->right);

    return std::max(ld, rd) + 1;
}

IPP_TPL std::size_t BinaryTree<T,Node>::depth() const
{
    return depth(root);
}

IPP_TPL auto BinaryTree<T,Node>::search(T x) const -> Node*
{
    Node* t = root;
    while (t != guard && t->value != x) {
        t = x < t->value ? t->left : t->right;
    }
    return t != guard ? t : nullptr;
}

IPP_TPL auto BinaryTree<T,Node>::searchRecursive(T x, Node* t) const -> Node*
{
    if (t == guard) {
        return nullptr;
    }

    if (t->value == x) {
        return t;
    }

    auto tl = searchRecursive(x, t->left);
    if (tl) {
        return tl;
    }

    auto tr = searchRecursive(x, t->right);
    if (tr) {
        return tr;
    }
}

IPP_TPL auto BinaryTree<T,Node>::searchRecursive(T x) const -> Node*
{
    return searchRecursive(x, root);
}

IPP_TPL auto BinaryTree<T,Node>::findExtremum(Node* t, bool searchMin) const -> Node*
{
    Node* p  = guard;
    while (t != guard) {
        p = t;
        t = searchMin ? t->left : t->right;
    }
    return p;
}

IPP_TPL T BinaryTree<T,Node>::minimum() const
{
    return findExtremum(root, true)->value;
}

IPP_TPL T BinaryTree<T,Node>::maximum() const
{
    return findExtremum(root, false)->value;
}

IPP_TPL void BinaryTree<T,Node>::preorder(Node* t) const
{
    if (t != guard) {
        t->print();     // is printed before calling recursively for children
        preorder(t->left);
        preorder(t->right);
    }
}

IPP_TPL void BinaryTree<T,Node>::inorder(Node* t) const
{
    if (t != guard) {
        inorder(t->left);
        t->print();     // is printed in between recursive call with children
        inorder(t->right);
    }
}

IPP_TPL void BinaryTree<T,Node>::postorder(Node* t) const
{
    if (t != guard) {
        postorder(t->left);
        postorder(t->right);
        t->print();     // printing after recursion
    }
}

IPP_TPL void BinaryTree<T,Node>::preorder() const
{
    preorder(root);
    std::cout << '\n';
}

IPP_TPL void BinaryTree<T,Node>::inorder() const
{
    inorder(root);
    std::cout << '\n';
}

IPP_TPL void BinaryTree<T,Node>::postorder() const
{
    postorder(root);
    std::cout << '\n';
}

#undef IPP_TPL
