#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setStyleSheet("QMainWindow{image: url(:/new/prefix1/bg4.jpg)}");


    w.show();

    return a.exec();
}
