#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "mainwindow.h"
#include "admin_member_database.h"
#include <QFile>
#include <QTextStream>
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

void adminLogin::on_pushButton_clicked()
{
    qDebug() << "Extracting Customers from .txt to .db";
    QString name;
    QString memberNum;
    QString status;
    QString expDate;

    QFile file(":/textfiles/Resource Stuff/Database textfiles/warehouse shoppers.txt");
    if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
    {
        qDebug() << "Could not Read File";
    }
    QTextStream in(&file);

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery qry;

    while(!in.atEnd())
    {
        name = in.readLine();
        memberNum = in.readLine();
        status = in.readLine();
        expDate = in.readLine();

        qDebug() << "Inserting Customer " << name;

        qry.exec("insert into customers (name, memberNum, status, expDate)"
                    "values ('"+name+"','"+memberNum+"','"+status+"','"+expDate+"')");
    }
    conn.connClose();
}
