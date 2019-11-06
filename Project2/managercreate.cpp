#include "managercreate.h"
#include "ui_managercreate.h"
#include "accountconfirm.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

managerCreate::managerCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managerCreate)
{
    ui->setupUi(this);
    if (!conn.connOpen())
        ui->Status2->setText("Failed to open the database");
    else
        ui->Status2->setText("Database Conneceted...");
}

managerCreate::~managerCreate()
{
    delete ui;
}

void managerCreate::on_pushButton_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}

void managerCreate::on_pushConfirm_clicked()
{
    char rank = '2';
    QString firstName = ui->lineFirst->text();
    QString lastName = ui->lineLast->text();
    QString userID = ui->lineUser->text();
    QString password = ui->linePass->text();
    QString passwordCon = ui->linePass2->text();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("insert into userDatabase (userID, password, firstName, lastName, rank)"
                "values ('"+userID+"','"+password+"','"+firstName+"','"+lastName+"','"+rank+"')");

    if (qry.exec())
    {
        conn.connClose();
        accountConfirm account;
        account.setModal(true);
        account.exec();
        hide();
    }
    else
    {
        QMessageBox::critical(this,tr("ERROR"),qry.lastError().text());
    }

}
