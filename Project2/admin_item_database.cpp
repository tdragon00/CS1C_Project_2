#include "admin_item_database.h"
#include "ui_admin_item_database.h"

#include "adminlogin.h"

#include <QMessageBox>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QSortFilterProxyModel>
#include <QAbstractTableModel>

admin_item_database::admin_item_database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_item_database)
{
    ui->setupUi(this);

    if (!conn.connOpen())
        ui->statusLine->setText("Failed to open the database");
    else
        ui->statusLine->setText("Database Connected...");
}

admin_item_database::~admin_item_database()
{
    delete ui;
}

void admin_item_database::on_returnButton_clicked()
{
    hide();
    adminLogin *administratorLogin = new adminLogin;
    administratorLogin -> show();
}


void admin_item_database::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QString name = ui->comboBox->currentText();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("select * from items where name='"+name+"'");

    if (db.exec())
    {
        while(db.next())
        {
            ui->nameEdit->setText(db.value(0).toString());
            ui->priceEdit->setText(db.value(1).toString());
            ui->qtyEdit->setText(db.value(2).toString());
        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void admin_item_database::on_listView_clicked(const QModelIndex &index)
{
    QString name = index.data(Qt::DisplayRole).toString();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("select * from items where name='"+name+"'");

    if (db.exec())
    {
        while(db.next())
        {
            ui->nameEdit->setText(db.value(0).toString());
            ui->priceEdit->setText(db.value(1).toString());
            ui->qtyEdit->setText(db.value(2).toString());
        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void admin_item_database::on_updateButton_clicked()
{
    QString name = ui->nameEdit->text();
    QString price = ui->priceEdit->text();
    QString qty = ui->qtyEdit->text();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("update items set name='"+name+"', price='"+price+"', qty='"+qty+"' where name='"+name+"'");


    if (db.exec())
    {

        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void admin_item_database::on_deleteButton_clicked()
{
    QString name = ui->nameEdit->text();
    qDebug() << "Begining deletion of Item " << name;

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("Delete from items where name='"+name+"'");

    if (db.exec())
    {
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void admin_item_database::on_loadButton_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("Select name,price, qty, totalRevenue, qtySold from items");

    qry->exec();
    modal->setQuery(*qry);
    ui->itemsTable->setModel(modal);
    ui->comboBox->setModel(modal);
    ui->listView->setModel(modal);
    ui->itemsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
}

void admin_item_database::on_itemsTable_activated(const QModelIndex &index)
{
    QString name = ui->itemsTable->model()->data(index).toString();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("select * from items where name='"+name+"'");

    if (db.exec())
    {
        while(db.next())
        {
            ui->nameEdit->setText(db.value(0).toString());
            ui->priceEdit->setText(db.value(1).toString());
            ui->qtyEdit->setText(db.value(2).toString());
        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}
