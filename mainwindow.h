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
    void searchValue(void);
    void deleteValue(void);
    void setVisibleAxisXYZ(bool visible);
    void setRotationX(int value);
    void setRotationY(int value);
    void setRotationZ(int value);
protected:
    void keyPressEvent(QKeyEvent *e);
    int getInputValue(void);
private:

    Ui::MainWindow *ui;
    BSTGL *bstGL;    
};

#endif // MAINWINDOW_H
