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
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("select purchaseDate, id, productName, price, purchaseQty, status from salesReport where day='"+ui->comboBox->currentText()+"'");

    if(qry->exec())
    {
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableView->horizontalHeader()->sortIndicatorChanged(-1, Qt::AscendingOrder);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
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

void admin_item_database::on_comboBox_currentIndexChanged()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("select purchaseDate, id, productName, price, purchaseQty, status from salesReport where day='"+ui->comboBox->currentText()+"'");

    if(qry->exec())
    {
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}
