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
    {
        ui->setupUi(this);
        MainWindow conn;
        QSqlQueryModel * modal = new QSqlQueryModel();

        conn.connOpen();
        QSqlQuery* qry = new QSqlQuery(conn.mydb);

        if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
        {
            qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                         "FROM salesReport "
                         "INNER JOIN customers ON salesReport.id=customers.memberNum "
                         "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
        }
        else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
        {
            ui->comboBox->setEnabled(false);
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
                         "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"'");
        }
        else
        {
            ui->memberFilter->setEnabled(false);
            ui->comboBox->setEnabled(false);
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
            ui->tableView->setModel(modal);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        else
        {
            qDebug() << "ERROR";
        }
        conn.connClose();
    }
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
    qry->prepare("select purchaseDate, id, productName, price, purchaseQty, status from salesReport where purchaseDate='"+ui->comboBox->currentText()+"'");
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        ui->comboBox->setEnabled(false);
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
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"'");
    }
    else
    {
        ui->memberFilter->setEnabled(false);
        ui->comboBox->setEnabled(false);
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
        ui->tableView->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_item_database::on_memberFilter_currentIndexChanged()
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
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
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
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"'");
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
        ui->tableView->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_item_database::on_checkMemberFilter_stateChanged()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where saleasReport.purchaseDate='"+ui->comboBox->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        ui->memberFilter->setEnabled(true);
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
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"'");
    }
    else
    {
        ui->memberFilter->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum");
    }
\
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
        ui->tableView->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_item_database::on_checkDateFilter_stateChanged()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        ui->comboBox->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        ui->comboBox->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        ui->comboBox->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"'");
    }
    else
    {
        ui->comboBox->setEnabled(false);
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
        ui->tableView->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_item_database::on_pushButton_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        ui->comboBox->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        ui->comboBox->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        ui->comboBox->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"' "
                     "ORDER BY salesReport.id ASC");
    }
    else
    {
        ui->comboBox->setEnabled(false);
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
        ui->tableView->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_item_database::on_pushButton_2_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        ui->comboBox->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        ui->comboBox->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        ui->comboBox->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"' "
                     "ORDER BY salesReport.id DESC");
    }
    else
    {
        ui->comboBox->setEnabled(false);
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
        ui->tableView->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_item_database::on_pushButton_3_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        ui->comboBox->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        ui->comboBox->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        ui->comboBox->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"'");
    }
    else
    {
        ui->comboBox->setEnabled(false);
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
        ui->tableView->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}

void admin_item_database::on_checkMemberFilter_stateChanged(int arg1)
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == true)
    {
        ui->comboBox->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"' and customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == false && ui->checkMemberFilter->isChecked() == true)
    {
        ui->comboBox->setEnabled(false);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where customers.name='"+ui->memberFilter->currentText()+"'");
    }
    else if(ui->checkDateFilter->isChecked() == true && ui->checkMemberFilter->isChecked() == false)
    {
        ui->comboBox->setEnabled(true);
        qry->prepare("SELECT salesReport.purchaseDate, customers.name, salesReport.id, salesReport.productName, salesReport.price, salesReport.purchaseQty, salesReport.status "
                     "FROM salesReport "
                     "INNER JOIN customers ON salesReport.id=customers.memberNum "
                     "where salesReport.purchaseDate='"+ui->comboBox->currentText()+"'");
    }
    else
    {
        ui->comboBox->setEnabled(false);
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
        ui->tableView->setModel(modal);
    }
    else
    {
        qDebug() << "ERROR";
    }
    conn.connClose();
}
