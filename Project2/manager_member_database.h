/** @file manager_member_database.h
*	@brief Displays a window for the manager to view the members list.
*/

#ifndef MANAGER_MEMBER_DATABASE_H
#define MANAGER_MEMBER_DATABASE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class manager_member_database;
}

/**
*	@brief Displays a window for the manager to view the members list.
*/
class manager_member_database : public QDialog
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit manager_member_database(QWidget *parent = nullptr);
    ~manager_member_database();

    void Load_Member_Data();
    
private slots:
    void on_returnButton_clicked();

    void on_loadButton_clicked();

    void on_comboBox_currentIndexChanged();

    void on_listView_clicked(const QModelIndex &index);

    void on_tableView_activated(const QModelIndex &index);

    void on_monthSelect_currentIndexChanged();

    void on_searchButton_clicked();

protected:
        void keyPressEvent(QKeyEvent* pe);

private:
    Ui::manager_member_database *ui;
};

#endif // MANAGER_MEMBER_DATABASE_H
