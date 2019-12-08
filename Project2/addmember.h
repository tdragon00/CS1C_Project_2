/** @file addMember.h
*	@brief Displays a window for adding a member to the database.
*/

#ifndef ADDMEMBER_H
#define ADDMEMBER_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class addMember;
}

/**
*	@brief Adding a member to the database.
*/
class addMember : public QWidget
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit addMember(QWidget *parent = nullptr);
    ~addMember();

private slots:
    void on_addButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::addMember *ui;
};

#endif // ADDMEMBER_H
