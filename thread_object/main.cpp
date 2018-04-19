#include "mainwindow.h"
#include <QApplication>

//error: /home/xgf/xgftest/testthread.cpp:4: error: undefined reference to `vtable for testThread'
//DEFINES += QT_DEPRECATED_WARNINGS

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
