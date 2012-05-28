#ifndef BSTOPENGL_H
#define BSTOPENGL_H

#include <QGLWidget>
#include "bst.h"
#include "painter.h"

class BSTGL: public QGLWidget, public BST,public Painter
{
    Q_OBJECT
public:
    BSTGL(QWidget *parent = 0);

    void setRotateX(int angle);
    void setRotateY(int angle);
    void setRotateZ(int angle);

    void viewAxisXYZ(bool view);
    void paint(Node* node,int y);


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
    void alignNodes(Node* node, int x, int y, int direction);
    void calculate();

    GLfloat fAspect;
    GLfloat angle;
    GLdouble oX;
    GLdouble oY;
    GLdouble oZ;
    int xRot;
    int yRot;
    int zRot;
    bool showAxisXYZ;
    QColor qtPurple;
    QPoint lastPos;
};

#endif // BSTOPENGL_H
