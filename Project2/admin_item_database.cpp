#include "admin_item_database.h"
#include "ui_admin_item_database.h"

admin_item_database::admin_item_database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_item_database)
{
    ui->setupUi(this);
}

admin_item_database::~admin_item_database()
{
    delete ui;
}
