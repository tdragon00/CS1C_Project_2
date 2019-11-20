#ifndef MANAGER_MEMBER_DATABASE_H
#define MANAGER_MEMBER_DATABASE_H

#include <QDialog>

namespace Ui {
class manager_member_database;
}

class manager_member_database : public QDialog
{
    Q_OBJECT

public:
    explicit manager_member_database(QWidget *parent = nullptr);
    ~manager_member_database();

private:
    Ui::manager_member_database *ui;
};

#endif // MANAGER_MEMBER_DATABASE_H
