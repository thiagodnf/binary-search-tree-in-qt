#ifndef OPENGLPAINTER_H
#define OPENGLPAINTER_H

class Painter
{
public:
    Painter();

    GLfloat* posicaoLuz;

    void drawAxis3D(void);
    void drawText(float posX, float posY, float posZ = 0.0, const char* text = "");
    void drawText(float posX, float posY, float posZ, int value);
    void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLdouble radio) ;
    void drawEdge(int x1, int y1,int x2, int y2);

    void enableLight(bool status);
    void setlightPositionX(int valueX);
    void setlightPositionY(int valueY);
    void setlightPositionZ(int valueZ);
    void resetLight();
};

#endif // OPENGLPAINTER_H
