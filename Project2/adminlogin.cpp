#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "mainwindow.h"
#include "admin_member_database.h"
//#include "viewdatabase.h"
//#include "employeedata.h"

adminLogin::adminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminLogin)
{
    ui->setupUi(this);
}

adminLogin::~adminLogin()
{
    delete ui;
}

void adminLogin::on_backLogin_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}

//void adminLogin::on_pushButton_clicked()
//{
//    viewDatabase database;
//    database.setModal(true);
//    database.exec();
//}

//void adminLogin::on_pushButton_2_clicked()
//{
//    employeeData employee;
//    employee.setModal(true);
//    employee.exec();
//}




void adminLogin::on_MemberListButton_clicked()
{
hide();
Admin_Member_Database *admin_member_database =new Admin_Member_Database();
admin_member_database->show();

}
