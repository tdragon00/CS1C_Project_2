#ifndef ADMIN_ITEM_DATABASE_H
#define ADMIN_ITEM_DATABASE_H

#include <QDialog>

namespace Ui {
class admin_item_database;
}

class admin_item_database : public QDialog
{
    Q_OBJECT

public:
    explicit admin_item_database(QWidget *parent = nullptr);
    ~admin_item_database();

private:
    Ui::admin_item_database *ui;
};

#endif // ADMIN_ITEM_DATABASE_H
