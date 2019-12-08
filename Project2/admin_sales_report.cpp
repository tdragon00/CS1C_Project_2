#include "admin_sales_report.h"
#include "ui_admin_sales_report.h"

#include "adminlogin.h"

#include <QMessageBox>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QSortFilterProxyModel>
#include <QAbstractTableModel>

admin_sales_report::admin_sales_report(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_sales_report)
{
    ui->setupUi(this);

    if (!conn.connOpen())
        ui->statusLine->setText("Failed to open the database");
    else
        ui->statusLine->setText("Database Connected...");

    {
        MainWindow conn;
        QSqlQueryModel * modal = new QSqlQueryModel();

        conn.connOpen();
        QSqlQuery* qry = new QSqlQuery(conn.mydb);

        if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
        {
            qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                         "FROM salesReport "
                         "INNER JOIN customers ON salesReport.id=customers.memberNum "
                         "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
        }
        else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
        {
            ui->dateFilter->setEnabled(false);
            qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                         "FROM salesReport "
                         "INNER JOIN customers ON salesReport.id=customers.memberNum "
                         "where customers.name='"+ui->memberFilter->currentText()+"'");
        }
        else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
        {
            ui->memberFilter->setEnabled(false);
            qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                         "FROM salesReport "
                         "INNER JOIN customers ON salesReport.id=customers.memberNum "
                         "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"'");
        }
        else
        {
            ui->memberFilter->setEnabled(false);
            ui->dateFilter->setEnabled(false);
            qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                         "FROM salesReport "
                         "INNER JOIN customers ON salesReport.id=customers.memberNum");
        }
        if(qry->exec())
        {
            modal->setQuery(*qry);
            qDebug() << "Setting Header Titles . . . ";
            modal->setHeaderData(0, Qt::Horizontal, tr("Date"));
            modal->setHeaderData(1, Qt::Horizontal, tr("Name"));
            modal->setHeaderData(2, Qt::Horizontal, tr("ID"));
            modal->setHeaderData(3, Qt::Horizontal, tr("Product"));
            modal->setHeaderData(4, Qt::Horizontal, tr("Price"));
            modal->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
            modal->setHeaderData(6, Qt::Horizontal, tr("Status"));
            qDebug() << "Loading Model into Table . . . ";
            ui->salesRepTable->setModel(modal);
            ui->salesRepTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        else
        {
            qDebug() << "ERROR";
        }
        conn.connClose();
    }
    {
        MainWindow conn;
        QSqlQueryModel * modal = new QSqlQueryModel();

        conn.connOpen();
        QSqlQuery* qry = new QSqlQuery(conn.mydb);

        qry->prepare("Select name, memberNum from customers");
        if(qry->exec())
        {
            modal->setQuery(*qry);
            ui->memberTable->setModel(modal);
            ui->memberFilter->setModel(modal);
            ui->salesRepTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        else
        {
            qDebug() << "ERROR";
        }
        conn.connClose();
    }
}

admin_sales_report::~admin_sales_report()
{
    delete ui;
}

void admin_sales_report::on_returnButton_clicked()
{
    hide();
    adminLogin *administratorLogin = new adminLogin;
    administratorLogin -> show();
}

