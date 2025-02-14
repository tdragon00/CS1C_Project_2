#include "managerlogin.h"
#include "adminlogin.h"
#include "mainwindow.h"
#include "ui_managerlogin.h"
#include <QUrl>
#include <QDesktopServices>
#include <QMessageBox>
#include "manager_member_database.h"
#include "manager_item_database.h"


managerLogin::managerLogin( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managerLogin)
{
    ui->setupUi(this);
    if (!conn.connOpen())
        ui->statusLine->setText("Failed to open the database");
    else
        ui->statusLine->setText("Database Connected...");

//    ui->lineEdit->setText(username);
}

managerLogin::~managerLogin()
{
    delete ui;
}

void managerLogin::on_backLogin_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}



void managerLogin::on_Member_Data_clicked()
{

    hide();
    manager_member_database *Manager_member_database =new manager_member_database();
    Manager_member_database->show();
}

void managerLogin::on_Item_Data_clicked()
{
    hide();
    manager_item_database *Manager_Item_database =new manager_item_database();
    Manager_Item_database->show();
}
