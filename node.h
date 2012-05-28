#ifndef NODE_H
#define NODE_H

class Node
{
public:
    Node(int key);
    int x;

    int getKey();
    void setKey(int key);
    void setRightNode(Node *node);
    Node* getRightNode();
    void setLeftNode(Node *node);
    Node* getLeftNode();
private:
    int key;
    Node *rigthNode;
    Node *leftNode;
};

#endif // NODE_H
