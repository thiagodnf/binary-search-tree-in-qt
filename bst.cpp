#include "bst.h"
#include <QDebug>

#define ROOT     0
#define TO_RIGHT 1
#define TO_LEFT  2

BST::BST()
{
    root = 0;
}

//bool BST::add(int value) {
//    if (root == 0) {
//        root = new Node(value);
//        return true;
//    }
//    Node *newNode = root;
//    while (newNode != 0) {
//        if (key < newNode->getKey()) {
//            if (newNode->leftNode == 0) {
//                newNode->leftNode = new Node(key);
//                return true;
//            }
//            newNode = newNode->leftNode;
//        } else if (key > newNode-) {
//            if (newNode->getRightNode() == 0) {
//                newNode->setRightNode(new Node(key));
//                return true;
//            }
//            newNode = newNode->getRightNode();
//        } else {
//            return false;
//        }
//    }
//    return false;
//}

void BST::add(int value, Node* currentNode)
{
    if (value > currentNode->value) {
        if (currentNode->hasRightNode())
            add(value,currentNode->rightNode);
        else
            currentNode->rightNode = new Node(value);
    } else if (value < currentNode->value) {
        if (currentNode->hasLeftNode())
            add(value,currentNode->leftNode);
        else
            currentNode->leftNode = new Node(value);
    } else
        qDebug()<<"Value already exists.";
}

void BST::addValue(int value){
    if(isEmpty())
        root = new Node(value);
    else
        add(value,root);

    //alignNodes(root,0,100,ROOT);
}

void BST::alignNodes(Node* node,int x,int y,int direction) {
    if (node != 0) {
        int parentX = 0;

        node->posY = y;

        if (direction == TO_RIGHT) {
            int nodes = this->numberOfNodes(node->leftNode);
            parentX = node->posX = x + (30 * (nodes + 1));
        }
        if (direction == TO_LEFT) {
            int nodes = this->numberOfNodes(node->rightNode);
            parentX = node->posX = x - (30 * (nodes + 1));
        }

        alignNodes(node->rightNode,parentX,y-30,TO_RIGHT);
        alignNodes(node->leftNode,parentX,y-30,TO_LEFT);
    }
}

bool BST::search(int value, Node *node)
{
    if(node != 0){
        if(node->value == value)
            return true;
        else if(value > node->value)
            return search(value,node->rightNode);
        else if(value < node->value)
            return search(value,node->leftNode);
    }
    return false;
}

bool BST::searchValue(int value) {
   return search(value,root);
}

bool BST::removeValue(int value)
{
    if(isEmpty())
        return false;
    else
        remove(&root,value);

    //alignNodes(root,0,100,ROOT);
    return false;
}

bool BST::remove(Node** node, int value){
    if(*node != 0){
        if((*node)->value == value){
            if((*node)->isLeaf()){
                delete (*node);
                (*node) = 0;
            }else if( ! (*node)->hasLeftNode() && (*node)->hasRightNode()){
                Node* aux = (*node);
                (*node) = aux->rightNode;
                aux->rightNode = 0;
                delete aux;
            }else if((*node)->hasLeftNode() && ! (*node)->hasRightNode()){
                Node* aux = (*node);
                (*node) = aux->leftNode;
                aux->leftNode = 0;
                delete aux;
            }

        }else if(value > (*node)->value)
            return remove(&(*node)->rightNode,value);
        else if(value < (*node)->value)
            return remove(&(*node)->leftNode,value);
    }
    return false;
}

//bool BST::remove(int key) {
//    //Árvore vazia
//    if (root == 0)
//        return false;

//    //Remover a raiz
//    if (root->getKey() == key) {
//        Node* toDelete = root;
//        if (root->getLeftNode() == 0)
//            root = root->getRightNode();
//        else if (root->getRightNode() == 0)
//            root = root->getLeftNode();
//        else {
//            Node* rightMost = root->getLeftNode();
//            Node* previous = 0;
//            while (rightMost->getRightNode() != 0) {
//                previous = rightMost;
//                rightMost = rightMost->getRightNode();
//            }
//            if (previous == 0)
//                toDelete->setLeftNode(rightMost->getLeftNode());
//            else
//                previous->setRightNode(rightMost->getLeftNode());
//            root->setKey(rightMost->getKey());
//            toDelete = rightMost;
//        }
//        delete toDelete;
//        return true;
//    }

//    //Pesquisar na árvore
//    Node* search = root;
//    Node* previous = 0;
//    while (search != 0) {
//        if (search->getKey() == key) {
//            if (previous->getLeftNode() == search)
//                removeLeftByCopy(previous);
//            else
//                removeRightByCopy(previous);
//            return true;
//        }
//        previous = search;
//        search =
//                key < search->getKey() ?
//                        search->getLeftNode() : search->getRightNode();
//    }
//    return false;
//}

//void BST::removeLeftByCopy(Node *node) {
//    Node* toDelete = node->getLeftNode();
//    if (toDelete->getLeftNode() == 0)
//        node->setLeftNode(toDelete->getRightNode());
//    else if (toDelete->getRightNode() == 0)
//        node->setLeftNode(toDelete->getLeftNode());
//    else {
//        Node* rightMost = toDelete->getLeftNode();
//        Node* previous = 0;
//        while (rightMost->getRightNode() != 0) {
//            previous = rightMost;
//            rightMost = rightMost->getRightNode();
//        }
//        if (previous == 0)
//            toDelete->setLeftNode(rightMost->getLeftNode());
//        else
//            previous->setRightNode(rightMost->getLeftNode());
//        toDelete->setKey(rightMost->getKey());
//        toDelete = rightMost;
//    }
//    delete toDelete;
//}

//void BST::removeRightByCopy(Node *node) {
//    Node* toDelete = node->getRightNode();
//    if (toDelete->getLeftNode() == 0)
//        node->setRightNode(toDelete->getRightNode());
//    else if (toDelete->getRightNode() == 0)
//        node->setRightNode(toDelete->getLeftNode());
//    else {
//        Node* rightMost = toDelete->getLeftNode();
//        Node* previous = 0;
//        while (rightMost->getRightNode() != 0) {
//            previous = rightMost;
//            rightMost = rightMost->getRightNode();
//        }
//        if (previous == 0)
//            toDelete->setLeftNode(rightMost->getLeftNode());
//        else
//            previous->setRightNode(rightMost->getLeftNode());
//        toDelete->setKey(rightMost->getKey());
//        toDelete = rightMost;
//    }
//    delete toDelete;
//}

int BST::numberOfNodes(Node* node) {
    if (node != 0)
        return numberOfNodes(node->leftNode) + numberOfNodes(node->rightNode) + 1;
    return 0;
}

bool BST::isEmpty() {
    if (root == 0)
        return true;
    return false;
}
