#include <QtGui>
#include <QtOpenGL>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <stack>

#include "bstgl.h"
#include "painter.h"

#define ROOT     0
#define TO_RIGHT 1
#define TO_LEFT  2

using namespace std;

BSTGL::BSTGL(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent),BST(),Painter()
{
    oX = 0;
    oY = 0;
    oZ = 200;
    xRot = 0;
    yRot = 0;
    zRot = 0;
    operation = 0;
    xTrans = 0;
    yTrans = 0;
    zTrans = 0;
    showAxisXYZ = false;
    angle = 45;
    currentNode = 0;
    nextCurrentNode = 0;
    newCurrentNode = 0;
    parentNextCurrentNode = 0;
    timerAnimation = new QTimer( this );
}

void BSTGL::addValue(int value){
    qDebug()<<"BSTGL::addValue("<<value<<")";
    operation = 1;
    currentNode = new Node(value,0,150,18);
    currentNode->color = QColor(255,240,0);

    if( ! isEmpty())
        nextCurrentNode = root;

    startAnimation();    
}

void BSTGL::searchValue(int value){
    qDebug()<<"BSTGL::searchValue("<<value<<")";
    operation = 2;

    currentNode = new Node(value,0,150,18);
    currentNode->color = QColor(255,0,255);

    if( ! isEmpty())
        nextCurrentNode = root;

    startAnimation();
}

void BSTGL::removeValue(int value){
    qDebug()<<"BSTGL::deleteValue("<<value<<")";
    operation = 3;

    currentNode = new Node(value,0,150,18);
    currentNode->color = QColor(100,200,12);

    if( ! isEmpty())
        nextCurrentNode = root;

    startAnimation();
}

void BSTGL::appendValue(Node* node,Node** dest){
    operation = 4;
    (*dest) = node;
    updateNumberOfChildren(root);
    currentNode->color = QColor(56,106,231);
}

void BSTGL::discardedValue(){
    qDebug()<<"BSTGL::discardedValue("<<currentNode->value<<")";
    delete currentNode;
    finish();
}

void BSTGL::removeValue(){
    qDebug()<<"BSTGL::removeValue()";
    operation = 4;
    newCurrentNode = 0;
    currentNode = 0;
    updateNumberOfChildren(root);
}

void BSTGL::foundValue(){
    qDebug()<<"BSTGL::foundValue("<<currentNode->value<<")";
    operation = 0;
    nextCurrentNode = 0;
    stopAnimation();
}

void BSTGL::finish(){
    qDebug()<<"BSTGL::finish()";
    nextCurrentNode = 0;
    currentNode = 0;
    operation = 0;

    stopAnimation();
}

void BSTGL::startAnimation(){
    emit startOperation();
    connect(timerAnimation, SIGNAL(timeout()), this, SLOT(animate()) );
    timerAnimation->start(30);
}

void BSTGL::stopAnimation(){    
    disconnect(timerAnimation, SIGNAL(timeout()), this, SLOT(animate()) );   
    emit doneOperation();
}

void BSTGL::animate(){
    switch(operation){
    case 1:
        animateAdd();
        break;
    case 2:
        animateSearch();
        break;
    case 3:
        animateRemove();
        break;
    case 4:
         animateAlign();
         break;
    }
    updateGL();
}

void BSTGL::animateAdd(){
    if(isEmpty()){
         if(currentNode->moveYUntil(100) && currentNode->moveZUntil(0))
            appendValue(currentNode,&root);
    }else{
        if(currentNode->travelUtil(nextCurrentNode)){
            if(currentNode->value > nextCurrentNode->value){
                if(nextCurrentNode->hasRightNode())
                    nextCurrentNode = nextCurrentNode->rightNode;
                else
                    if(currentNode->moveZUntil(0) && currentNode->travelRight(nextCurrentNode))
                        appendValue(currentNode,&nextCurrentNode->rightNode);
            }else if(currentNode->value < nextCurrentNode->value){
                if(nextCurrentNode->hasLeftNode())
                    nextCurrentNode = nextCurrentNode->leftNode;
                else
                    if(currentNode->moveZUntil(0) && currentNode->travelLeft(nextCurrentNode))
                        appendValue(currentNode,&nextCurrentNode->leftNode);
            }else{
                if(currentNode->moveZUntil(0) && currentNode->travelDown(-width()/3,7))
                    discardedValue();
            }
        }
    }
}

