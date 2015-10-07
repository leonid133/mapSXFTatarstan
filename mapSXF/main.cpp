//#include <QtGui/QApplication>
#include <QtWidgets>
#include <QGuiApplication>
#include "mainwindow.h"
//#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
