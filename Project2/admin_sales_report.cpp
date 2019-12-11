#include "admin_sales_report.h"
#include "ui_admin_sales_report.h"
#include "mainwindow.h"
#include "managerlogin.h"

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
        QSqlQueryModel *modal = new QSqlQueryModel();

        conn.connOpen();
        QSqlQuery* qry = new QSqlQuery(conn.mydb);

        ui->memberFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
/*
        QSqlQuery grab;
        grab.exec("SELECT SUM(total) "
                         "FROM salesReport");
        grab.first();
        double TB = grab.value(0).toDouble();

       qDebug() << "AAAAAA" << QString::number(TB);
        ui->lineEdit->setText(QString::number(TB));  */

        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum");

        QSqlQuery statuses;
        statuses.exec("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                      "FROM salesReport "
                      "INNER JOIN customers ON salesReport.id=customers.memberNum "
                      "GROUP BY salesReport.id");

        int sumE = 0;
        int sumR = 0;
        statuses.first();
        do
        {
            if(statuses.value(6) == "Regular")
            {
                sumR++;
            }
            else
            {
                sumE++;
            }
        }
        while(statuses.next());

        ui->lineReg->setText(QString::number(sumR));
        ui->lineEx->setText(QString::number(sumE));


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
        QSqlQueryModel *modal = new QSqlQueryModel();
        conn.connOpen();
        QSqlQuery* qry = new QSqlQuery(conn.mydb);

        qry->prepare("Select name, memberNum from customers");
        if(qry->exec())
        {
            modal->setQuery(*qry);
            ui->memberTable->setModel(modal);
            ui->memberFilter->setModel(modal);
            ui->memberTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        else
        {
            qDebug() << "ERROR";
        }
        conn.connClose();
    }
    {
        QSqlQueryModel *modal = new QSqlQueryModel();
        conn.connOpen();
        QSqlQuery* qry = new QSqlQuery(conn.mydb);

        qry->prepare("Select name from items");
        if(qry->exec())
        {
            modal->setQuery(*qry);
            ui->itemFilter->setModel(modal);
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

void admin_sales_report::keyPressEvent(QKeyEvent* pe)
{
if(pe->key() == Qt::Key_Escape) on_returnButton_clicked();                   //Enter Key works as input for buttonLogin()
}

void admin_sales_report::on_returnButton_clicked()
{
    hide();
    if(MainWindow::Is_Admin)
    {
    adminLogin *Login = new adminLogin;
    Login -> show();

    }
    else if(!MainWindow::Is_Admin)
    {
    managerLogin *Login = new managerLogin;
    Login->show();
    }

}

void admin_sales_report::refreshDb()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->itemFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName='"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.productName='"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.status='"+ui->statusFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->itemFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName='"+ui->itemFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.productName='"+ui->itemFilter->currentText()+"'");
    }
    else
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
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

    if(ui->checkDateFilter->isChecked() == true)
    {
        QSqlQuery statuses;
        statuses.prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                         "FROM salesReport "
                         "INNER JOIN customers "
                         "ON salesReport.id=customers.memberNum "
                         "GROUP BY salesReport.id,salesReport.purchaseDate");
        if(!statuses.exec())
        {
            qDebug() << "ERROR";
        }
        int sumE = 0;
        int sumR = 0;
        statuses.first();
        do
 {
            qDebug() << statuses.value(0).toString() << " AND " << ui->dateFilter->currentText();
            if(statuses.value(0).toString() == ui->dateFilter->currentText())
            {
                if(statuses.value(6) == "Regular")
                {
                    sumR++;
                }
                else
                {
                    sumE++;
                }
            }
        } while(statuses.next());

        ui->lineReg->setText(QString::number(sumR));
        ui->lineEx->setText(QString::number(sumE));

        {
            QSqlQuery grab;
            double TB = 0.0;
            grab.exec("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                      "FROM salesReport "
                      "INNER JOIN customers ON salesReport.id=customers.memberNum "
                      "GROUP BY salesReport.productName, salesReport.purchaseDate ");

            grab.first();
            do
            {
                if(grab.value(0).toString() == ui->dateFilter->currentText())
                {
                    TB = TB + grab.value(4).toDouble()*grab.value(5).toDouble();
                }
            }
            while(grab.next());

            TB = TB + TB * 0.0775;

            ui->lineEdit->setText(QString::number(TB));
        }
    }
    else
    {
        QSqlQuery statuses;
        statuses.exec("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                      "FROM salesReport "
                      "INNER JOIN customers ON salesReport.id=customers.memberNum "
                      "GROUP BY salesReport.id");
        int sumE = 0;
        int sumR = 0;
        statuses.first();
        do
        {
            if(statuses.value(6) == "Regular")
            {
                sumR++;
            }
            else
            {
                sumE++;
            }
        }
        while(statuses.next());
        ui->lineReg->setText(QString::number(sumR));
        ui->lineEx->setText(QString::number(sumE));

        {
            QSqlQuery grab;
            grab.exec("SELECT SUM(total) "
                             "FROM salesReport");
            grab.first();
            double TB = grab.value(0).toDouble();

           //qDebug() << "AAAAAA" << QString::number(TB);
            ui->lineEdit->setText(QString::number(TB));
        }
    }

    conn.connClose();
}

void admin_sales_report::on_dateFilter_currentIndexChanged()
{
    refreshDb();
}

void admin_sales_report::on_memberFilter_currentIndexChanged()
{
    refreshDb();
}

void admin_sales_report::on_checkMemberFilter_stateChanged()
{
    refreshDb();
}

void admin_sales_report::on_checkDateFilter_stateChanged()
{
    refreshDb();
}

void admin_sales_report::on_originalSort_clicked()
{
    refreshDb();
}

void admin_sales_report::on_idAscSort_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->itemFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName='"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.productName='"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->itemFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName='"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' "
                      "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.productName='"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
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
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->itemFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName='"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.productName='"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->itemFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName='"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' "
                      "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.productName='"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
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

void admin_sales_report::on_checkItemFilter_stateChanged()
{
    refreshDb();
}

void admin_sales_report::on_itemFilter_currentIndexChanged()
{
    refreshDb();
}

void admin_sales_report::on_statusAscSort_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->itemFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName='"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.productName='"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.status='"+ui->statusFilter->currentText()+"'"
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->itemFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName='"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' "
                      "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.productName='"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.status ASC");
    }
    else
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "ORDER BY salesReport.status ASC");
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

void admin_sales_report::on_statusDescSort_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->itemFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName='"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.productName='"+ui->itemFilter->currentText()+"' and customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.status='"+ui->statusFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->itemFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName='"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and salesReport.productName'"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' "
                      "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(true);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->dateFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true && ui->checkItemFilter->isChecked() == false && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(true);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == false && ui->checkItemFilter->isChecked() == true && ui->checkStatusFilter->isChecked() == false)
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(true);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.productName='"+ui->itemFilter->currentText()+"' "
                     "ORDER BY salesReport.status DESC");
    }
    else
    {
        ui->memberFilter->setEnabled(false);
        ui->itemFilter->setEnabled(false);
        ui->dateFilter->setEnabled(false);
        ui->statusFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "ORDER BY salesReport.status DESC");
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

void admin_sales_report::on_checkStatusFilter_stateChanged()
{
    refreshDb();
}

void admin_sales_report::on_statusFilter_currentIndexChanged()
{
    refreshDb();
}
