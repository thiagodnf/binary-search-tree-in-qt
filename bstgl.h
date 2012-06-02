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

    void addValue(int value);
    void searchValue(int value);
    void removeValue(int value);
    void setRotateX(int angle);
    void setRotateY(int angle);
    void setRotateZ(int angle);
    void resetRotation(void);    
    void enableAxis(bool status);
    void enableLight(bool status);
    void clearAll();
    void zoomIn();
    void zoomOut();
    void moveRight();
    void moveLeft();
    void moveBack();
    void moveFront();
    void moveUp();
    void moveDown();
    int numberOfNodes();

protected slots:
    void animate(void);
    void animateAdd();
    void animateSearch();
    void animateRemove();
    void animateAlign();

signals:
    void startOperation();
    void doneOperation();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void calculate();
    void wheelEvent(QWheelEvent *event);

private:
    void appendValue(Node* node, Node** dest);
    void discardedValue();
    void foundValue();
    void removeValue();
    void finish();
    void startAnimation();
    void stopAnimation();
    void paint(Node *node);
    void paintNode(Node* node);
    void paintEdgeCurrentNode();
    bool alignNodes(Node* node,Node *parent,int y,int direction);
    int updateNumberOfChildren(Node* node);

    QTimer* timerAnimation;
    GLfloat fAspect;

    Node* currentNode;
    Node* newCurrentNode;
    Node* nextCurrentNode;
    Node* parentNextCurrentNode;
    int xRot;
    int yRot;
    int zRot;
    int xTrans;
    int yTrans;
    int zTrans;
    bool showAxisXYZ;
    int operation;

};

#endif // BSTGL_H
