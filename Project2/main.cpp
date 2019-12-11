#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>

#include <QApplication>

    bool MainWindow:: Superadmin=true;
    bool MainWindow::Is_Admin=false;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // The widget, contains a layout
    QWidget * b;
    b = new QWidget;

    // The layout arranges and holds
    // all the children of the widget
    QVBoxLayout * vbox;

    vbox = new QVBoxLayout;

    // The user input element, the spinbox!
    QSpinBox * spinbox;

    spinbox = new QSpinBox();
    spinbox->setValue(5);// example of using a pointer to edit its states

    // now add it to the layout
    vbox->addWidget(spinbox);

    // add in an element to connect to,
    // the infamous QLabel
    QLabel * label;

    label = new QLabel("spinbox output");

    // add it also to the layout
    vbox->addWidget(label);
    w.show();
    return a.exec();
}
