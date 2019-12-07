#include "manager_sales_report.h"
#include "ui_manager_sales_report.h"
#include "managerlogin.h"

Manager_Sales_Report::Manager_Sales_Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manager_Sales_Report)
{
    ui->setupUi(this);
}

Manager_Sales_Report::~Manager_Sales_Report()
{
    delete ui;
}

void Manager_Sales_Report::on_return_2_clicked()
{
    hide();
    managerLogin *managerALogin = new managerLogin;
    managerALogin -> show();
}
