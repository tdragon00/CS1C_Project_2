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

    if (!conn.connOpen())
        ui->statusLine->setText("Failed to open the database");
    else
        ui->statusLine->setText("Database Connected...");
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



void manager_member_database::on_monthSelect_currentIndexChanged()
{
    QString month = ui->monthSelect->currentText();
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
    ui->tableView_2->setModel(modal);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
}

void manager_member_database::on_searchButton_clicked()
{
    QString keyTerm = ui->searchBar->text();

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
    ui->tableView_3->setModel(modal);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
}




void manager_member_database::on_tableView_2_activated(const QModelIndex &index)
{
    QString selected = ui->tableView_2->model()->data(index).toString();
    QString status;
    QString renewalString;
    double rebate;
    double renewal;

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
            status = db.value(2).toString();
            if(status == "Regular")
            {
                ui->costLine->setText("$65");
                ui->rebateLine->setText("$0");
                ui->renewalCost->setText("$65");
            }
            else if(status == "Executive")
            {
                ui->costLine->setText("$120");
                ui->rebateLine->setText(db.value(5).toString());
                rebate = db.value(5).toDouble();

                if(rebate == 0)
                {
                    ui->renewalCost->setText("$120");
                }
                else if((120-rebate) <= 0)
                {
                    ui->renewalCost->setText("$0");
                }
                else
                {
                    renewal = 120-rebate;
                    renewalString = QString::number(renewal);
                    ui->renewalCost->setText(renewalString);
                }
            }
            else
            {
                ui->costLine->setText("Error");
                ui->rebateLine->setText("Error");
                ui->renewalCost->setText("Error");
            }
        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}
