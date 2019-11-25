#include "admin_member_database.h"
#include "ui_admin_member_database.h"
#include "adminlogin.h"
#include "mainwindow.h"
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QFileInfo>
#include <QKeyEvent>


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

void Admin_Member_Database::on_pushButton_clicked()
{
    hide();
    adminLogin *administratorLogin = new adminLogin;
    administratorLogin -> show();
}


void Admin_Member_Database::on_pushButton_2_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();
    MainWindow conn;
    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
qry->prepare("select name, id, status, expDay, expMonth from customers ExpYear ");
//qry->prepare("Select last, first, email, phone from customers where rank = '1' order by last ASC");


    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();
}
