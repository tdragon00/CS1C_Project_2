/** @file managerCreate.h
*	@brief Displays a window letting the user create an account for manager.
*/

#ifndef MANAGERCREATE_H
#define MANAGERCREATE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class managerCreate;
}

/**
*	@brief Lets the user create an account for manager.
*/
class managerCreate : public QDialog
{
    Q_OBJECT
public:
    MainWindow conn;
    explicit managerCreate(QWidget *parent = nullptr);
    ~managerCreate();

private slots:
    void on_pushButton_clicked();

    void on_pushConfirm_clicked();

    void on_checkPassword_stateChanged();

private:
    Ui::managerCreate *ui;
};

#endif // MANAGERCREATE_H
