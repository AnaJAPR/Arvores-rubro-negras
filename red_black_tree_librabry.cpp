#include <iostream>
#include <memory>
#include <algorithm>

enum Color { RED, BLACK };

template <typename T>
struct Node {
    T data;
    Color color;
    std::shared_ptr<Node<T>> left, right, parent;

    Node(T data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RedBlackTree {
private:
    std::shared_ptr<Node<T>> root;

    void rotateLeft(std::shared_ptr<Node<T>>& node);
    void rotateRight(std::shared_ptr<Node<T>>& node);
    void fixInsert(std::shared_ptr<Node<T>>& node);
    void fixDelete(std::shared_ptr<Node<T>>& node);

    void transplant(std::shared_ptr<Node<T>>& u, std::shared_ptr<Node<T>>& v);
    std::shared_ptr<Node<T>> minimum(std::shared_ptr<Node<T>> node);
    std::shared_ptr<Node<T>> maximum(std::shared_ptr<Node<T>> node);
    int height(std::shared_ptr<Node<T>> node);
    void inorderTraversal(std::shared_ptr<Node<T>> node); // Método privado

public:
    RedBlackTree() : root(nullptr) {}

    void insert(const T& data);
    void remove(const T& data);
    std::shared_ptr<Node<T>> search(const T& data);
    void inorderTraversal(); // Método público
    bool isValid();

    std::shared_ptr<Node<T>> getMinimum();
    std::shared_ptr<Node<T>> getMaximum();
    int getHeight();
};

// Implementação dos métodos privados

template <typename T>
void RedBlackTree<T>::rotateLeft(std::shared_ptr<Node<T>>& node) {
    auto y = node->right;
    node->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == nullptr) {
        root = y;
    } else if (node == node->parent->left) {
        node->parent->left = y;
    } else {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
}

template <typename T>
void RedBlackTree<T>::rotateRight(std::shared_ptr<Node<T>>& node) {
    auto y = node->left;
    node->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == nullptr) {
        root = y;
    } else if (node == node->parent->right) {
        node->parent->right = y;
    } else {
        node->parent->left = y;
    }
    y->right = node;
    node->parent = y;
}

template <typename T>
void RedBlackTree<T>::fixInsert(std::shared_ptr<Node<T>>& node) {
    std::shared_ptr<Node<T>> parent = nullptr;
    std::shared_ptr<Node<T>> grandparent = nullptr;

    while ((node != root) && (node->color != BLACK) && (node->parent->color == RED)) {
        parent = node->parent;
        grandparent = node->parent->parent;

        if (parent == grandparent->left) {
            auto uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            auto uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

template <typename T>
void RedBlackTree<T>::inorderTraversal(std::shared_ptr<Node<T>> node) {
    if (node == nullptr) {
        return;
    }
    inorderTraversal(node->left);
    std::cout << node->data << " ";
    inorderTraversal(node->right);
}

template <typename T>
void RedBlackTree<T>::transplant(std::shared_ptr<Node<T>>& u, std::shared_ptr<Node<T>>& v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

template <typename T>
std::shared_ptr<Node<T>> RedBlackTree<T>::minimum(std::shared_ptr<Node<T>> node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <typename T>
std::shared_ptr<Node<T>> RedBlackTree<T>::maximum(std::shared_ptr<Node<T>> node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

template <typename T>
int RedBlackTree<T>::height(std::shared_ptr<Node<T>> node) {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return std::max(leftHeight, rightHeight) + 1;
}

// Implementação dos métodos públicos

template <typename T>
void RedBlackTree<T>::insert(const T& data) {
    auto node = std::make_shared<Node<T>>(data);
    auto y = std::shared_ptr<Node<T>>(nullptr);
    auto x = root;

    while (x != nullptr) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }

    fixInsert(node);
}

template <typename T>
void RedBlackTree<T>::remove(const T& data) {
    // Implementação do método de remoção
}

template <typename T>
std::shared_ptr<Node<T>> RedBlackTree<T>::search(const T& data) {
    auto node = root;
    while (node != nullptr && node->data != data) {
        if (data < node->data) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

template <typename T>
void RedBlackTree<T>::inorderTraversal() {
    inorderTraversal(root);
    std::cout << std::endl;
}

template <typename T>
bool RedBlackTree<T>::isValid() {
    // Implementar verificação das propriedades da árvore rubro-negra
    return true;
}

template <typename T>
std::shared_ptr<Node<T>> RedBlackTree<T>::getMinimum() {
    return minimum(root);
}

template <typename T>
std::shared_ptr<Node<T>> RedBlackTree<T>::getMaximum() {
    return maximum(root);
}

template <typename T>
int RedBlackTree<T>::getHeight() {
    return height(root);
}

// Função de teste

void testRedBlackTree() {
    RedBlackTree<int> rbt;

    // Teste de inserção
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(25);

    // Teste de percurso em ordem simétrica (inorder)
    std::cout << "Inorder traversal: ";
    rbt.inorderTraversal();

    // Teste de busca
    std::cout << "Search for 15: " << (rbt.search(15) != nullptr ? "Found" : "Not Found") << std::endl;
    std::cout << "Search for 100: " << (rbt.search(100) != nullptr ? "Found" : "Not Found") << std::endl;

    // Teste de máximo e mínimo
    std::cout << "Minimum: " << rbt.getMinimum()->data << std::endl;
    std::cout << "Maximum: " << rbt.getMaximum()->data << std::endl;

    // Teste de altura
    std::cout << "Height: " << rbt.getHeight() << std::endl;

    // Teste de validade da árvore rubro-negra
    std::cout << "Is valid Red-Black Tree: " << (rbt.isValid() ? "Yes" : "No") << std::endl;
}

int main() {
    testRedBlackTree();
    return 0;
}
