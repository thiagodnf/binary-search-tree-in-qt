#include "node.h"

Node::Node(int key) {
    this->key = key;
    this->rigthNode = 0;
    this->leftNode = 0;
    this->x = 0;
}

int Node::getKey() {
    return this->key;
}

Node *Node::getRightNode() {
    return this->rigthNode;
}

Node *Node::getLeftNode() {
    return this->leftNode;
}

void Node::setRightNode(Node *node) {
    this->rigthNode = node;
}

void Node::setLeftNode(Node *node) {
    this->leftNode = node;
}

void Node::setKey(int key) {
    this->key = key;
}

