#include "createcheck.h"
#include "ui_createcheck.h"

#include "mainwindow.h"
#include "managercreate.h"
#include "admincreate.h"
//#include "employeecreate.h"

#include <QMessageBox>


CreateCheck::CreateCheck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateCheck)
{
    ui->setupUi(this);
}

CreateCheck::~CreateCheck()
{
    delete ui;
}

void CreateCheck::on_typeConfirm_clicked()
{
    if(ui->adminRadio->isChecked())
    {
        hide();
        adminCreate *admin = new adminCreate();
        admin -> show();
    }
    else if(ui->managerRadio->isChecked())
    {
        hide();
        managerCreate *manager = new managerCreate();
        manager -> show();
    }
    else
    {
        QMessageBox::warning(this,"Error", "Type of user must be selected.");
    }
}
