/** @file accountConfirm.h
*	@brief Displays a window letting the user know the account was made in success.
*/

#ifndef ACCOUNTCONFIRM_H
#define ACCOUNTCONFIRM_H

#include <QDialog>

namespace Ui {
class accountConfirm;
}

/**
*	@brief Lets the user know the account was made in success.
*/
class accountConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit accountConfirm(QWidget *parent = nullptr);
    ~accountConfirm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::accountConfirm *ui;
};

#endif // ACCOUNTCONFIRM_H
