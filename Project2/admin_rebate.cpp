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

//Function for when clicking on a name the info will come up on the right side for changing the membership
void admin_rebate::on_EtoRtable_activated(const QModelIndex &index)
{
    QString selected = ui->EtoRtable->model()->data(index).toString();
    QString changeMembership;
    MainWindow conn;

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("SELECT * from customers WHERE memberNum='"+selected+"' OR name='"+selected+"'");

    if (db.exec())
    {
        while(db.next())
        {
            ui->nameLineEdit->setText(db.value(0).toString());
            ui->currentLineEdit->setText(db.value(2).toString());

            if(db.value(2).toString() == "Regular")
                changeMembership = "Executive";
            else
                changeMembership = "Regular";

            ui->changeTypeLineEdit->setText(changeMembership);
        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void admin_rebate::on_RtoEtable_activated(const QModelIndex &index)
{
    QString selected = ui->RtoEtable->model()->data(index).toString();
    QString changeMembership;
    MainWindow conn;

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("SELECT * from customers WHERE memberNum='"+selected+"' OR name='"+selected+"'");

    if (db.exec())
    {
        while(db.next())
        {
            ui->nameLineEdit->setText(db.value(0).toString());
            ui->currentLineEdit->setText(db.value(2).toString());

            if(db.value(2).toString() == "Regular")
                changeMembership = "Executive";
            else
                changeMembership = "Regular";

            ui->changeTypeLineEdit->setText(changeMembership);
        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }
}
