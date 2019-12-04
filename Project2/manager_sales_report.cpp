#include "manager_sales_report.h"
#include "ui_manager_sales_report.h"

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
