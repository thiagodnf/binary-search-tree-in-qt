#ifndef BST_H
#define BST_H

#include "node.h"

class BST
{
public:
    BST();
    bool add(int key);
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
