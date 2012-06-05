#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

#include "bstgl.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void addValue(void);
    void addRandomValue(void);
    void searchValue(void);
    void deleteValue(void);
    void enableAxis(bool status);
    void enableLight(bool status);
    void setRotationX(int value);
    void setRotationY(int value);
    void setRotationZ(int value);
    void setLightPositionX(int value);
    void setLightPositionY(int value);
    void setLightPositionZ(int value);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void moveBack();
    void moveFront();
    void resetLight(void);
    void resetRotation(void);
    void clearAll(void);
    void zoomIn(void);
    void zoomOut(void);
    void activeButtons(void);
    void desactiveButtons(void);
    void random(bool status);
    void aboutQt(void);
    void aboutUs(void);

protected:
    void keyPressEvent(QKeyEvent *e);
    int getInputValue(QString name);

private:
    Ui::MainWindow* ui;
    BSTGL* bstGL;
};

#endif // MAINWINDOW_H
