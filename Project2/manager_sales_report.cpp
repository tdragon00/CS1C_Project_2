#include "manager_sales_report.h"
#include "ui_manager_sales_report.h"
#include "managerlogin.h"

Manager_Sales_Report::Manager_Sales_Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manager_Sales_Report)
{
    ui->setupUi(this);
    if (!conn.connOpen())
        ui->statusLine->setText("Failed to open the database");
    else
        ui->statusLine->setText("Database Connected...");
}

Manager_Sales_Report::~Manager_Sales_Report()
{
    delete ui;
}

void Manager_Sales_Report::keyPressEvent(QKeyEvent* pe)
{
if(pe->key() == Qt::Key_Escape) on_return_2_clicked();                   //Enter Key works as input for buttonLogin()
}

void Manager_Sales_Report::on_return_2_clicked()
{
    hide();
    managerLogin *managerALogin = new managerLogin;
    managerALogin -> show();
}
