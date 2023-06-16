#ifndef REDBLACKTREE_HPP_
#  error Template implementation file should only be included from corresponding header file
#endif

#define IPP_TPL template<typename T>

IPP_TPL void RedBlackTree<T>::rotateLeft(Node* x)
{
    auto y = x->right;
    x->right = y->left;

    if (y->left && y->left != this->guard) {
        y->left->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == this->guard) {
        this->root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

IPP_TPL void RedBlackTree<T>::rotateRight(Node* x)
{
    auto y = x->left;
    x->left = y->right;

    if (y->right != this->guard) {
        y->right->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == this->guard) {
        this->root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

IPP_TPL auto RedBlackTree<T>::insert(T v) -> Node*
{
    auto z = Base::insert(v);
    z->color = rbtree::Color::Red;
    if (z->parent == this->guard) {
        z->color = rbtree::Color::Black;
    }
    else if (z->parent->parent != this->guard) {
        fixupInsert(z);
    }
    return z;
}

IPP_TPL void RedBlackTree<T>::fixupInsert(Node* z)
{
    while (z->parent->color == rbtree::Color::Red) {
        if (z->parent == z->parent->parent->right) {
            auto y = z->parent->parent->left;
            if (y->color == rbtree::Color::Red) {
                y->color = rbtree::Color::Black;
                z->parent->color = rbtree::Color::Black;
                z->parent->parent->color = rbtree::Color::Red;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(z);
                }
                z->parent->color = rbtree::Color::Black;
                z->parent->parent->color = rbtree::Color::Red;
                rotateLeft(z->parent->parent);
            }
        }
        else {
            auto y = z->parent->parent->right;

            if (y->color == rbtree::Color::Red) {
                y->color = rbtree::Color::Black;
                z->parent->color = rbtree::Color::Black;
                z->parent->parent->color = rbtree::Color::Red;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(z);
                }
                z->parent->color = rbtree::Color::Black;
                z->parent->parent->color = rbtree::Color::Red;
                rotateRight(z->parent->parent);
            }
        }
        if (z == this->root) {
            break;
        }
    }
    this->root->color = rbtree::Color::Black;
}

IPP_TPL void RedBlackTree<T>::remove(T v)
{
    if (!this->search(v)) {
        return;
    }

    auto transplant = [this](Node* u, Node* v) {
                          if (u->parent == this->guard) {
                              this->root = v;
                          }
                          else if (u == u->parent->left) {
                              u->parent->left = v;
                          }
                          else {
                              u->parent->right = v;
                          }
                          v->parent = u->parent;
                      };

    auto t = this->root;
    auto z = this->guard;

    while (t != this->guard) {
        if (t->value == v) {
            z = t;
        }

        if (t->value <= v) {
            t = t->right;
        }
        else {
            t = t->left;
        }
    }

    if (z == this->guard) {
        return;
    }

    Node* x;
    auto y = z;
    auto y_orig_color = y->color;

    if (z->left == this->guard) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == this->guard) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = this->findExtremum(z->right, true /* = minimum */);
        y_orig_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (y_orig_color == rbtree::Color::Black) {
        fixupRemove(x);
    }

    --(this->count);
}

IPP_TPL void RedBlackTree<T>::erase(T v)
{
    remove(v);
}

IPP_TPL void RedBlackTree<T>::fixupRemove(Node* x)
{
    while (x != this->root && x->color == rbtree::Color::Black) {
        if (x == x->parent->left) {
            auto w = x->parent->right;
            if (w->color == rbtree::Color::Red) {
                w->color = rbtree::Color::Black;
                x->parent->color = rbtree::Color::Red;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == rbtree::Color::Black && w->right->color == rbtree::Color::Black) {
                w->color = rbtree::Color::Red;
                x = x->parent;
            }
            else {
                if (w->right->color == rbtree::Color::Black) {
                    w->left->color = rbtree::Color::Black;
                    w->color = rbtree::Color::Red;
                    rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = rbtree::Color::Black;
                rotateLeft(x->parent);
                x = this->root;
            }
        }
        else {
            auto w = x->parent->right;
            if (w->color == rbtree::Color::Red) {
                w->color = rbtree::Color::Black;
                x->parent->color = rbtree::Color::Red;
                rotateRight(x->parent);
                w = x->parent->right;
            }
            if (w->right->color == rbtree::Color::Black && w->right->color == rbtree::Color::Black) {
                w->color = rbtree::Color::Red;
                x = x->parent;
            }
            else {
                if (w->right->color == rbtree::Color::Black) {
                    w->right->color = rbtree::Color::Black;
                    w->color = rbtree::Color::Red;
                    rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = rbtree::Color::Black;
                rotateRight(x->parent);
                x = this->root;
            }
        }
    }
    x->color = rbtree::Color::Black;
}

#undef IPP_TPL
