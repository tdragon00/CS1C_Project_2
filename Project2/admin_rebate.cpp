#include "admin_rebate.h"
#include "ui_admin_rebate.h"

#include "adminlogin.h"

admin_rebate::admin_rebate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_rebate)
{
    ui->setupUi(this);
    on_loadButton_clicked();
}

admin_rebate::~admin_rebate()
{
    delete ui;
}

//return to admin login page
void admin_rebate::on_returnButton_clicked()
{
    hide();
    adminLogin *administratorLogin = new adminLogin;
    administratorLogin -> show();
}

void admin_rebate::on_loadButton_clicked()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();
    QString statusString = "Executive";

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
