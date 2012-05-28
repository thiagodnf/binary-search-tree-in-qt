#ifndef OPENGLPAINTER_H
#define OPENGLPAINTER_H

class Painter
{
public:
    Painter();

    void drawAxis3D(void);
    void drawText(float posX, float posY, float posZ = 0.0, const char* text = "");
    void drawText(float posX, float posY, float posZ, int value);
    void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLdouble radio) ;

    void drawCone(int x,int y,int z,int radius_top, int radius_bottom, int height, int a, int b, int c);

    void drawCylinder(int x,int y,int z,int radius, int height,int a, int b, int c);
    void drawEdge(int x1, int y1,int x2, int y2);
};

#endif // OPENGLPAINTER_H
