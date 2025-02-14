#include "admincreate.h"
#include "ui_admincreate.h"
#include "accountconfirm.h"
#include "mainwindow.h"
#include <QTextStream>
#include <QMessageBox>

adminCreate::adminCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminCreate)
{
    ui->setupUi(this);
    if (!conn.connOpen())
        ui->Status2->setText("Failed to open the database");
    else
        ui->Status2->setText("Database Conneceted...");
}

adminCreate::~adminCreate()
{
    delete ui;
}

void adminCreate::on_pushButton_clicked()
{
    hide();
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
}

void adminCreate::on_pushConfirm_clicked()
{
    char rank = '1';
    QString firstName = ui->lineFirst->text();
    QString lastName = ui->lineLast->text();
    QString userID = ui->lineUser->text();
    QString password = ui->linePass->text();
    QString passwordCon = ui->linePass2->text();

    if(passwordCon == password)
    {
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
    else
    {
        QMessageBox::warning(this, "Error" , QString("Passwords do no match ! ! !").arg(password).arg(password));
    }
}

void adminCreate::on_checkPassword_stateChanged()
{
    ui->linePass->setEchoMode(ui->checkPassword->checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password );

}
