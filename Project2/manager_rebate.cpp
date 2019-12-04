#include "manager_rebate.h"
#include "ui_manager_rebate.h"

#include "managerlogin.h"

manager_rebate::manager_rebate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager_rebate)
{
    ui->setupUi(this);
}

manager_rebate::~manager_rebate()
{
    delete ui;
}

void manager_rebate::on_returnButton_clicked()
{
    hide();
    managerLogin *managerALogin = new managerLogin;
    managerALogin -> show();
}
