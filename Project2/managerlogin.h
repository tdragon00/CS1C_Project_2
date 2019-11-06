#ifndef MANAGERLOGIN_H
#define MANAGERLOGIN_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class managerLogin;
}

class managerLogin : public QDialog
{
    Q_OBJECT

public:
    explicit managerLogin(QString username, QWidget *parent = nullptr);
    ~managerLogin();

public:
    MainWindow conn;
private slots:
    void on_backLogin_clicked();

//    void on_orderButton_clicked();

//    void on_checkout_clicked();

private:
    Ui::managerLogin *ui;
};

#endif // managerLogin_H
