#ifndef BINARYTREE_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif // BINARYTREE_HPP_

#define IPP_TPL template<typename T>

IPP_TPL BinaryTree<T>::BinaryTree() :
    root{nullptr}, count{0}
{}

IPP_TPL auto BinaryTree<T>::insert(int x) -> shrNode
{
    shrNode s = std::make_shared<Node>(x);

    if (root == nullptr) {     // insert as first element
        root = std::move(s);
    }
    else {       // inser after traversing tree
        Node* t = root.get();
        Node* p = nullptr;
        while (t != nullptr) {     // find right place; one loop - linear complexity
            p = t;
            t = x < t->value ? t->left.get() : t->right.get();
        }
        s->parent = p;
        if (x < p->value) {
            p->left = std::move(s);
        }
        else {
            p->right = std::move(s);
        }
    }

    ++count;
    return s;
}

IPP_TPL auto BinaryTree<T>::erase(shrNode t, T x) -> shrNode
{
    if (t != nullptr) {     // traverse tree until `null`
        if (x < t->value) {
            t->left = erase(t->left, x);
        }
        else if (x > t->value) {
            t->right = erase(t->right, x);
        }
        else {       // if `x` is same as `t->value`, then this is the node to be deleted

            // Node with only one child or no child
            if (t->left == nullptr) {
                return t->right;
            }
            else if (t->right == nullptr) {
                return t->left;
            }

            t->value = findExtremum(t->right, true)->value;     // node with two children; get smallest to the right branch
            //                                ^^^^ = search for mininmum

            t->right = erase(t->right, t->value);     // remove the inorder successor
        }
    }

    --count;
    return t;
}

IPP_TPL void BinaryTree<T>::erase(T x)
{
    root = erase(root, x);
}

IPP_TPL std::size_t BinaryTree<T>::size()
{
    return count;
}

IPP_TPL std::size_t BinaryTree<T>::depth(shrNode t)
{
    if (t == nullptr) {
        return 0;
    }

    auto ld = depth(t->left);
    auto rd = depth(t->right);

    return std::max(ld, rd) + 1;
}

IPP_TPL std::size_t BinaryTree<T>::depth()
{
    return depth(root);
}

IPP_TPL auto BinaryTree<T>::search(T x) -> shrNode
{
    shrNode t = root;
    while (t != nullptr && t->value != x) {
        t = x < t->value ? t->left : t->right;
    }
    return t;
}

IPP_TPL auto BinaryTree<T>::searchRecursive(T x, shrNode t) -> shrNode
{
    if (t == nullptr || t->value == x) {
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

IPP_TPL auto BinaryTree<T>::searchRecursive(T x) -> shrNode
{
    return searchRecursive(x, root);
}

IPP_TPL auto BinaryTree<T>::findExtremum(shrNode t, bool searchMin) -> shrNode
{
    shrNode p  = nullptr;
    while (t != nullptr) {
        p = t;
        t = searchMin ? t->left : t->right;
    }
    return p;
}

IPP_TPL T BinaryTree<T>::minimum()
{
    return findExtremum(root, true)->value;
}

IPP_TPL T BinaryTree<T>::maximum()
{
    return findExtremum(root, false)->value;
}

IPP_TPL void BinaryTree<T>::preorder(shrNode t)
{
    if (t != nullptr) {
        t->print();     // is printed before calling recursively for children
        preorder(t->left);
        preorder(t->right);
    }
}

IPP_TPL void BinaryTree<T>::inorder(shrNode t)
{
    if (t != nullptr) {
        inorder(t->left);
        t->print();     // is printed in between recursive call with children
        inorder(t->right);
    }
}

IPP_TPL void BinaryTree<T>::postorder(shrNode t)
{
    if (t != nullptr) {
        postorder(t->left);
        postorder(t->right);
        t->print();     // printing after recursion
    }
}

IPP_TPL void BinaryTree<T>::preorder()
{
    preorder(root);
    std::cout << '\n';
}

IPP_TPL void BinaryTree<T>::inorder()
{
    inorder(root);
    std::cout << '\n';
}

IPP_TPL void BinaryTree<T>::postorder()
{
    postorder(root);
    std::cout << '\n';
}

#undef IPP_TPL
