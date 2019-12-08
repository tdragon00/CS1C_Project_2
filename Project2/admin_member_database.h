/** @file Admin_Member_Database.h
*	@brief Displays a window for the admin to view the members list and be able to edit, add and delete members.
*/

#ifndef ADMIN_MEMBER_DATABASE_H
#define ADMIN_MEMBER_DATABASE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Admin_Member_Database;
}

/**
*	@brief Admin UI to view the members list and be able to edit, add and delete members.
*/

class Admin_Member_Database : public QDialog
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit Admin_Member_Database(QWidget *parent = nullptr);
    ~Admin_Member_Database();

private slots:
    void on_returnButton_clicked();

    void on_loadButton_clicked();

    void on_comboBox_currentIndexChanged();

    void on_updateButton_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_tableView_activated(const QModelIndex &index);

    void on_deleteButton_clicked();

    void on_pushButton_clicked();

    void on_monthSelect_currentIndexChanged();

    void on_searchButton_clicked();



private:
    Ui::Admin_Member_Database *ui;
};

#endif // ADMIN_MEMBER_DATABASE_H
