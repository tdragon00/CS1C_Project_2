#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "mainwindow.h"
#include "admin_member_database.h"
#include <QFile>
#include <QMessageBox>
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

void adminLogin::on_MemberListButton_clicked()
{
    hide();
    Admin_Member_Database *admin_member_database =new Admin_Member_Database();
    admin_member_database->show();
}

void adminLogin::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Alert ! ! ! ");
    msgBox.setInformativeText("Are you sure you want to factory reset " + ui->dbBox->currentText() + " Database?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    switch (ret)
    {
      case QMessageBox::Yes:
          {
            if (!conn.connOpen())
            {
                qDebug() << "Failed To Open the Database";
            }
            conn.connOpen();
            QSqlQuery db;

            if(ui->dbBox->currentText() == "Customers")
            {//Refreshing Customer db
                qDebug() << "Begining extraction for cusomters from .txt to .db";
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

                qDebug() << "Deleting cusomter db";
                db.exec("delete from customers");

                while(!in.atEnd())
                {
                    name = in.readLine();
                    memberNum = in.readLine();
                    status = in.readLine();
                    expDate = in.readLine();

                    qDebug() << "Inserting Customer " << name;

                    db.exec("insert into customers (name, memberNum, status, expDate)"
                            "values ('"+name+"','"+memberNum+"','"+status+"','"+expDate+"')");
                }
            }
            else if(ui->dbBox->currentText() == "Items")
            {

            }
            else if(ui->dbBox->currentText() == "Sales Report")
            {
                {//Refreshing Day 1 Sales Report db
                    qDebug() << "Begining extraction for Day 1 sales report from .txt to .db";
                    QString purchaseDate;
                    QString id;
                    QString productName;
                    QString price;
                    QString purchaseQty;
                    QString status;

                    QFile file(":/textfiles/Resource Stuff/Database textfiles/day1.txt");
                    if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
                    {
                        qDebug() << "Could not Read File";
                    }
                    QTextStream in(&file);

                    qDebug() << "Deleting salesReport db";
                    db.exec("delete from salesReport");

                    while(!in.atEnd())
                    {
                        purchaseDate = in.readLine();
                        id = in.readLine();
                        productName = in.readLine();
                        price = in.readLine();
                        purchaseQty = in.readLine();
                        status = in.readLine();

                        qDebug() << "Inserting purchase of " << productName << " for customer " << id;

                        db.exec("insert into salesReport (purchaseDate, id, productName, price, purchaseQty, status, day)"
                                "values ('"+purchaseDate+"','"+id+"','"+productName+"','"+price+"','"+purchaseQty+"','"+status+"','"+"1"+"')");
                    }
                }
                {//Refreshing Day 2 Sales Report db
                    qDebug() << "Begining extraction for Day 2 sales report from .txt to .db";
                    QString purchaseDate;
                    QString id;
                    QString productName;
                    QString price;
                    QString purchaseQty;
                    QString status;

                    QFile file(":/textfiles/Resource Stuff/Database textfiles/day2.txt");
                    if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
                    {
                        qDebug() << "Could not Read File";
                    }
                    QTextStream in(&file);

                    while(!in.atEnd())
                    {
                        purchaseDate = in.readLine();
                        id = in.readLine();
                        productName = in.readLine();
                        price = in.readLine();
                        purchaseQty = in.readLine();
                        status = in.readLine();

                        qDebug() << "Inserting purchase of " << productName << " for customer " << id;

                        db.exec("insert into salesReport (purchaseDate, id, productName, price, purchaseQty, status, day)"
                                "values ('"+purchaseDate+"','"+id+"','"+productName+"','"+price+"','"+purchaseQty+"','"+status+"','"+"2"+"')");
                    }
                }
                {//Refreshing Day 3 Sales Report db
                    qDebug() << "Begining extraction for Day 3 sales report from .txt to .db";
                    QString purchaseDate;
                    QString id;
                    QString productName;
                    QString price;
                    QString purchaseQty;
                    QString status;

                    QFile file(":/textfiles/Resource Stuff/Database textfiles/day3.txt");
                    if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
                    {
                        qDebug() << "Could not Read File";
                    }
                    QTextStream in(&file);

                    while(!in.atEnd())
                    {
                        purchaseDate = in.readLine();
                        id = in.readLine();
                        productName = in.readLine();
                        price = in.readLine();
                        purchaseQty = in.readLine();
                        status = in.readLine();

                        qDebug() << "Inserting purchase of " << productName << " for customer " << id;

                        db.exec("insert into salesReport (purchaseDate, id, productName, price, purchaseQty, status, day)"
                                "values ('"+purchaseDate+"','"+id+"','"+productName+"','"+price+"','"+purchaseQty+"','"+status+"','"+"3"+"')");
                    }
                }
                {//Refreshing Day 4 Sales Report db
                    qDebug() << "Begining extraction for Day 4 sales report from .txt to .db";
                    QString purchaseDate;
                    QString id;
                    QString productName;
                    QString price;
                    QString purchaseQty;
                    QString status;

                    QFile file(":/textfiles/Resource Stuff/Database textfiles/day4.txt");
                    if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
                    {
                        qDebug() << "Could not Read File";
                    }
                    QTextStream in(&file);

                    while(!in.atEnd())
                    {
                        purchaseDate = in.readLine();
                        id = in.readLine();
                        productName = in.readLine();
                        price = in.readLine();
                        purchaseQty = in.readLine();
                        status = in.readLine();

                        qDebug() << "Inserting purchase of " << productName << " for customer " << id;

                        db.exec("insert into salesReport (purchaseDate, id, productName, price, purchaseQty, status, day)"
                                "values ('"+purchaseDate+"','"+id+"','"+productName+"','"+price+"','"+purchaseQty+"','"+status+"','"+"4"+"')");
                    }
                }
                {//Refreshing Day 5 Sales Report db
                    qDebug() << "Begining extraction for Day 5 sales report from .txt to .db";
                    QString purchaseDate;
                    QString id;
                    QString productName;
                    QString price;
                    QString purchaseQty;
                    QString status;

                    QFile file(":/textfiles/Resource Stuff/Database textfiles/day5.txt");
                    if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
                    {
                        qDebug() << "Could not Read File";
                    }
                    QTextStream in(&file);

                    while(!in.atEnd())
                    {
                        purchaseDate = in.readLine();
                        id = in.readLine();
                        productName = in.readLine();
                        price = in.readLine();
                        purchaseQty = in.readLine();
                        status = in.readLine();

                        qDebug() << "Inserting purchase of " << productName << " for customer " << id;

                        db.exec("insert into salesReport (purchaseDate, id, productName, price, purchaseQty, status, day)"
                                "values ('"+purchaseDate+"','"+id+"','"+productName+"','"+price+"','"+purchaseQty+"','"+status+"','"+"5"+"')");
                    }
                }
                {//Refreshing Day 6 Sales Report db
                    qDebug() << "Begining extraction for Day 6 sales report from .txt to .db";
                    QString purchaseDate;
                    QString id;
                    QString productName;
                    QString price;
                    QString purchaseQty;
                    QString status;

                    QFile file(":/textfiles/Resource Stuff/Database textfiles/day6.txt");
                    if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
                    {
                        qDebug() << "Could not Read File";
                    }
                    QTextStream in(&file);

                    while(!in.atEnd())
                    {
                        purchaseDate = in.readLine();
                        id = in.readLine();
                        productName = in.readLine();
                        price = in.readLine();
                        purchaseQty = in.readLine();
                        status = in.readLine();

                        qDebug() << "Inserting purchase of " << productName << " for customer " << id;

                        db.exec("insert into salesReport (purchaseDate, id, productName, price, purchaseQty, status, day)"
                                "values ('"+purchaseDate+"','"+id+"','"+productName+"','"+price+"','"+purchaseQty+"','"+status+"','"+"6"+"')");
                    }
                }
                {//Refreshing Day 7 Sales Report db
                    qDebug() << "Begining extraction for Day 7 sales report from .txt to .db";
                    QString purchaseDate;
                    QString id;
                    QString productName;
                    QString price;
                    QString purchaseQty;
                    QString status;

                    QFile file(":/textfiles/Resource Stuff/Database textfiles/day7.txt");
                    if(!file.open(QIODevice::ReadOnly  | QIODevice::Text))
                    {
                        qDebug() << "Could not Read File";
                    }
                    QTextStream in(&file);

                    while(!in.atEnd())
                    {
                        purchaseDate = in.readLine();
                        id = in.readLine();
                        productName = in.readLine();
                        price = in.readLine();
                        purchaseQty = in.readLine();
                        status = in.readLine();

                        qDebug() << "Inserting purchase of " << productName << " for customer " << id;

                        db.exec("insert into salesReport (purchaseDate, id, productName, price, purchaseQty, status, day)"
                                "values ('"+purchaseDate+"','"+id+"','"+productName+"','"+price+"','"+purchaseQty+"','"+status+"','"+"7"+"')");

                    }
                }

            }

            conn.connClose();
          }
           msgBox.setText("Success ! ! ! ");
           msgBox.setInformativeText(ui->dbBox->currentText()+" Database has been restored.");
           msgBox.setStandardButtons(QMessageBox::Ok);
           msgBox.exec();
          break;
      case QMessageBox::No:
          break;
      default:
          break;
    }
}

void adminLogin::on_comboBox_currentIndexChanged(const QString &arg1)
{

}
