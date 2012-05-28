#include <QtOpenGL>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "painter.h"

Painter::Painter()
{
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
        glColor3f(1.0, 0.0, 0.0);
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
        glColor3f(0.2f, 0.5f, 1.0f);
        glutSolidSphere(radio, 20, 20);
    glPopMatrix();
}

void Painter::drawCone(int x,int y,int z,int radius_top, int radius_bottom, int height,int a,int b,int c) {
    glPushMatrix();
    {
        GLUquadric *cylinder = gluNewQuadric();
        gluQuadricDrawStyle(cylinder, GLU_FILL);
        gluQuadricOrientation(cylinder, GLU_INSIDE);

        glTranslatef(x,y,z);
        //glRotatef(45, a, b, c);
        glRotatef(90, 1, 0, 0);
        glRotatef(45, 0, 1, 0);

        gluCylinder(cylinder, radius_bottom, radius_top, height, 20, 20);
        gluDeleteQuadric(cylinder);
    }
    glPopMatrix();
}

void Painter::drawCylinder(int x,int y,int z,int radius, int height,int a,int b,int c) {
    drawCone(x,y,z,radius, radius, height,a,b,c);
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
        glRotatef(-anguloGraus, 0, 1, 0);

        gluCylinder(cylinder, 2, 2, distance, 200, 20);
        gluDeleteQuadric(cylinder);
    }
    glPopMatrix();
}
