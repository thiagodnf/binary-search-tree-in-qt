#ifndef BST_H
#define BST_H

#include "node.h"

class BST
{
public:
    BST();
    void add(int value,Node* currentNode);
    void addValue(int value);
    void alignNodes(Node* node,int x,int y,int direction);

    bool search(int key);
    bool remove(int key);
    bool isEmpty(void);

    int numberOfNodes(Node* node);
protected:
    Node* root;
    void removeLeftByCopy(Node* node);
    void removeRightByCopy(Node* node);
};

#endif // BST_H
