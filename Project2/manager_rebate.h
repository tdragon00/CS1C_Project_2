#ifndef MANAGER_REBATE_H
#define MANAGER_REBATE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class manager_rebate;
}

class manager_rebate : public QDialog
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit manager_rebate(QWidget *parent = nullptr);
    ~manager_rebate();

private slots:
    void on_returnButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::manager_rebate *ui;
};

#endif // MANAGER_REBATE_H
