//#include <QtGui/QApplication>
#include <QtWidgets>
#include <QGuiApplication>
#include "mainwindow.h"
//#include <QFileDialog>
#include <locale.h>
#include <QTextCodec> // подключение класса кодека текста

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "RUS");

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
