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
   // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8")); //изменения
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP1251")); //изменения
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8")); //изменения

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
