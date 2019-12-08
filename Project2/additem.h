#ifndef ADDITEM_H
#define ADDITEM_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class addItem;
}

class addItem : public QWidget
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit addItem(QWidget *parent = nullptr);
    ~addItem();

private slots:
    void on_addButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::addItem *ui;
};

#endif // ADDITEM_H
