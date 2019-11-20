#ifndef MANAGERCREATE_H
#define MANAGERCREATE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class managerCreate;
}

class managerCreate : public QDialog
{
    Q_OBJECT
public:
    MainWindow conn;
public:
    explicit managerCreate(QWidget *parent = nullptr);
    ~managerCreate();

private slots:
    void on_pushButton_clicked();

    void on_pushConfirm_clicked();

    void on_checkPassword_stateChanged(int arg1);

private:
    Ui::managerCreate *ui;
};

#endif // MANAGERCREATE_H
