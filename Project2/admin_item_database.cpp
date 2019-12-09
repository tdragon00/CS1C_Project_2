#include "admin_item_database.h"
#include "ui_admin_item_database.h"
#include "mainwindow.h"
#include "managerlogin.h"

#include "adminlogin.h"
#include "addItem.h"

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

    on_loadButton_clicked();
    Update_Items();

if(!MainWindow::Is_Admin)
{
    ui->addButton->hide();
    ui->deleteButton->hide();
}


    on_loadButton_clicked();

}
void admin_item_database::Update_Items()
{
    conn.connOpen();






    QSqlQuery qry;
    QSqlQueryModel * modal = new QSqlQueryModel();

    qry.prepare("Select productName,purchaseQty,price FROM salesReport GROUP BY productName");

    qry.exec();
    modal->setQuery(qry);
    ui->test->setModel(modal);
    while (qry.next())
    {
        qry.prepare("UPDATE ")
    }



}

admin_item_database::~admin_item_database()
{
    delete ui;
}

void admin_item_database::keyPressEvent(QKeyEvent* pe)
{
if(pe->key() == Qt::Key_Escape) on_returnButton_clicked();
}

void admin_item_database::on_returnButton_clicked()
{
    hide();
    if(MainWindow::Is_Admin)
    {
    adminLogin *administratorLogin = new adminLogin;
    administratorLogin -> show();
    }
    else if(!MainWindow::Is_Admin)
    {
        managerLogin *ManagerLogin = new managerLogin;
        ManagerLogin->show();
    }

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

    qry->prepare("Select name,price, qty, totalRevenue, qtySold from items "
                          "ORDER BY name ");

    qry->exec();
    modal->setQuery(*qry);

    modal->setHeaderData(0, Qt::Horizontal, tr("Name"));
    modal->setHeaderData(1, Qt::Horizontal, tr("Price"));
    modal->setHeaderData(2, Qt::Horizontal, tr("Quantity"));
    modal->setHeaderData(3, Qt::Horizontal, tr("Total Revenue"));
    modal->setHeaderData(4, Qt::Horizontal, tr("Quantity Sold"));

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

void admin_item_database::on_addButton_clicked()
{
    addItem *AddItem = new addItem;
    AddItem -> show();
}

//When search button is clicked with key word(s)
void admin_item_database::on_searchButton_clicked()
{
    QString keyTerm = ui->searchLineEdit->text();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }

    conn.connOpen();

    QSqlQuery qry;
    QSqlQueryModel * modal = new QSqlQueryModel();


    qry.prepare("SELECT * from items "
                       "WHERE (UPPER(name) LIKE UPPER('%"+keyTerm+"%')) "
                       "ORDER BY name");

    qry.exec();
    modal->setQuery(qry);

    modal->setHeaderData(0, Qt::Horizontal, tr("Name"));
    modal->setHeaderData(1, Qt::Horizontal, tr("Price"));
    modal->setHeaderData(2, Qt::Horizontal, tr("Quantity"));
    modal->setHeaderData(3, Qt::Horizontal, tr("Total Revenue"));
    modal->setHeaderData(4, Qt::Horizontal, tr("Quantity Sold"));

    ui->searchItemTable->setModel(modal);
    ui->searchItemTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    conn.connClose();
}
