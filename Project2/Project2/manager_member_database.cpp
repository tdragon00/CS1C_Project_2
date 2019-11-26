#include "manager_member_database.h"
#include "ui_manager_member_database.h"

manager_member_database::manager_member_database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager_member_database)
{
    ui->setupUi(this);
}

manager_member_database::~manager_member_database()
{
    delete ui;
}
