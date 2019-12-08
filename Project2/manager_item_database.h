#ifndef MANAGER_ITEM_DATABASE_H
#define MANAGER_ITEM_DATABASE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class manager_item_database;
}

class manager_item_database : public QDialog
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit manager_item_database(QWidget *parent = nullptr);
    ~manager_item_database();

private:
    Ui::manager_item_database *ui;
};

#endif // MANAGER_ITEM_DATABASE_H
