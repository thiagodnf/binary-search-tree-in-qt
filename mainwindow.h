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
    void addValue();
    void searchValue(void);
    void deleteValue(void);
    void setVisibleAxisXYZ(bool status);
    void enableLight(bool status);
    void setRotationX(int value);
    void setRotationY(int value);
    void setRotationZ(int value);
    void resetRotation();
    void animate(void);
    void zoomIn();
    void zoomOut(void);
    void random(bool status);
protected:
    void keyPressEvent(QKeyEvent *e);
    int getInputValue(void);
private:

    bool isRandom;
    Ui::MainWindow *ui;
    BSTGL *bstGL;    
};

#endif // MAINWINDOW_H
