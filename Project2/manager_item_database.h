/** @file manager_item_database.h
*	@brief Displays a window for the manager to view the items list.
*/

#ifndef MANAGER_ITEM_DATABASE_H
#define MANAGER_ITEM_DATABASE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class manager_item_database;
}

/**
*	@brief A window for the manager to view the items list.
*/
class manager_item_database : public QDialog
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit manager_item_database(QWidget *parent = nullptr);
    ~manager_item_database();

private slots:
    void on_returnButton_clicked();

private:
    Ui::manager_item_database *ui;
};

#endif // MANAGER_ITEM_DATABASE_H
