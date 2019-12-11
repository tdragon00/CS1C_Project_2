#include "admin_member_database.h"
#include "ui_admin_member_database.h"

#include "adminlogin.h"
#include "addmember.h"
#include"QDebug"

#include <QMessageBox>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>



//constructor

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
//destructor
Admin_Member_Database::~Admin_Member_Database()
{
    delete ui;
}

//refreshor
void Admin_Member_Database::refresh()
{


Calc_Total_Purchases();
LoadData();

}

//!calculate purchase total

void Admin_Member_Database::Calc_Total_Purchases()
{
MainWindow conn;
conn.connOpen();

QSqlQuery qry;

//!summing up toalpurchases from customers the db

qry.prepare("SELECT totalPurchases FROM customers");
qry.exec();

//! setting itterator to the front of the values
qry.first();

//! creating a double to store the total purchases
double Grand_Total=0;
do
{
    Grand_Total=Grand_Total+ qry.value(0).toDouble();






}
while (qry.next());
  qDebug()<<"end of loop";

QString QGrand_total= QString::number(Grand_Total);
ui->TotalPurchaseBox->setText(QGrand_total);

}








void Admin_Member_Database::keyPressEvent(QKeyEvent* pe)
{
if(pe->key() == Qt::Key_Escape) on_returnButton_clicked();
}

void Admin_Member_Database::on_returnButton_clicked()
{
    hide();
    adminLogin *administratorLogin = new adminLogin;
    administratorLogin -> show();
}

void Admin_Member_Database::LoadData()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("Select name,memberNum, status, expDate,totalPurchases from customers");

    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->comboBox->setModel(modal);
    ui->listView->setModel(modal);
    conn.connClose();
}

void Admin_Member_Database::on_loadButton_clicked()
{
    //! Triggers a refresh
    refresh();
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
    //! triggers a Refresh
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
    refresh();
}

void Admin_Member_Database::on_listView_clicked(const QModelIndex &index)
{

    //! triggers a refresh


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
    refresh();
}

void Admin_Member_Database::on_pushButton_clicked()
{
    //! does not trigger a refresh it opens up a new window

    addMember *AddMember = new addMember;
    AddMember -> show();
    //LoadData();

}

void Admin_Member_Database::on_monthSelect_2_currentIndexChanged()
{
    QString month = ui->monthSelect_2->currentText();
    QString numMonth;

    if(month == "January")
    {
        numMonth = "01%";
    }
    else if(month == "Feburary")
    {
        numMonth = "02%";
    }
    else if(month == "March")
    {
        numMonth = "03%";
    }
    else if(month == "April")
    {
        numMonth = "04%";
    }
    else if(month == "May")
    {
        numMonth = "05%";
    }
    else if(month == "June")
    {
        numMonth = "06%";
    }
    else if(month == "July")
    {
        numMonth = "07%";
    }
    else if(month == "August")
    {
        numMonth = "08%";
    }
    else if(month == "September")
    {
        numMonth = "09%";
    }
    else if(month == "October")
    {
        numMonth = "10%";
    }
    else if(month == "November")
    {
        numMonth = "11%";
    }
    else if(month == "December")
    {
        numMonth = "12%";
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

    qry.prepare("select * from customers where expDate LIKE '"+numMonth+"' "
                        "ORDER BY expDate");

    qry.exec();
    modal->setQuery(qry);

    modal->setHeaderData(0, Qt::Horizontal, tr("Name"));
    modal->setHeaderData(1, Qt::Horizontal, tr("Member Number"));
    modal->setHeaderData(2, Qt::Horizontal, tr("Membership"));
    modal->setHeaderData(3, Qt::Horizontal, tr("Expiration Date"));
    modal->setHeaderData(4, Qt::Horizontal, tr("Total Purchases"));
    modal->setHeaderData(5, Qt::Horizontal, tr("Total Rebate"));

    ui->tableView_5->setModel(modal);
    ui->tableView_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
}

void Admin_Member_Database::on_searchButton_5_clicked()
{   
    QString keyTerm = ui->searchBar_5->text();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }

    conn.connOpen();

    QSqlQuery qry;
    QSqlQueryModel * modal = new QSqlQueryModel();


    qry.prepare("select * from customers "
                       "WHERE memberNum='"+keyTerm+"' OR (UPPER(name) LIKE UPPER('%"+keyTerm+"%') ) "
                       "ORDER BY name");

    qry.exec();
    modal->setQuery(qry);

    modal->setHeaderData(0, Qt::Horizontal, tr("Name"));
    modal->setHeaderData(1, Qt::Horizontal, tr("Member Number"));
    modal->setHeaderData(2, Qt::Horizontal, tr("Membership"));
    modal->setHeaderData(3, Qt::Horizontal, tr("Expiration Date"));
    modal->setHeaderData(4, Qt::Horizontal, tr("Total Purchases"));
    modal->setHeaderData(5, Qt::Horizontal, tr("Total Rebate"));

    ui->tableView_15->setModel(modal);
    ui->tableView_15->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
}

