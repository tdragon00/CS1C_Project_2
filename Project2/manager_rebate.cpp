#include "manager_rebate.h"
#include "ui_manager_rebate.h"

#include "managerlogin.h"

manager_rebate::manager_rebate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager_rebate)
{
    ui->setupUi(this);

    if (!conn.connOpen())
        ui->statusLine->setText("Failed to open the database");
    else
        ui->statusLine->setText("Database Connected...");

    on_loadButton_clicked();
}

manager_rebate::~manager_rebate()
{
    delete ui;
}

void manager_rebate::keyPressEvent(QKeyEvent* pe)
{
if(pe->key() == Qt::Key_Escape) on_returnButton_clicked();
}

void manager_rebate::on_returnButton_clicked()
{
    hide();
    managerLogin *managerALogin = new managerLogin;
    managerALogin -> show();
}

void manager_rebate::on_loadButton_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    //FOR LOADING THE EXECUTIVE MEMBER LIST
    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("SELECT name, memberNum, status, totalRebate from customers "
                           "WHERE status='Executive' "
                           "ORDER BY memberNum ASC" ) ;

    qry->exec();

    modal->setQuery(*qry);
    modal->setHeaderData(0, Qt::Horizontal, tr("Name"));
    modal->setHeaderData(1, Qt::Horizontal, tr("Member Number"));
    modal->setHeaderData(2, Qt::Horizontal, tr("Membership"));
    modal->setHeaderData(3, Qt::Horizontal, tr("Total Rebate"));

    ui->executiveTable->setModel(modal);
    ui->executiveTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    conn.connClose();
}
