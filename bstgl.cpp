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
    showAxisXYZ = true;

    qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void BSTGL::calculate() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle, fAspect, 0.5, 500);

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
    qglClearColor(qtPurple.dark());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    angle=45;
    glMatrixMode(GL_MODELVIEW);

    //Light
    GLfloat luzAmbiente[4]  = {1.0,0.7,0.5,1.0};
    GLfloat luzDifusa[4]    = {1.0,1.0,1.0,1.0};	// "cor"
    GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};// "brilho"
    GLfloat posicaoLuz[4]   = {0.0, 10.0, 0.0, 0.0};

    // Capacidade de brilho do material
    GLfloat especularidade[4] = {0.5,1.0,1.0,1.0};
    GLint especMaterial       = 10;

    glShadeModel(GL_SMOOTH);
    // Define a refletância do material
    glMaterialfv(GL_FRONT,GL_DIFFUSE, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);
}

void BSTGL::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    //glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

    if(showAxisXYZ)
        drawAxis3D();


    glColor3f(0.0f, 0.2f, 0.4f);
    alignNodes(root,0,100,ROOT);
    paint(root,100);

//    FTGLPixmapFont font("/home/thiagodnf/Ubuntu-L.ttf");

//    if(font.Error())
//        return ;

//    // Set the font size and render a small text.

//    glPushMatrix();
//    glTranslatef(20,10,10);
//    font.FaceSize(14);
//    font.Render("Hello World!");
//    glPopMatrix();
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

void BSTGL::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void BSTGL::mouseMoveEvent(QMouseEvent *event){
//    int dx = event->x() - lastPos.x();
//    int dy = event->y() - lastPos.y();

//    if (event->buttons() & Qt::LeftButton) {
//        setRotateX(xRot - 8 * dy);
//        //setRotateY(yRot + 8 * dx);
//    } else if (event->buttons() & Qt::RightButton) {
//        setRotateY(xRot + 8 * dy);
//        //setRotateZ(zRot + 8 * dx);
//    }
//    lastPos = event->pos();
}

void BSTGL::wheelEvent(QWheelEvent *event){

    if (event->delta() == -120) {
        if (angle >= 10)
            angle -= 5;

    }else {
        if (angle <= 130)
            angle += 5;
    }
    event->accept();
    calculate();
    updateGL();
}

void BSTGL::setRotateX(int angle){
    //qNormalizeAngle(angle);

    //calculate();

    if(angle < xRot){
        glRotatef(-10, 1.0, 0.0, 0.0);
    }else{
        glRotatef(10, 1.0, 0.0, 0.0);
    }
    xRot = angle;

     updateGL();
}

void BSTGL::setRotateY(int angle){
    if(angle < yRot){
        glRotatef(-10, 0.0, 1.0, 0.0);
    }else{
        glRotatef(10, 0.0, 1.0, 0.0);
    }
    yRot = angle;

     updateGL();
}

void BSTGL::setRotateZ(int angle){
    if(angle < zRot){
        glRotatef(-10, 0.0, 0.0, 1.0);
    }else{
        glRotatef(10, 0.0, 0.0, 1.0);
    }
    zRot = angle;

     updateGL();
}





void BSTGL::viewAxisXYZ(bool view){
    showAxisXYZ = view;
    updateGL();
}

void BSTGL::alignNodes(Node* node,int x,int y,int direction) {
    if (node != 0) {
        int parentX = 0;

        if (direction == TO_RIGHT) {
            int nodes = this->numberOfNodes(node->getLeftNode());
            parentX = node->x = x + (40 * (nodes + 1));
        }
        if (direction == TO_LEFT) {
            int nodes = this->numberOfNodes(node->getRightNode());
            parentX = node->x = x - (40 * (nodes + 1));
        }

        alignNodes(node->getRightNode(),parentX,y,TO_RIGHT);
        alignNodes(node->getLeftNode(),parentX,y,TO_LEFT);
    }
}

void BSTGL::paint(Node* node,int y){
     if(node != 0){

         glColor3f(0.0f, 0.2f, 0.4f);
        if(node->getRightNode() != 0){
            drawEdge(node->x,y,node->getRightNode()->x,y-40);
        }
        if(node->getLeftNode() != 0){
            drawEdge(node->x,y,node->getLeftNode()->x,y-40);
        }

        glColor4f(0.3f, 0.2f, 0.4f,0.1f);
        drawSphere(node->x,y,0,8);

        glColor3f(1.0f, 0.2f, 0.4f);
        drawText(node->x-3,y+15,0, node->getKey());

        paint(node->getLeftNode(),y-40);
        paint(node->getRightNode(),y-40);
    }
}


