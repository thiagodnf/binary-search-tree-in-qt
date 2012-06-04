#include <QtOpenGL>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "painter.h"

Painter::Painter()
{
    posicaoLuz = new GLfloat[4];
    resetLight();
}

void Painter::drawAxis3D(){
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    {
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(100.0, 0.0, 0.0);
    }
    glEnd();
    drawText(100.0, 0.0, 0.0, "X");

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    {
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 100.0, 0.0);
    }
    glEnd();
    drawText(0.0, 100.0, 0.0, "Y");

    glColor3f(0.0f, 0.5f, 0.4f);
    glBegin(GL_LINES);
    {
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 100.0);
    }
    glEnd();
    drawText(0.0, 0.0, 100.0, "Z");
}

void Painter::drawText(float posX, float posY, float posZ, const char* text) {
    glPushMatrix();
        glRasterPos3f(posX, posY, posZ);
        glutBitmapString(GLUT_BITMAP_HELVETICA_10, (const unsigned char*) text);
    glPopMatrix();
}

void Painter::drawText(float posX, float posY, float posZ, int value) {
    char str[200];
    sprintf(str, "%d", value);
    drawText(posX, posY, posZ, str);
}

void Painter::drawSphere(GLfloat x, GLfloat y, GLfloat z, GLdouble radio) {
    glPushMatrix();
        glTranslatef(x, y, z);        
        glutSolidSphere(radio, 20, 20);
    glPopMatrix();
}

void Painter::drawEdge(int x1,int y1,int x2,int y2){

    int height = abs(y2-y1);
    int width = abs(x2-x1);
    float distance = sqrt(abs(pow(width,2)+pow(height,2)));
    float tan = float(x2-x1)/(y2-y1);
    float anguloRad = atan(tan);
    float anguloGraus = (180/M_PI)*anguloRad;

    glPushMatrix();
    {
        GLUquadric *cylinder = gluNewQuadric();
        gluQuadricDrawStyle(cylinder, GLU_FILL);
        gluQuadricOrientation(cylinder, GLU_INSIDE);

        glTranslatef(x1,y1,0);
        glRotatef(90, 1, 0, 0);

        if(y1>y2)
            glRotatef(-anguloGraus, 0, 1, 0);
        else
            glRotatef(180-anguloGraus, 0, 1, 0);

        gluCylinder(cylinder, 2, 2, distance, 20, 20);
        gluDeleteQuadric(cylinder);
    }
    glPopMatrix();
}

void Painter::enableLight(bool status=true){
    if(status){
        //Light
        GLfloat luzAmbiente[4]  = {1.0,0.7,0.5,1.0};
        GLfloat luzDifusa[4]    = {1.0,1.0,1.0,1.0};	// "cor"
        GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0};// "brilho"        

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
    }else{
        glDisable(GL_COLOR_MATERIAL);
        //Habilita o uso de iluminação
        glDisable(GL_LIGHTING);
        // Habilita a luz de número 0
        glDisable(GL_LIGHT0);
        // Habilita o depth-buffering
        glDisable(GL_DEPTH_TEST);
    }
}

void Painter::setlightPositionX(int valueX){
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    posicaoLuz[0] = valueX;
}

void Painter::setlightPositionY(int valueY){
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    posicaoLuz[1] = valueY;
}

void Painter::setlightPositionZ(int valueZ){
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    posicaoLuz[2] = valueZ;
}

void Painter::resetLight(){
    posicaoLuz[0] = 15.0;
    posicaoLuz[1] = 10.0;
    posicaoLuz[2] = 10.0;
    posicaoLuz[3] = 0.0;
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}
