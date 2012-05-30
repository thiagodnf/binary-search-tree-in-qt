#include <QtGui>
#include <QtOpenGL>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <stack>

#include "bstgl.h"
#include "painter.h"

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
    xTrans = 0;
    showAxisXYZ = true;    
    angle = 45;
    currentNode = 0;
    nextCurrentNode = 0;
    timerAnimation = new QTimer( this );
}

void BSTGL::addValue(int value){
    qDebug()<<"BSTGL::addValue("<<value<<")";

    currentNode = new Node(value,0,150,18);
    currentNode->color = QColor(255,240,0);

    if( ! isEmpty())
        nextCurrentNode = root;

    startAnimation();
}

void BSTGL::appendValue(int value){
    BST::addValue(value);
    currentNode = 0;
    nextCurrentNode = 0;

    stopAnimation();
    emit valueInserted();
}

void BSTGL::startAnimation(){
    connect(timerAnimation, SIGNAL(timeout()), this, SLOT(animate()) );
    timerAnimation->start( 30);
}

void BSTGL::stopAnimation(){
    disconnect(timerAnimation, SIGNAL(timeout()), this, SLOT(animate()) );
}

void BSTGL::animate()
{
    if(currentNode != 0){
        if(nextCurrentNode == 0){
            if(currentNode->moveYUntil(100)){
                if(currentNode->moveZUntil(0))
                    appendValue(currentNode->value);
            }
        }else{
            if(currentNode->moveYUntil(nextCurrentNode->posY )){
                if(currentNode->value > nextCurrentNode->value){
                    if(! nextCurrentNode->hasRightNode()){
                        if(currentNode->moveZUntil(0))
                            if(currentNode->moveXYUntilRight(nextCurrentNode->posX+30,nextCurrentNode->posY-30))
                                appendValue(currentNode->value);
                    }else
                        if(currentNode->moveXYUntilRight(nextCurrentNode->rightNode->posX,nextCurrentNode->rightNode->posY))
                            nextCurrentNode = nextCurrentNode->rightNode;
                }else if(currentNode->value < nextCurrentNode->value){
                    if(! nextCurrentNode->hasLeftNode()){
                        if(currentNode->moveZUntil(0))
                            if(currentNode->moveXYUntilLeft(nextCurrentNode->posX-30,nextCurrentNode->posY-30))
                                appendValue(currentNode->value);
                    }else
                        if(currentNode->moveXYUntilLeft(nextCurrentNode->leftNode->posX,nextCurrentNode->leftNode->posY))
                            nextCurrentNode = nextCurrentNode->leftNode;
                }else{
                    if(currentNode->moveZUntil(0)){
                        currentNode->color = QColor(255,21,0);
                        if(currentNode->moveYUntil(-100,3)){
                            nextCurrentNode = currentNode = 0;
                            emit valueInserted();
                        }
                    }
                }
            }
        }
        updateGL();
    }
}

void BSTGL::calculate()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle, fAspect, 0.4, 2000);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posição do observador e do alvo
    gluLookAt(oX, oY, oZ, 0, 50, 0, 0, 1, 0);
}

void BSTGL::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);

    Painter::enableLight(true);
}

void BSTGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    calculate();
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glTranslatef(xTrans,0,0);

    if(showAxisXYZ)
        drawAxis3D();

    paintEdgeCurrentNode();
    paintNode(currentNode);

    paint(root);
}

void BSTGL::resizeGL(int width, int height)
{
    if (height == 0)
          height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    fAspect = (GLfloat) width / (GLfloat) height;

    calculate();
}

void BSTGL::wheelEvent(QWheelEvent *event)
{
    if (event->delta() == -120) {

    }else {

    }
    event->accept();
}

void BSTGL::zoomIn()
{
    if (angle >= 10)
        angle -= 5;
    calculate();
    updateGL();
}

void BSTGL::zoomOut()
{
    if (angle <= 130)
        angle += 5;
    calculate();
    updateGL();
}

void BSTGL::setRotateX(int angle)
{
    xRot = angle;
    updateGL();
}

void BSTGL::setRotateY(int angle)
{
    yRot = angle;
    updateGL();
}

void BSTGL::setRotateZ(int angle)
{
    zRot = angle;
    updateGL();
}

void BSTGL::resetRotation(){
    xRot = 0;
    yRot = 0;
    zRot = 0;
    updateGL();
}

void BSTGL::moveX(int direction)
{
    if(direction == 1)
        xTrans++;
    else
        xTrans--;
    updateGL();
}


void BSTGL::enableAxisXYZ(bool status){
    showAxisXYZ = status;
    updateGL();
}

void BSTGL::enableLight(bool status)
{
    Painter::enableLight(status);
    updateGL();
}

void BSTGL::paintNode(Node *node)
{
    if(node != 0){
        glColor3f(node->color.redF(),node->color.greenF(),node->color.blueF());
        drawSphere(node->posX,node->posY,node->posZ,8);

        glColor3f(1.0f, 0.2f, 0.4f);
        drawText(node->posX-3,node->posY+15,node->posZ, node->value);
    }
}

void BSTGL::paintEdgeCurrentNode()
{
    if(currentNode != 0){
        if(nextCurrentNode != 0 && currentNode->posY <= nextCurrentNode->posY){
            if(currentNode->color != QColor(255,21,0)){ //Se não for um nó invalido
                glColor3f(0.0f, 0.2f, 0.4f);
                drawEdge(nextCurrentNode->posX,nextCurrentNode->posY,currentNode->posX,currentNode->posY);
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


