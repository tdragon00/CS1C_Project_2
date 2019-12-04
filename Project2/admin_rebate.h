#ifndef ADMIN_REBATE_H
#define ADMIN_REBATE_H

#include <QDialog>

namespace Ui {
class admin_rebate;
}

class admin_rebate : public QDialog
{
    Q_OBJECT

public:
    explicit admin_rebate(QWidget *parent = nullptr);
    ~admin_rebate();

private slots:
    void on_returnButton_clicked();

private:
    Ui::admin_rebate *ui;
};

#endif // ADMIN_REBATE_H
