#include "admin_member_database.h"
#include "ui_admin_member_database.h"

#include "adminlogin.h"
#include "addmember.h"

#include <QMessageBox>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>


Admin_Member_Database::Admin_Member_Database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin_Member_Database)
{
    ui->setupUi(this);

    if (!conn.connOpen())
        ui->statusLine->setText("Failed to open the database");
    else
        ui->statusLine->setText("Database Connected...");

    on_loadButton_clicked();
}

Admin_Member_Database::~Admin_Member_Database()
{
    delete ui;
}

void Admin_Member_Database::on_returnButton_clicked()
{
    hide();
    adminLogin *administratorLogin = new adminLogin;
    administratorLogin -> show();
}

void Admin_Member_Database::on_loadButton_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("Select name,memberNum, status, expDate from customers");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->comboBox->setModel(modal);
    ui->listView->setModel(modal);
    conn.connClose();
}

void Admin_Member_Database::on_comboBox_currentIndexChanged()
{
    QString name = ui->comboBox->currentText();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("select * from customers where name='"+name+"'");

    if (db.exec())
    {
        while(db.next())
        {
            ui->nameEdit->setText(db.value(0).toString());
            ui->memberNumEdit->setText(db.value(1).toString());
            ui->statusEdit->setText(db.value(2).toString());
            ui->expirationEdit->setText(db.value(3).toString());
        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void Admin_Member_Database::on_updateButton_clicked()
{
    QString name = ui->nameEdit->text();
    QString memberNum = ui->memberNumEdit->text();
    QString status = ui->statusEdit->text();
    QString expDate = ui->expirationEdit->text();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("update customers set name='"+name+"', memberNum='"+memberNum+"', status='"+status+"', expDate='"+expDate+"' where memberNum='"+memberNum+"'");


    if (db.exec())
    {

        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void Admin_Member_Database::on_listView_clicked(const QModelIndex &index)
{
    QString name = index.data(Qt::DisplayRole).toString();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("select * from customers where name='"+name+"'");

    if (db.exec())
    {
        while(db.next())
        {
            ui->nameEdit->setText(db.value(0).toString());
            ui->memberNumEdit->setText(db.value(1).toString());
            ui->statusEdit->setText(db.value(2).toString());
            ui->expirationEdit->setText(db.value(3).toString());
        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void Admin_Member_Database::on_tableView_activated(const QModelIndex &index)
{
    QString selected = ui->tableView->model()->data(index).toString();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("select * from customers where memberNum='"+selected+"' or name='"+selected+"'");

    if (db.exec())
    {
        while(db.next())
        {
            ui->nameEdit->setText(db.value(0).toString());
            ui->memberNumEdit->setText(db.value(1).toString());
            ui->statusEdit->setText(db.value(2).toString());
            ui->expirationEdit->setText(db.value(3).toString());
        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void Admin_Member_Database::on_deleteButton_clicked()
{
    QString memberNum = ui->memberNumEdit->text();
    qDebug() << "Begining deletion of Member# " << memberNum;

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("Delete from customers where memberNum='"+memberNum+"'");

    if (db.exec())
    {
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void Admin_Member_Database::on_pushButton_clicked()
{
    addMember *AddMember = new addMember;
    AddMember -> show();
}

void Admin_Member_Database::on_monthSelect_currentIndexChanged()
{
    QString month = ui->monthSelect_2->currentText();
    QString numMonth;

    if(month == "January")
    {
        numMonth = "01";
    }
    else if(month == "Feburary")
    {
        numMonth = "02/";
    }
    else if(month == "March")
    {
        numMonth = "03";
    }
    else if(month == "April")
    {
        numMonth = "04";
    }
    else if(month == "May")
    {
        numMonth = "05";
    }
    else if(month == "June")
    {
        numMonth = "06";
    }
    else if(month == "July")
    {
        numMonth = "07";
    }
    else if(month == "August")
    {
        numMonth = "08";
    }
    else if(month == "September")
    {
        numMonth = "09";
    }
    else if(month == "October")
    {
        numMonth = "10";
    }
    else if(month == "November")
    {
        numMonth = "11";
    }
    else if(month == "December")
    {
        numMonth = "12";
    }
    else
    {
        numMonth = "00";
    }


    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery qry;
    QSqlQueryModel * modal = new QSqlQueryModel();
    qry.prepare("select * from customers where instr(expDate, '"+numMonth+"')");
    qry.exec();
    modal->setQuery(qry);
    ui->tableView_5->setModel(modal);
    ui->tableView_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
}

void Admin_Member_Database::on_searchButton_clicked()
{
    QString keyTerm = ui->searchBar_5->text();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery qry;
    QSqlQueryModel * modal = new QSqlQueryModel();
    qry.prepare("select * from customers where memberNum='"+keyTerm+"' or name='"+keyTerm+"'");
    qry.exec();
    modal->setQuery(qry);
    ui->tableView_15->setModel(modal);
    ui->tableView_15->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
}
