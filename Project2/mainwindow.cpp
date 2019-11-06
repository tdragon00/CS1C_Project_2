#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "customerlogin.h"
//#include "secadminlogin.h"
//#include "viewdatabase.h"
#include "admincreate.h"
#include "adminlogin.h"
#include "managerlogin.h"
#include "accountconfirm.h"
#include "createcheck.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("/Users/LamsonBui/Desktop/School/CS1C/Project 2/Project2/BulkClubLogo.png");
    int w = ui->Logo->width();
    int h = ui->Logo->height();
    ui->Logo->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    if (!connOpen())
        ui->Status->setText("Failed to open the database");
    else
        ui->Status->setText("Database Connected...");

}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::keyPressEvent(QKeyEvent* pe)
{
if(pe->key() == Qt::Key_Return) on_pushLogin_clicked();                   //Enter Key works as input for buttonLogin()
}


void MainWindow::on_buttonCreate_clicked()
{
    CreateCheck createCheck;
    createCheck.setModal(true);
    createCheck.exec();
    hide();
}

void MainWindow::on_pushClear_clicked()
{
    this->ui->lineUser->setText("");
    this->ui->linePassword->setText("");
}

void MainWindow::on_pushLogin_clicked()
{
    QString userID = ui->lineUser->text();
    QString password = ui->linePassword->text();

    if (!connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }

    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from userDatabase where userID='"+userID +"' and password='"+password +"' and rank='2'");

    if (qry.exec())
    {
        int count = 0;
        while (qry.next())
        {
            count++;
        }
        if(count ==1)
        {
            QMessageBox::information(this, "Login", "Username and password is correct");
            hide();
            connClose();
            managerLogin *manLogin = new managerLogin(userID);
            manLogin->show();
        }
        else if (count != 1)
        {
            if(qry.exec("select * from userDatabase where userID='"+userID +"' and password='"+password +"' and rank='1'"))
            {
            int count = 0;
            while (qry.next())
            {
                count++;
            }
            if(count ==1)
            {
                QMessageBox::information(this, "Login", "Username and password is correct");
                hide();
                connClose();
                adminLogin *administratorLogin = new adminLogin;
                administratorLogin -> show();
            }
                else
                {
                    QMessageBox::warning(this,"Login", "Username and password is not correct!");
                }
            }
        }
    }
}