void BSTGL::animateSearch(){
    if(isEmpty()){
         if(currentNode->travelDown(-width()/3,7))
            discardedValue();
    }else{
        if(currentNode->travelUtil(nextCurrentNode)){
            if(currentNode->value > nextCurrentNode->value){
                if(nextCurrentNode->hasRightNode())
                    nextCurrentNode = nextCurrentNode->rightNode;
                else
                    if(currentNode->moveZUntil(0) && currentNode->travelDown(-width()/3,7))
                        discardedValue();
            }else if(currentNode->value < nextCurrentNode->value){
                if(nextCurrentNode->hasLeftNode())
                    nextCurrentNode = nextCurrentNode->leftNode;
                else
                    if(currentNode->moveZUntil(0) && currentNode->travelDown(-width()/3,7))
                        discardedValue();
            }else{
                if(currentNode->moveZUntil(0))
                    foundValue();
            }
        }
    }
}

void BSTGL::animateRemove(){
    if(isEmpty()){
         if(currentNode->travelDown(-width()/3,7))
            discardedValue();
    }else{
        if(currentNode->travelUtil(nextCurrentNode)){
            if(currentNode->value > nextCurrentNode->value){
                if(nextCurrentNode->hasRightNode()){
                    parentNextCurrentNode = nextCurrentNode;
                    nextCurrentNode = nextCurrentNode->rightNode;
                }else
                    if(currentNode->moveZUntil(0) && currentNode->travelDown(-width()/3,7))
                        discardedValue();
            }else if(currentNode->value < nextCurrentNode->value){
                if(nextCurrentNode->hasLeftNode()){
                    parentNextCurrentNode = nextCurrentNode;
                    nextCurrentNode = nextCurrentNode->leftNode;
                }else
                    if(currentNode->moveZUntil(0) && currentNode->travelDown(-width()/3,7))
                        discardedValue();
            }else{
                if(currentNode->moveZUntil(0)){
                    if(nextCurrentNode->isLeaf() ){
                        if(nextCurrentNode == root){
                            root = 0;
                        }else{
                            if(parentNextCurrentNode != 0){
                                if(parentNextCurrentNode->hasLeftNode())
                                    if(parentNextCurrentNode->leftNode == nextCurrentNode)
                                        parentNextCurrentNode->leftNode = 0;
                                if(parentNextCurrentNode->hasRightNode())
                                    if(parentNextCurrentNode->rightNode == nextCurrentNode)
                                        parentNextCurrentNode->rightNode = 0;
                            }
                        }
                        removeValue();
                    }else if( ! nextCurrentNode->hasLeftNode() && nextCurrentNode->hasRightNode()){
                        if(nextCurrentNode == root){
                            root = nextCurrentNode->rightNode;
                        }else{
                            if(parentNextCurrentNode->rightNode == nextCurrentNode)
                                parentNextCurrentNode->rightNode = nextCurrentNode->rightNode;
                            else if(parentNextCurrentNode->leftNode == nextCurrentNode)
                                parentNextCurrentNode->leftNode = nextCurrentNode->rightNode;
                        }
                        removeValue();
                    }else if( nextCurrentNode->hasLeftNode() && ! nextCurrentNode->hasRightNode()){
                        if(nextCurrentNode == root){
                            root = nextCurrentNode->leftNode;
                        }else{
                            if(parentNextCurrentNode->rightNode == nextCurrentNode)
                                parentNextCurrentNode->rightNode = nextCurrentNode->leftNode;
                            else if(parentNextCurrentNode->leftNode == nextCurrentNode)
                                parentNextCurrentNode->leftNode = nextCurrentNode->leftNode;
                        }
                        removeValue();
                    }else if( nextCurrentNode->hasLeftNode() && nextCurrentNode->hasRightNode()){
                        if(newCurrentNode == 0){
                            newCurrentNode = nextCurrentNode->rightNode;
                            while( newCurrentNode->hasLeftNode())
                                newCurrentNode = newCurrentNode->leftNode;
                        }
                        if(newCurrentNode->moveXYUntil(nextCurrentNode)){
                            nextCurrentNode->value = newCurrentNode->value;
                            BST::remove(&nextCurrentNode->rightNode,newCurrentNode->value);
                            removeValue();
                        }
                    }
                }
            }
        }
    }
}

void BSTGL::animateAlign(){
    if(alignNodes(root,0,100,ROOT))
        finish();
}

bool BSTGL::alignNodes(Node *node,Node* parent,int y, int direction){
    bool position = true;
    if (node != 0) {
        position = node->moveYUntil(y);

        int nodes = 0;
        int value = 0;

        if(direction == ROOT && node->isLeaf())
            position = true;
        if (direction == TO_RIGHT) {
            if(node->hasLeftNode())
                nodes = node->leftNode->children;
            value = parent->posX + (30 * (nodes + 1));
        }
        if (direction == TO_LEFT) {
            if(node->hasRightNode())
                nodes = node->rightNode->children;
            value = parent->posX - (30 * (nodes + 1));
        }

        if(node->moveXUntil(value,3))
            position = position && true;
        else
            position = position && false;

        bool resultRight = alignNodes(node->rightNode,node,y-30,TO_RIGHT);
        bool resultLeft = alignNodes(node->leftNode,node,y-30,TO_LEFT);

        position = position && resultRight && resultLeft;
    }
    return position;
}

