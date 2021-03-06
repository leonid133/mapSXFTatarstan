#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>
#include <QObject>
#include "map.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots: // публичные слоты

private slots: // приватные

signals: // сигналы

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    WMap *wgt;
};

#endif // MAINWINDOW_H
