#include "admin_rebate.h"
#include "ui_admin_rebate.h"

#include "adminlogin.h"

admin_rebate::admin_rebate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_rebate)
{
    ui->setupUi(this);
}

admin_rebate::~admin_rebate()
{
    delete ui;
}

//return to admin login page
void admin_rebate::on_returnButton_clicked()
{
    hide();
    adminLogin *administratorLogin = new adminLogin;
    administratorLogin -> show();
}
