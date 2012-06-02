#ifndef NODE_H
#define NODE_H

#include <QColor>
#include <cmath>

class Node
{
public:
    Node(int value);
    Node(int value,int x,int y,int z);
    ~Node();

    int posX;
    int posY;
    int posZ;
    int value;
    int children;
    Node* rightNode;
    Node* leftNode;
    QColor color;   

    bool hasLeftNode(void);
    bool hasRightNode(void);
    bool isLeaf(void);

    bool moveXUntil(int value, int speed = 1);
    bool moveYUntil(int value,int speed = 1);
    bool moveZUntil(int value, int speed = 1);
    bool moveXYUntilRight(int valueX,int valueY, int speed=1);
    bool moveXYUntil(Node *node,int speed=1);

    bool travelUtil(Node* node, int speed=1);
    bool travelLeft(Node* node,int speed=1);
    bool travelRight(Node* node,int speed=1);
    bool travelDown(int value, int speed);
};

#endif // NODE_H
