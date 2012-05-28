#include <QtGui/QApplication>
#include "mainwindow.h"

#include <GL/glut.h>

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