int BSTGL::updateNumberOfChildren(Node* node){
    int number = 0;
    if (node != 0) {
        int rightNumber = updateNumberOfChildren(node->rightNode);
        int leftNumber = updateNumberOfChildren(node->leftNode);
        number = node->children = 1 + rightNumber + leftNumber;
    }
    return number;
}

void BSTGL::clearAll(){
    delete root;
    root = 0;
    currentNode = 0;
    updateGL();
}

void BSTGL::calculate(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle, fAspect, 0.4, 2000);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posição do observador e do alvo
    gluLookAt(oX, oY, oZ, 0, 50, 0, 0, 1, 0);

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glTranslatef(xTrans,yTrans,zTrans);
}

void BSTGL::initializeGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);

    Painter::enableLight(true);
}

void BSTGL::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(showAxisXYZ)
        drawAxis3D();

    if(operation == 1)
        paintEdgeCurrentNode();

    paintNode(currentNode);

    paint(root);
}

void BSTGL::resizeGL(int width, int height){
    if (height == 0)
          height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    fAspect = (GLfloat) width / (GLfloat) height;

    calculate();
}

void BSTGL::wheelEvent(QWheelEvent *event){
    if (event->delta() == -120)
        zoomIn();
    else
        zoomOut();
    event->accept();
}

void BSTGL::zoomIn(){
    if (angle >= 10)
        angle -= 5;
    calculate();
    updateGL();
}

void BSTGL::zoomOut(){
    if (angle <= 130)
        angle += 5;
    calculate();
    updateGL();
}

void BSTGL::moveRight(){
    xTrans += 3;
    calculate();
    updateGL();
}

void BSTGL::moveLeft(){
    xTrans -= 3;
    calculate();
    updateGL();
}

void BSTGL::moveFront(){
    zTrans += 3;
    calculate();
    updateGL();
}

void BSTGL::moveBack(){
    zTrans -= 3;
    calculate();
    updateGL();
}

void BSTGL::moveUp(){
    yTrans += 3;
    calculate();
    updateGL();
}

void BSTGL::moveDown(){
    yTrans -= 3;
    calculate();
    updateGL();
}

int BSTGL::numberOfNodes(){
    if(! isEmpty())
        return root->children;
    return 0;
}

void BSTGL::setRotateX(int angle){
    xRot = angle;
    calculate();
    updateGL();
}

void BSTGL::setRotateY(int angle){
    yRot = angle;
    calculate();
    updateGL();
}

void BSTGL::setRotateZ(int angle){
    zRot = angle;
    calculate();
    updateGL();
}

void BSTGL::resetRotation(){
    xRot = 0;
    yRot = 0;
    zRot = 0;
    calculate();
    updateGL();
}

void BSTGL::enableAxis(bool status){
    showAxisXYZ = status;
    updateGL();
}

void BSTGL::enableLight(bool status){
    Painter::enableLight(status);
    updateGL();
}

void BSTGL::paintNode(Node *node){
    if(node != 0){
        glColor3f(node->color.redF(),node->color.greenF(),node->color.blueF());
        drawSphere(node->posX,node->posY,node->posZ,8);

        glColor3f(1.0f, 0.2f, 0.4f);        
        drawText(node->posX-3,node->posY+10,node->posZ, node->value);
    }
}

void BSTGL::paintEdgeCurrentNode(){
    if(currentNode != 0){
        if(nextCurrentNode != 0){
            if(currentNode->posY <= nextCurrentNode->posY){
                if(currentNode->color != QColor(255,21,0)){ //Se não for um nó invalido
                    glColor3f(0.0f, 0.2f, 0.4f);
                    drawEdge(nextCurrentNode->posX,nextCurrentNode->posY,currentNode->posX,currentNode->posY);
                }
            }
        }
    }
}

void BSTGL::paint(Node* node){
     if(node != 0){
        glColor3f(0.0f, 0.2f, 0.4f);

        if(node->hasRightNode())
            drawEdge(node->posX,node->posY,node->rightNode->posX,node->rightNode->posY);
        if(node->hasLeftNode())
            drawEdge(node->posX,node->posY,node->leftNode->posX,node->leftNode->posY);

        paintNode(node);

        paint(node->leftNode);
        paint(node->rightNode);
    }
}


