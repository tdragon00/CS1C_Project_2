#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class adminLogin;
}

class adminLogin : public QDialog
{
    Q_OBJECT

public:
   MainWindow conn;
public:
    explicit adminLogin(QWidget *parent = nullptr);
    ~adminLogin();

private slots:
    void on_backLogin_clicked();

    void on_MemberListButton_clicked();

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_Item_Database_clicked();

private:
    Ui::adminLogin *ui;
};

#endif // adminLogin_H
