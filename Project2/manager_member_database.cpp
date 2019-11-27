#include "manager_member_database.h"
#include "ui_manager_member_database.h"
#include "managerlogin.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
manager_member_database::manager_member_database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager_member_database)
{
    ui->setupUi(this);
}

manager_member_database::~manager_member_database()
{
    delete ui;
}

void manager_member_database::on_returnButton_clicked()
{
    hide();
    managerLogin *managerALogin = new managerLogin;
    managerALogin -> show();
}

void manager_member_database::on_loadButton_clicked()
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

void manager_member_database::on_comboBox_currentIndexChanged()
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


void manager_member_database::on_listView_clicked(const QModelIndex &index)
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

void manager_member_database::on_tableView_activated(const QModelIndex &index)
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


