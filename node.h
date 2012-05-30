#ifndef NODE_H
#define NODE_H

#include <QColor>

class Node
{
public:
    Node(int value);
    Node(int value,int x,int y,int z);

    int posX;
    int posY;
    int posZ;
    int value;
    Node* rightNode;
    Node* leftNode;
    QColor color;

    bool hasLeftNode(void);
    bool hasRightNode(void);

    bool moveXUntil(int value, int speed = 1);
    bool moveYUntil(int value,int speed = 1);
    bool moveZUntil(int value, int speed = 1);
    bool moveXYUntilRight(int valueX,int valueY, int speed=1);
    bool moveXYUntilLeft(int valueX,int valueY,int speed=1);
};

#endif // NODE_H
