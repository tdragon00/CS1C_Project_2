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
        ui->statusLine->setText("Database Conneceted...");

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


