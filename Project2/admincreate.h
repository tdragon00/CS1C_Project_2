/** @file adminCreate.h
*	@brief Displays a window for the user to create an administrator account.
*/

#ifndef ADMINCREATE_H
#define ADMINCREATE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class adminCreate;
}

/**
*	@brief Lets the user to create an administrator account.
*/
class adminCreate : public QDialog
{
    Q_OBJECT
public:
    MainWindow conn;
    explicit adminCreate(QWidget *parent = nullptr);
    ~adminCreate();

private slots:
    void on_pushButton_clicked();

    void on_pushConfirm_clicked();

    void on_checkPassword_stateChanged();

private:
    Ui::adminCreate *ui;
};

#endif // adminCREATE_H
