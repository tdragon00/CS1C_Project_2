/** @file managerLogin.h
*	@brief Displays a menu for the manager once logged in.
*/

#ifndef MANAGERLOGIN_H
#define MANAGERLOGIN_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class managerLogin;
}

/**
*	@brief Displays a menu for the manager once logged in.
*/
class managerLogin : public QDialog
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit managerLogin( QWidget *parent = nullptr);
    ~managerLogin();
private slots:
    void on_backLogin_clicked();

//    void on_orderButton_clicked();

//    void on_checkout_clicked();

    void on_Member_Data_clicked();

    void on_Item_Data_clicked();

    void on_rebateButton_clicked();

    void on_itemsButton_clicked();

    void on_Sales_Report_clicked();

private:
    Ui::managerLogin *ui;
};

#endif // managerLogin_H
