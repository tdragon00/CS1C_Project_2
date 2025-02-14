#ifndef MANAGER_MEMBER_DATABASE_H
#define MANAGER_MEMBER_DATABASE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class manager_member_database;
}

class manager_member_database : public QDialog
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit manager_member_database(QWidget *parent = nullptr);
    ~manager_member_database();

private slots:
    void on_returnButton_clicked();

    void on_loadButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_listView_clicked(const QModelIndex &index);

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::manager_member_database *ui;
};

#endif // MANAGER_MEMBER_DATABASE_H
