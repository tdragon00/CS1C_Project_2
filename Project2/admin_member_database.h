#ifndef ADMIN_MEMBER_DATABASE_H
#define ADMIN_MEMBER_DATABASE_H

#include <QDialog>

namespace Ui {
class Admin_Member_Database;
}

class Admin_Member_Database : public QDialog
{
    Q_OBJECT

public:
    explicit Admin_Member_Database(QWidget *parent = nullptr);
    ~Admin_Member_Database();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Admin_Member_Database *ui;
};

#endif // ADMIN_MEMBER_DATABASE_H
