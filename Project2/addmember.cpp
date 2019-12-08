#include "addmember.h"
#include "ui_addmember.h"
#include <QRandomGenerator>

addMember::addMember(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addMember)
{
    ui->setupUi(this);

    int idGenerator = qrand()% 89999 + 10000;
    ui->idEdit->setText(QString::number(idGenerator));
}

addMember::~addMember()
{
    delete ui;
}


void addMember::on_addButton_clicked()
{
    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->exec("insert into customers (name, memberNum, status, expDate)"
              "values ('"+ui->nameEdit->text()+"','"+ui->idEdit->text()+"','"+ui->statusEdit->currentText()+"','"+ui->dateEdit->text()+"')");
    if(qry->exec())
    {
        hide();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void addMember::on_cancelButton_clicked()
{
    hide();
}
