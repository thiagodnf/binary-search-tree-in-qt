#include "node.h"

Node::Node(int value)
{
    this->value = value;
    this->rightNode = 0;
    this->leftNode = 0;
    this->posX = 0;
    this->posY = 0;
    this->posZ = 0;
    this->color = QColor(56,106,231);
}

Node::Node(int value, int x, int y, int z)
{
    this->value = value;
    this->rightNode = 0;
    this->leftNode = 0;
    this->posX = x;
    this->posY = y;
    this->posZ = z;
    this->color = QColor(56,106,231);
}

bool Node::hasLeftNode(void)
{
    return leftNode != 0;
}

bool Node::hasRightNode(void)
{
    return rightNode != 0;
}

bool Node::moveXUntil(int value,int speed)
{
    if(posX >= value)
        return true;
    else
        posX += speed;
    return false;
}

bool Node::moveYUntil(int value,int speed){
    if(posY <= value)
        return true;
    else
        posY -= speed;
    return false;
}

bool Node::moveZUntil(int value, int speed){
    if(posZ <= value)
        return true;
    else
        posZ -= speed;
    return false;
}

bool Node::moveXYUntilRight(int valueX,int valueY,int speed){
    if(posX >= valueX && posY <= valueY)
        return true;
    else{
        float deltaY = std::abs(posY - valueY);
        float deltaX = std::abs(valueX - posX);

        if(posX < valueX)
            posX += speed*deltaX/deltaY;
        if(posY > valueY)
            posY -= speed;
    }
    return false;
}

bool Node::moveXYUntilLeft(int valueX,int valueY, int speed){
    if(posX <= valueX && posY <= valueY)
        return true;
    else{
        float deltaY = (posY - valueY);
        float deltaX = (posX - valueX);

        if(posX > valueX)
            posX -= speed*deltaX/deltaY;
        if(posY > valueY)
            posY -= speed;
    }
    return false;
}
