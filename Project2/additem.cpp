#include "additem.h"
#include "ui_additem.h"

addItem::addItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addItem)
{
    ui->setupUi(this);
}

addItem::~addItem()
{
    delete ui;
}

void addItem::on_addButton_clicked()
{
    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    if(qry->exec("insert into items (name, price, qty, totalRevenue, qtySold )"
                       "values ('"+ui->nameEdit->text()+"','"+ui->priceEdit->text()+"','"+ui->qtyEdit->text()+"', 0.00, 0)"))
    {
        hide();
    }
    else
    {
        qDebug() << "ERROR";
    }
}

void addItem::on_cancelButton_clicked()
{
    hide();
}
