/** @file adminLogin.h
*	@brief Displays a window for the adminstrator a menu page once logged in.
*/

#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class adminLogin;
}

/**
*	@brief A menu page for the adminstrator once logged in.
*/
class adminLogin : public QDialog
{
    Q_OBJECT

public:
   MainWindow conn;
    explicit adminLogin(QWidget *parent = nullptr);
    ~adminLogin();

private slots:
    void on_backLogin_clicked();

    void on_MemberListButton_clicked();

    void on_pushButton_clicked();

    void on_itemsButton_clicked();

    void on_rebateButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::adminLogin *ui;
};

#endif // adminLogin_H