void admin_sales_report::on_dateFilter_currentIndexChanged()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    qry->prepare("select purchaseDate, id, productName, price, purchaseQty, status from salesReport where purchaseDate='"+ui->dateFilter->currentText()+"'");
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        ui->dateFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"'");
    }
    else
    {
        ui->memberFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum");
    }

    if(qry->exec())
    {
        modal->setQuery(*qry);
        qDebug() << "Setting Header Titles . . . ";
        modal->setHeaderData(0, Qt::Horizontal, tr("Date"));
        modal->setHeaderData(1, Qt::Horizontal, tr("Name"));
        modal->setHeaderData(2, Qt::Horizontal, tr("ID"));
        modal->setHeaderData(3, Qt::Horizontal, tr("Product"));
        modal->setHeaderData(4, Qt::Horizontal, tr("Price"));
        modal->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
        modal->setHeaderData(6, Qt::Horizontal, tr("Status"));
        qDebug() << "Loading Model into Table . . . ";
        ui->salesRepTable->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_sales_report::on_memberFilter_currentIndexChanged()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"'");
    }
    else
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum");
    }

    if(qry->exec())
    {
        modal->setQuery(*qry);
        qDebug() << "Setting Header Titles . . . ";
        modal->setHeaderData(0, Qt::Horizontal, tr("Date"));
        modal->setHeaderData(1, Qt::Horizontal, tr("Name"));
        modal->setHeaderData(2, Qt::Horizontal, tr("ID"));
        modal->setHeaderData(3, Qt::Horizontal, tr("Product"));
        modal->setHeaderData(4, Qt::Horizontal, tr("Price"));
        modal->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
        modal->setHeaderData(6, Qt::Horizontal, tr("Status"));
        qDebug() << "Loading Model into Table . . . ";
        ui->salesRepTable->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_sales_report::on_checkMemberFilter_stateChanged()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"'");
    }
    else
    {
        ui->memberFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum");
    }

    if(qry->exec())
    {
        modal->setQuery(*qry);
        qDebug() << "Setting Header Titles . . . ";
        modal->setHeaderData(0, Qt::Horizontal, tr("Date"));
        modal->setHeaderData(1, Qt::Horizontal, tr("Name"));
        modal->setHeaderData(2, Qt::Horizontal, tr("ID"));
        modal->setHeaderData(3, Qt::Horizontal, tr("Product"));
        modal->setHeaderData(4, Qt::Horizontal, tr("Price"));
        modal->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
        modal->setHeaderData(6, Qt::Horizontal, tr("Status"));
        qDebug() << "Loading Model into Table . . . ";
        ui->salesRepTable->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_sales_report::on_checkDateFilter_stateChanged()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        ui->dateFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        ui->dateFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        ui->dateFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"'");
    }
    else
    {
        ui->dateFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum");
    }

    if(qry->exec())
    {
        modal->setQuery(*qry);
        qDebug() << "Setting Header Titles . . . ";
        modal->setHeaderData(0, Qt::Horizontal, tr("Date"));
        modal->setHeaderData(1, Qt::Horizontal, tr("Name"));
        modal->setHeaderData(2, Qt::Horizontal, tr("ID"));
        modal->setHeaderData(3, Qt::Horizontal, tr("Product"));
        modal->setHeaderData(4, Qt::Horizontal, tr("Price"));
        modal->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
        modal->setHeaderData(6, Qt::Horizontal, tr("Status"));
        qDebug() << "Loading Model into Table . . . ";
        ui->salesRepTable->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_sales_report::on_originalSort_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' ");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' ");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' ");
    }
    else
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum ");
    }

    if(qry->exec())
    {
        modal->setQuery(*qry);
        qDebug() << "Setting Header Titles . . . ";
        modal->setHeaderData(0, Qt::Horizontal, tr("Date"));
        modal->setHeaderData(1, Qt::Horizontal, tr("Name"));
        modal->setHeaderData(2, Qt::Horizontal, tr("ID"));
        modal->setHeaderData(3, Qt::Horizontal, tr("Product"));
        modal->setHeaderData(4, Qt::Horizontal, tr("Price"));
        modal->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
        modal->setHeaderData(6, Qt::Horizontal, tr("Status"));
        qDebug() << "Loading Model into Table . . . ";
        ui->salesRepTable->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_sales_report::on_idAscSort_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "ORDER BY salesReport.id ASC");
    }

    if(qry->exec())
    {
        modal->setQuery(*qry);
        qDebug() << "Setting Header Titles . . . ";
        modal->setHeaderData(0, Qt::Horizontal, tr("Date"));
        modal->setHeaderData(1, Qt::Horizontal, tr("Name"));
        modal->setHeaderData(2, Qt::Horizontal, tr("ID"));
        modal->setHeaderData(3, Qt::Horizontal, tr("Product"));
        modal->setHeaderData(4, Qt::Horizontal, tr("Price"));
        modal->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
        modal->setHeaderData(6, Qt::Horizontal, tr("Status"));
        qDebug() << "Loading Model into Table . . . ";
        ui->salesRepTable->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_sales_report::on_idDescSort_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "ORDER BY salesReport.id DESC");
    }

    if(qry->exec())
    {
        modal->setQuery(*qry);
        qDebug() << "Setting Header Titles . . . ";
        modal->setHeaderData(0, Qt::Horizontal, tr("Date"));
        modal->setHeaderData(1, Qt::Horizontal, tr("Name"));
        modal->setHeaderData(2, Qt::Horizontal, tr("ID"));
        modal->setHeaderData(3, Qt::Horizontal, tr("Product"));
        modal->setHeaderData(4, Qt::Horizontal, tr("Price"));
        modal->setHeaderData(5, Qt::Horizontal, tr("Quantity"));
        modal->setHeaderData(6, Qt::Horizontal, tr("Status"));
        qDebug() << "Loading Model into Table . . . ";
        ui->salesRepTable->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}
