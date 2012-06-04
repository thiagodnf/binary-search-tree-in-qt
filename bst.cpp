#include "bst.h"
#include <QDebug>

#define ROOT     0
#define TO_RIGHT 1
#define TO_LEFT  2

BST::BST()
{
    root = 0;
}

void BST::add(int value, Node* currentNode){
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

bool BST::search(int value, Node *node){
    if(node != 0){
        if(value > node->value)
            return search(value,node->rightNode);
        else if(value < node->value)
            return search(value,node->leftNode);
        return true;
    }
    return false;
}

bool BST::searchValue(int value) {
   return search(value,root);
}

bool BST::removeValue(int value){
    if(!isEmpty())
        remove(&root,value);
    return false;
}

/**
*@TODO Falta implementar o caso de remoção quando
*       o nó tem dois filhos
*/
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

int BST::numberOfNodes(Node* node) {
    return node == 0 ? 0 : numberOfNodes(node->leftNode) + numberOfNodes(node->rightNode) + 1;
}

bool BST::isEmpty() {
    return root == 0;
}
