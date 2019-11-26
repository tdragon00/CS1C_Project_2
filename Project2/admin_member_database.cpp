#include "admin_member_database.h"
#include "ui_admin_member_database.h"
#include "adminlogin.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admincreate.h"
#include "adminlogin.h"
#include "managerlogin.h"
#include "accountconfirm.h"
#include "createcheck.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>


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
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("Select name,memberNum, status, expDate from customers");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();
}
