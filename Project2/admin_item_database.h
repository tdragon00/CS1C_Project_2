#ifndef ADMIN_ITEM_DATABASE_H
#define ADMIN_ITEM_DATABASE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class admin_item_database;
}

class admin_item_database : public QDialog
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit admin_item_database(QWidget *parent = nullptr);
    ~admin_item_database();

private slots:
    void on_returnButton_clicked();

    void on_comboBox_currentIndexChanged();

    void on_memberFilter_currentIndexChanged();

    void on_checkMemberFilter_stateChanged();

    void on_checkDateFilter_stateChanged();

private:
    Ui::admin_item_database *ui;
};

#endif // ADMIN_ITEM_DATABASE_H
