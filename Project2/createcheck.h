/** @file CreateCheck.h
*	@brief Displays a window letting the user choose which type of an account to create.
*/

#ifndef CREATECHECK_H
#define CREATECHECK_H

#include <QDialog>

namespace Ui {
class CreateCheck;
}

/**
*	@brief Lets the user choose which type of an account to create.
*/
class CreateCheck : public QDialog
{
    Q_OBJECT

public:
    explicit CreateCheck(QWidget *parent = nullptr);
    ~CreateCheck();

private slots:
    void on_typeConfirm_clicked();

private:
    Ui::CreateCheck *ui;
};

#endif // CREATECHECK_H
