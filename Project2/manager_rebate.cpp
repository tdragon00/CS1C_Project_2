#include "manager_rebate.h"
#include "ui_manager_rebate.h"

#include "managerlogin.h"

manager_rebate::manager_rebate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager_rebate)
{
    ui->setupUi(this);
    on_loadButton_clicked();
}

manager_rebate::~manager_rebate()
{
    delete ui;
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


    //FOR LOADING THE EXECUTIVE TO REGULAR MEMBER LIST
    QSqlQueryModel * modal2 = new QSqlQueryModel();
    QSqlQuery* qry2 = new QSqlQuery(conn.mydb);

    qry2->prepare("SELECT name, memberNum, totalRebate from customers "
                           "WHERE totalRebate < 120 AND totalRebate > 0 AND status='Executive' "
                           "ORDER BY memberNum ASC" ) ;

    qry2->exec();

    modal2->setQuery(*qry2);
    modal2->setHeaderData(0, Qt::Horizontal, tr("Name"));
    modal2->setHeaderData(1, Qt::Horizontal, tr("Member Number"));
    modal2->setHeaderData(2, Qt::Horizontal, tr("Total Rebate"));

    ui->EtoRtable->setModel(modal2);
    ui->EtoRtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    //FOR LOADING REGULAR TO EXECUTIVE MEMBER LIST
    QSqlQueryModel * modal3 = new QSqlQueryModel();
    QSqlQuery* qry3 = new QSqlQuery(conn.mydb);

    qry3->prepare("SELECT name, memberNum, totalRebate from customers "
                            "WHERE totalRebate > 120 AND status='Regular' "
                            "ORDER BY memberNum ASC" ) ;

    qry3->exec();

    modal3->setQuery(*qry3);
    modal3->setHeaderData(0, Qt::Horizontal, tr("Name"));
    modal3->setHeaderData(1, Qt::Horizontal, tr("Member Number"));
    modal3->setHeaderData(2, Qt::Horizontal, tr("Potential Total Rebate"));

    ui->RtoEtable->setModel(modal3);
    ui->RtoEtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    conn.connClose();
}
