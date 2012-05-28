#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"

int z = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bstGL = new BSTGL(this);

    ui->centralWidget->layout()->addWidget(bstGL);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
   // qDebug()<<e->key();
    if (e->key() == Qt::Key_Escape)
        close();
    if(e->key() == Qt::Key_Z)
        setRotationZ(z++);
//    if(e->key() == Qt::Key_X)
//        bstGL->rotateX();
//    if(e->key() == Qt::Key_Y)
//        bstGL->rotateY();

    else
        QWidget::keyPressEvent(e);
    qDebug()<<z;
}

void MainWindow::addValue(){
    int value = getInputValue();

    if(value == -1)
        return;

    bool result = bstGL->add(value);

    if(result)
        qDebug()<<"Sucess";
    else
        qDebug()<<"Fail";

    bstGL->updateGL();
}

void MainWindow::searchValue(){

}

void MainWindow::deleteValue(){

}

int MainWindow::getInputValue(){
    bool ok = false;

    int value = QInputDialog::getInt(this, tr("Input"),tr("Add Value:"), 2,1,199,1,&ok);

    if(ok)
        return value;
    else
        return -1;
}

void MainWindow::setVisibleAxisXYZ(bool visible){
    bstGL->viewAxisXYZ(visible);
}

void MainWindow::setRotationX(int angle){
    bstGL->setRotateX(angle);
}

void MainWindow::setRotationY(int angle){
    bstGL->setRotateY(angle);
}

void MainWindow::setRotationZ(int angle){
    bstGL->setRotateZ(angle);
}
