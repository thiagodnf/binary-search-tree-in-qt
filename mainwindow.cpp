#include <QtGui>
#include <ctime>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    srand ( time(NULL) );

    bstGL = new BSTGL(this);
    ui->centralWidget->layout()->addWidget(bstGL);

    setFocus();
    connect(bstGL,SIGNAL(startOperation()),this,SLOT(desactiveButtons()));
    connect(bstGL,SIGNAL(doneOperation()),this,SLOT(activeButtons()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_Escape)
        close();
    if(e->key() == Qt::Key_Right)
        moveRight();
    if(e->key() == Qt::Key_Left)
        moveLeft();
    if(e->key() == Qt::Key_PageUp)
        moveFront();
    if(e->key() == Qt::Key_PageDown)
        moveBack();
    if(e->key() == Qt::Key_Up)
        moveUp();
    if(e->key() == Qt::Key_Down)
        moveDown();
    else
        QWidget::keyPressEvent(e);
}

void MainWindow::moveLeft(){
    bstGL->moveLeft();
}

void MainWindow::moveRight(){
    bstGL->moveRight();
}

void MainWindow::moveFront(){
    bstGL->moveFront();
}

void MainWindow::moveBack(){
    bstGL->moveBack();
}

void MainWindow::moveUp(){
    bstGL->moveUp();
}

void MainWindow::moveDown(){
    bstGL->moveDown();
}

void MainWindow::addValue(){
    int value = getInputValue("Add Value");

    if(value == -1)
        return;
    bstGL->addValue(value);
}

void MainWindow::addRandomValue(){
    int value = rand() % 100 + 1;
    bstGL->addValue(value);
}

void MainWindow::searchValue(){
    int value = getInputValue("Search Value");

    if(value == -1)
        return;
    bstGL->searchValue(value);
}

void MainWindow::deleteValue(){
    int value = getInputValue("Remove Value");

    if(value == -1)
        return;
    bstGL->removeValue(value);
}

int MainWindow::getInputValue(QString name){
    bool ok = false;
    int value = QInputDialog::getInt(this, tr("Input"),name, 2,1,199,1,&ok);

    if(ok)
        return value;
    return -1;
}

void MainWindow::enableAxis(bool status){
    bstGL->enableAxis(status);
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

void MainWindow::setLightPositionX(int value){
    bstGL->setlightPositionX(value);
    bstGL->updateGL();
}

void MainWindow::setLightPositionY(int value){
    bstGL->setlightPositionY(value);
    bstGL->updateGL();
}

void MainWindow::setLightPositionZ(int value){
    bstGL->setlightPositionZ(value);
    bstGL->updateGL();
}

void MainWindow::resetLight(){
    ui->hSliderLightX->setValue(15);
    ui->hSliderLightY->setValue(10);
    ui->hSliderLightZ->setValue(10);
    bstGL->resetLight();
    bstGL->updateGL();
}

void MainWindow::resetRotation(){
    bstGL->resetRotation();
    ui->spinBoxAxisX->setValue(0);
    ui->spinBoxAxisY->setValue(0);
    ui->spinBoxAxisZ->setValue(0);
}

void MainWindow::clearAll(){
    bstGL->clearAll();
    ui->lineEditNodes->setText(QString::number(bstGL->numberOfNodes()));
}

void MainWindow::zoomIn(){
    bstGL->zoomIn();
}

void MainWindow::zoomOut(){
    bstGL->zoomOut();
}

void MainWindow::aboutQt(){
    qApp->aboutQt();
}

void MainWindow::aboutUs(){
    QMessageBox::about(this, tr("About Us"),
            QString::fromUtf8(
               "<h2>Qt BST with OpenGL</h2>"
               "Trabalho final da disciplina de Computação Gráfica"
               "<br><br>"
               "<b>Universidade Estadual do Ceará - UECE</b>"
               "<br><br>"
               "<b>Professor:</b>  Thelmo de Araújo"
               "<br><br>"
               "<b>Semestre:</b>  2012.1"
               "<br><br>"
               "<b>Desenvolvedores</b>"
               "<br>"
               "Débora Martins <br>"
               "Marcos Brizeno <br>"
               "Thiago Nascimento <br>"
               "<br>"
               "<b>Código Fonte:</b>  <a href='https://github.com/thiagodnf/QtBSTOpenGL'>https://github.com/thiagodnf/QtBSTOpenGL</a>"
               "<br><br>"
               ));
}

void MainWindow::activeButtons(){
    ui->actionAddValue->setEnabled(true);
    ui->actionSearchValue->setEnabled(true);
    ui->actionRemoveValue->setEnabled(true);
    ui->actionClearAll->setEnabled(true);
    ui->lineEditNodes->setText(QString::number(bstGL->numberOfNodes()));
}

void MainWindow::desactiveButtons(){
    ui->actionAddValue->setEnabled(false);
    ui->actionSearchValue->setEnabled(false);
    ui->actionRemoveValue->setEnabled(false);
    ui->actionClearAll->setEnabled(false);
}

void MainWindow::random(bool status){      
    if(status){
        addRandomValue();
        connect(bstGL,SIGNAL(doneOperation()),this,SLOT(addRandomValue()));
    }else
        disconnect(bstGL,SIGNAL(doneOperation()),this,SLOT(addRandomValue()));
}
