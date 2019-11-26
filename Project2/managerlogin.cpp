<<<<<<< Updated upstream
#include "managerlogin.h"
#include "adminlogin.h"
#include "mainwindow.h"
#include "ui_managerlogin.h"
#include <QUrl>
#include <QDesktopServices>
#include <QMessageBox>


managerLogin::managerLogin( QString userID, QWidget *parent) :
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


=======
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





void managerLogin::on_MemberData_clicked()
{

    hide();
    manager_member_database *Manager_Member_Database =new manager_member_database();
    Manager_Member_Database->show();
}

void managerLogin::on_Item_data_clicked()
{

    hide();
    manager_item_database *Manager_Item_Database =new manager_item_database();
    Manager_Item_Database->show();
}
>>>>>>> Stashed changes
