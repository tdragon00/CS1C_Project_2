#include "mainwindow.h"

#include <QApplication>

    bool MainWindow:: Superadmin=false;
    bool MainWindow::Is_Admin=false;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
