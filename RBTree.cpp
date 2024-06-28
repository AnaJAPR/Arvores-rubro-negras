#include "RBTree.h"

// Construtor da classe RBTree
RBTree::RBTree() : root(nullptr) {}

// Método para realizar a rotação para a esquerda
void RBTree::rotateLeft(Node *&x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Método para realizar a rotação para a direita
void RBTree::rotateRight(Node *&x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != nullptr)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// Método para corrigir violações das propriedades da árvore após inserção
void RBTree::fixInsertion(Node *&k) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (k != root && k->color != BLACK && k->parent->color == RED) {
        parent = k->parent;
        grandparent = k->parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                k = grandparent;
            } else {
                if (k == parent->right) {
                    rotateLeft(parent);
                    k = parent;
                    parent = k->parent;
                }
                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);
                k = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                k = grandparent;
            } else {
                if (k == parent->left) {
                    rotateRight(parent);
                    k = parent;
                    parent = k->parent;
                }
                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);
                k = parent;
            }
        }
    }
    root->color = BLACK;
}

// Método público para inserir um novo nó na árvore
void RBTree::insert(int data) {
    Node *node = new Node(data);
    Node *y = nullptr;
    Node *x = root;

    // Localiza a posição correta para inserção do novo nó
    while (x != nullptr) {
        y = x;
        if (node->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    // Insere o novo nó na posição encontrada
    node->parent = y;
    if (y == nullptr)
        root = node;
    else if (node->data < y->data)
        y->left = node;
    else
        y->right = node;

    // Caso especial: ajusta a raiz para ser preta após a inserção
    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }

    // Corrige possíveis violações das propriedades da árvore vermelho-negra após a inserção
    if (node->parent->parent == nullptr)
        return;

    fixInsertion(node);
}

// Método para substituir um nó na árvore
void RBTree::transplant(Node *u, Node *v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != nullptr)
        v->parent = u->parent;
}

// Método para encontrar o nó mínimo a partir de um nó dado
Node* RBTree::minimum(Node *node) const {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

// Método para encontrar o nó máximo a partir de um nó dado
Node* RBTree::maximum(Node *node) const {
    while (node->right != nullptr)
        node = node->right;
    return node;
}

// Método para corrigir violações das propriedades da árvore após deleção
void RBTree::fixDeletion(Node *&x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

// Método público para remover um nó da árvore
void RBTree::remove(int data) {
    Node *z = search(data);
    if (z == nullptr)
        return;

    Node *y = z;
    Node *x;
    Color originalColor = y->color;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
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
    if (originalColor == BLACK)
        fixDeletion(x);
}

// Método para buscar um dado na árvore
Node* RBTree::search(int data) const {
    Node *node = root;
    while (node != nullptr && node->data != data) {
        if (data < node->data)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

// Método privado para realizar a travessia em ordem na árvore
void RBTree::inorderTraversal(Node *node) const {
    if (node != nullptr) {
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }
}

// Método público para iniciar a travessia em ordem na árvore
void RBTree::inorder() const {
    inorderTraversal(root);
    std::cout << std::endl;
}

// Método privado para validar as propriedades da árvore a partir de um dado nó
bool RBTree::validateProperties(Node *node) const {
    if (node == nullptr) {
        return true;
    }

    if (node->color == RED) {
        if ((node->left != nullptr && node->left->color == RED) || 
            (node->right != nullptr && node->right->color == RED)) {
            return false;
        }
    }

    int leftBlackHeight = 0;
    Node *temp = node;
    while (temp != nullptr) {
        if (temp->color == BLACK) {
            leftBlackHeight++;
        }
        temp = temp->left;
    }

    int rightBlackHeight = 0;
    temp = node;
    while (temp != nullptr) {
        if (temp->color == BLACK) {
            rightBlackHeight++;
        }
        temp = temp->right;
    }

    if (leftBlackHeight != rightBlackHeight) {
        return false;
    }

    return validateProperties(node->left) && validateProperties(node->right);
}

// Método público para validar as propriedades da árvore vermelho-negra
bool RBTree::validate() const {
    if (root == nullptr) return true;
    if (root->color != BLACK) return false;
    return validateProperties(root);
}

// Método público para encontrar o valor mínimo na árvore
int RBTree::findMin() const {
    if (root == nullptr) return -1;
    Node *minNode = minimum(root);
    return (minNode != nullptr) ? minNode->data : -1;
}

// Método público para encontrar o valor máximo na árvore
int RBTree::findMax() const {
    Node *maxNode = maximum(root);
    return (maxNode != nullptr) ? maxNode->data : -1;
}

// Método privado recursivo para calcular a altura de um dado nó
int RBTree::height(Node *node) const {
    if (node == nullptr) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return std::max(leftHeight, rightHeight) + 1;
}

// Método público para obter a altura da árvore
int RBTree::getHeight() const {
    return height(root);
}
