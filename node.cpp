#include "node.h"
#include <cmath>

using namespace std;

Node::Node(int value)
{
    this->value = value;
    this->rightNode = 0;
    this->leftNode = 0;
    this->posX = 0;
    this->posY = 0;
    this->posZ = 0;
    this->children = 0;
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

Node::~Node(){
    if(hasLeftNode())
        delete leftNode;
    if(hasRightNode())
        delete rightNode;
}

bool Node::hasLeftNode(void){
    return leftNode != 0;
}

bool Node::hasRightNode(void){
    return rightNode != 0;
}

bool Node::isLeaf(void){
    return ! hasLeftNode() && ! hasRightNode();
}

bool Node::moveXUntil(int value,int speed)
{
    if(posX == value)
        return true;
    if(posX > value)
        posX -= speed;
    else
        posX += speed;
    return false;    
}

bool Node::moveYUntil(int value,int speed){
    if(posY == value)
        return true;
    if(posY > value)
        posY -= speed;
    else
        posY += speed;
    return false;
}

bool Node::moveZUntil(int value, int speed){
    if(posZ <= value)
        return true;
    posZ -= speed;
    return false;
}

bool Node::moveXYUntilRight(int valueX,int valueY,int speed){
    if(posX >= valueX && posY <= valueY)
        return true;
    float deltaY = std::abs(posY - valueY);
    float deltaX = std::abs(valueX - posX);

    if(posX < valueX)
        posX += speed*deltaX/deltaY;
    if(posY > valueY)
        posY -= speed;
    return false;
}

bool Node::moveXYUntil(Node *node,int speed)
{
    if(node != 0){
        if(posX == node->posX && posY == node->posY)
            return true;

        float deltaY =  abs(posY - node->posY);
        float deltaX = abs(posX - node->posX);
        float reason = deltaX/deltaY;

        if(posY > node->posY)
            posY -= speed;
        else
            posY += speed;
        if(posX > node->posX)
            posX -= speed*reason;
        else
            posX += speed*reason;
    }
    return false;
}

bool Node::travelUtil(Node *node,int speed)
{
    if(node != 0){
        if(posY < node->posY)
            return true;
        if(posX == node->posX && posY == node->posY)
            return true;

        float deltaY = (posY - node->posY);
        float deltaX = (posX - node->posX);
        float reason = deltaX/deltaY;

        posY -= speed;
        posX -= speed*reason;
    }
    return false;
}

bool Node::travelLeft(Node* node,int speed)
{
    float destX = node->posX-30;
    float destY = node->posY-30;
    if(posX == destX && posY == destY)
        return true;

    if(posY > destY)
        posY -= speed;
    if(posX > destX)
        posX -= speed;

    return false;
}

bool Node::travelRight(Node* node,int speed)
{
    float destX = node->posX+30;
    float destY = node->posY-30;
    if(posX == destX && posY == destY)
        return true;

    if(posY > destY)
        posY -= speed;
    if(posX < destX)
        posX += speed;

    return false;
}

bool Node::travelDown(int value, int speed)
{
    color = QColor(255,21,0);

    if(posY <= value)
        return true;
    posY -= speed;
    return false;
}
