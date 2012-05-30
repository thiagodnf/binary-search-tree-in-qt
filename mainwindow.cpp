#include <QtGui>
#include <ctime>

#include "mainwindow.h"
#include "ui_mainwindow.h"

int z = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand ( time(NULL) );

    bstGL = new BSTGL(this);
    isRandom = false;

    ui->centralWidget->layout()->addWidget(bstGL);

    setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    if(e->key() == Qt::Key_Up)
        bstGL->oZ++;
    if(e->key() == Qt::Key_Down)
        bstGL->oZ--;
    if(e->key() == Qt::Key_Left){
        bstGL->moveX(2);
    }if(e->key() == Qt::Key_Right)
        bstGL->moveX(1);
    else
        QWidget::keyPressEvent(e);
}

void MainWindow::addValue(){
    int value = -1;

    if(isRandom)
        value = rand() % 100 + 1;
    else
        value = getInputValue();

    if(value == -1)
        return;

    bstGL->addValue(value);
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
    return -1;
}

void MainWindow::animate(){

}

void MainWindow::setVisibleAxisXYZ(bool status){
    bstGL->enableAxisXYZ(status);
}

void MainWindow::enableLight(bool status){
    bstGL->enableLight(status);
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

void MainWindow::resetRotation(){
    bstGL->resetRotation();
    ui->spinBoxAxisX->setValue(0);
    ui->spinBoxAxisY->setValue(0);
    ui->spinBoxAxisZ->setValue(0);
}

void MainWindow::zoomIn()
{
    bstGL->zoomIn();
}

void MainWindow::zoomOut()
{
    bstGL->zoomOut();
}

void MainWindow::random(bool status)
{
    isRandom = status;
    ui->actionAddValue->setEnabled(!status);
    ui->actionSearchValue->setEnabled(!status);
    ui->actionRemoveValue->setEnabled(!status);

    if(status){
        addValue();
        connect(bstGL,SIGNAL(valueInserted()),this,SLOT(addValue()));
    }else{
        disconnect(bstGL,SIGNAL(valueInserted()),this,SLOT(addValue()));
    }
}
