#include "bst.h"

BST::BST()
{
    root = 0;
}

bool BST::add(int key) {
    if (root == 0) {
        root = new Node(key);
        return true;
    }
    Node *newNode = root;
    while (newNode != 0) {
        if (key < newNode->getKey()) {
            if (newNode->getLeftNode() == 0) {
                newNode->setLeftNode(new Node(key));
                return true;
            }
            newNode = newNode->getLeftNode();
        } else if (key > newNode->getKey()) {
            if (newNode->getRightNode() == 0) {
                newNode->setRightNode(new Node(key));
                return true;
            }
            newNode = newNode->getRightNode();
        } else {
            return false;
        }
    }
    return false;
}

bool BST::search(int key) {
    Node * search = root;
    while (search != 0) {
        if (search->getKey() == key)
            return true;
        if (key < search->getKey())
            search = search->getLeftNode();
        else
            search = search->getRightNode();
    }
    return false;
}

bool BST::remove(int key) {
    //Árvore vazia
    if (root == 0)
        return false;

    //Remover a raiz
    if (root->getKey() == key) {
        Node* toDelete = root;
        if (root->getLeftNode() == 0)
            root = root->getRightNode();
        else if (root->getRightNode() == 0)
            root = root->getLeftNode();
        else {
            Node* rightMost = root->getLeftNode();
            Node* previous = 0;
            while (rightMost->getRightNode() != 0) {
                previous = rightMost;
                rightMost = rightMost->getRightNode();
            }
            if (previous == 0)
                toDelete->setLeftNode(rightMost->getLeftNode());
            else
                previous->setRightNode(rightMost->getLeftNode());
            root->setKey(rightMost->getKey());
            toDelete = rightMost;
        }
        delete toDelete;
        return true;
    }

    //Pesquisar na árvore
    Node* search = root;
    Node* previous = 0;
    while (search != 0) {
        if (search->getKey() == key) {
            if (previous->getLeftNode() == search)
                removeLeftByCopy(previous);
            else
                removeRightByCopy(previous);
            return true;
        }
        previous = search;
        search =
                key < search->getKey() ?
                        search->getLeftNode() : search->getRightNode();
    }
    return false;
}

void BST::removeLeftByCopy(Node *node) {
    Node* toDelete = node->getLeftNode();
    if (toDelete->getLeftNode() == 0)
        node->setLeftNode(toDelete->getRightNode());
    else if (toDelete->getRightNode() == 0)
        node->setLeftNode(toDelete->getLeftNode());
    else {
        Node* rightMost = toDelete->getLeftNode();
        Node* previous = 0;
        while (rightMost->getRightNode() != 0) {
            previous = rightMost;
            rightMost = rightMost->getRightNode();
        }
        if (previous == 0)
            toDelete->setLeftNode(rightMost->getLeftNode());
        else
            previous->setRightNode(rightMost->getLeftNode());
        toDelete->setKey(rightMost->getKey());
        toDelete = rightMost;
    }
    delete toDelete;
}

void BST::removeRightByCopy(Node *node) {
    Node* toDelete = node->getRightNode();
    if (toDelete->getLeftNode() == 0)
        node->setRightNode(toDelete->getRightNode());
    else if (toDelete->getRightNode() == 0)
        node->setRightNode(toDelete->getLeftNode());
    else {
        Node* rightMost = toDelete->getLeftNode();
        Node* previous = 0;
        while (rightMost->getRightNode() != 0) {
            previous = rightMost;
            rightMost = rightMost->getRightNode();
        }
        if (previous == 0)
            toDelete->setLeftNode(rightMost->getLeftNode());
        else
            previous->setRightNode(rightMost->getLeftNode());
        toDelete->setKey(rightMost->getKey());
        toDelete = rightMost;
    }
    delete toDelete;
}

int BST::numberOfNodes(Node* node) {
    if (node != 0)
        return numberOfNodes(node->getLeftNode()) + numberOfNodes(node->getRightNode()) + 1;
    return 0;
}

bool BST::isEmpty() {
    if (root == 0)
        return true;
    return false;
}
