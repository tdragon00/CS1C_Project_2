#include "admin_member_database.h"
#include "ui_admin_member_database.h"

Admin_Member_Database::Admin_Member_Database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin_Member_Database)
{
    ui->setupUi(this);
}

Admin_Member_Database::~Admin_Member_Database()
{
    delete ui;
}
