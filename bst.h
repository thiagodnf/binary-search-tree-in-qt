#ifndef BST_H
#define BST_H

#include "node.h"

class BST
{
public:
    BST();

    void addValue(int value);    
    bool searchValue(int value);
    bool removeValue(int value);


    bool isEmpty(void);

    void alignNodes(Node* node,int x,int y,int direction);
    int numberOfNodes(Node* node);
protected:
    Node* root;    
    void add(int value,Node* currentNode);
    bool search(int value,Node* node);    
    bool remove(Node** node, int value);
};

#endif // BST_H
