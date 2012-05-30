#ifndef BSTGL_H
#define BSTGL_H

#include <QGLWidget>
#include "bst.h"
#include "painter.h"

class BSTGL: public QGLWidget, public BST,public Painter
{
    Q_OBJECT
public:
    GLdouble oX;
    GLdouble oY;
    GLdouble oZ;
    GLfloat angle;
    BSTGL(QWidget *parent = 0);

    void setRotateX(int angle);
    void setRotateY(int angle);
    void setRotateZ(int angle);

    void addValue(int value);
    void appendValue(int value);

    void enableAxisXYZ(bool status);
    void enableLight(bool status);

    void paint(Node *node);
    void startAnimation();
    void stopAnimation();
    void zoomIn();
    void zoomOut();
    void camera();
protected slots:
    void animate(void);

signals:
    void valueInserted();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void wheelEvent(QWheelEvent *event);
private:
    void paintNode(Node* node);
    void paintEdgeCurrentNode();

    void calculate();


    QTimer *timerAnimation;
    GLfloat fAspect;

    Node* currentNode;
    Node* nextCurrentNode;
    int xRot;
    int yRot;
    int zRot;
    bool showAxisXYZ;

};

#endif // BSTGL_H
