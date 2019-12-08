/** @file admin_item_database.h
*	@brief Displays a window for the admin to see the items list and be able to add and delete items.
*/

#ifndef ADMIN_ITEM_DATABASE_H
#define ADMIN_ITEM_DATABASE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class admin_item_database;
}

/**
*	@brief Admin side UI to see the items list and be able to add and delete items.
*/
class admin_item_database : public QDialog
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit admin_item_database(QWidget *parent = nullptr);
    ~admin_item_database();

private slots:
    void on_returnButton_clicked();

private:
    Ui::admin_item_database *ui;
};

#endif // ADMIN_ITEM_DATABASE_H
