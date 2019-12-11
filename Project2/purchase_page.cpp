#include "purchase_page.h"
#include "ui_purchase_page.h"
#include "adminlogin.h"
#include "mainwindow.h"
#include "admin_member_database.h"
#include "qsqlquery.h"
#include "qdebug.h"



void Purchase_Page::Load_Customer_Boxes()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("Select name,memberNum, status, expDate,totalPurchases from customers");

    qry->exec();
    modal->setQuery(*qry);
    ui->Customer_Combo_Box->setModel(modal);
    conn.connClose();
}

void Purchase_Page::Load_Item_Boxes()
{
    MainWindow conn;
    QSqlQueryModel * modal = new QSqlQueryModel();

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);

    qry->prepare("Select name, price, qty, totalRevenue, qtySold  from items");

    qry->exec();
    modal->setQuery(*qry);
    ui->Item_Combo_Box->setModel(modal);
    conn.connClose();
}

void Purchase_Page::Refresh()
{
    Load_Customer_Boxes();
    Load_Item_Boxes();
}



//void Purchase_Page::Setup_Boxes()
//{
//        //!this function sets up the combo boxes
//    MainWindow conn;
//    conn.connOpen();
//    //! setting up the qry
//    QSqlQuery customers;
//    QSqlQuery items;



//    //CUSTOMER BOX FILLING

//    //!filling in the customers combo box
//    //! prepping the sql query
//    customers.prepare("SELECT name,memberNum,status FROM customers");
//    customers.exec();
//    customers.first();


//    //! settign iterator to the first result
//    //! while loop to insert customers into the combo box
//    //! creating int counter for the ID of the combo box
//    int i =0;
//    qDebug()<<"before while loop"<<customers.value(0).toString();
//    do
//    {
//        ui->Customer_Combo_Box->insertItem(i,customers.value(0).toString());


//    i++;
//    }while(customers.next());
//    customers.next();
//    qDebug()<<"after while loop"<<customers.value(0).toString();



//    //ITEM BOX FILLING

//    //!filling in the items combo box
//    //! prepping the sql query
//    items.prepare("Select name,price,qty, FROM items");
//    items.exec();
//    items.first();
//    //! settign iterator to the first result
//    //! while loop to insert items into the combo box
//    //! creating int counter for the ID of the combo box
//    int j =0;
//    items.first();
//    do
//    {
//        ui->Item_Combo_Box->insertItem(j,items.value(0).toString());


//    i++;
//    }while(items.next());

//    conn.connClose();
//}





//constructor
Purchase_Page::Purchase_Page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Purchase_Page)
{

ui->setupUi(this);
//Setup_Boxes();

}


//destructor
Purchase_Page::~Purchase_Page()
{
    delete ui;
}

//return button
void Purchase_Page::on_Return_Button_clicked()
{
    //!sends user back to the admin login
 hide();
 adminLogin * Login = new adminLogin;
 Login->show();
}




void Purchase_Page::on_loadButton_clicked()
{
    //! Triggers a refresh
    Refresh();
}


void Purchase_Page::on_Customer_Combo_Box_currentIndexChanged()
{
    QString name = ui->Customer_Combo_Box->currentText();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("select * from customers where name='"+name+"'");

    if (db.exec())
    {
        while(db.next())
        {
            ui->Name_Box->setText(db.value(0).toString());
            ui->Customer_Num_Box->setText(db.value(1).toString());
            ui->Customer_Membership_Box->setText(db.value(2).toString());

        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }

}


void Purchase_Page::on_Item_Combo_Box_currentIndexChanged()
{
    QString name = ui->Item_Combo_Box->currentText();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("select * from items where name='"+name+"'");

    if (db.exec())
    {
        while(db.next())
        {
            ui->Item_Name_Box->setText(db.value(0).toString());
            ui->Item_Cost_Box->setText(db.value(1).toString());
            ui->Item_Inventory_Box->setText(db.value(4).toString());

        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }

}


void Purchase_Page::on_Item_Count_Selector_valueChanged(int arg1)
{
    int newQty = arg1;
    qDebug() << "Spinbox value" << newQty;

    QString name = ui->Item_Combo_Box->currentText();

    if (!conn.connOpen())
    {
        qDebug() << "Failed To Open the Database";
    }
    conn.connOpen();
    QSqlQuery db;
    db.prepare("select * from items where name='"+name+"'");


    if (db.exec())
    {
        while(db.next())
        {
            double price = db.value(1).toDouble();

            qDebug() << "Price of Item: " << price;

            double subtotal = newQty * price;
            double total = subtotal - (subtotal * 0.0775);

            QString Subtotal = QString::number(subtotal);
            QString Total = QString::number(total, 'f', 2);     //DISPLAYS ONLY 2 DECIMAL PLACES

            ui->Subtotal_Box->setText(Subtotal);
            ui->Total_Box->setText(Total);

            QString qty = QString::number(newQty);

        }
        conn.connClose();
    }
    else
    {
        qDebug() << "ERROR";
    }


}

void Purchase_Page::on_Purchase_Button_clicked()
{
    conn.connOpen();
    QSqlQuery db;

    QString purchaseDate = ui->Date_Selector->text();
    QString id = ui->Customer_Num_Box->text();
    QString productName = ui->Item_Combo_Box->currentText();
    QString price = ui->Item_Cost_Box->text();
    QString purchaseQty = QString::number(ui->Item_Count_Selector->value());
    QString status = ui->Customer_Membership_Box->text();
    QString Subtotal = ui->Subtotal_Box->text();
    QString Total = ui->Total_Box->text();

    db.exec("insert into salesReport (purchaseDate, id, productName, price, purchaseQty, day, status, subtotal, total)"
            "values ('"+purchaseDate+"','"+id+"','"+productName+"','"+price+"','"+purchaseQty+"','"+"1"+"','"+status+"', '"+Subtotal+"', '"+Total+"')");
}

void Purchase_Page::on_Date_Selector_userDateChanged(const QDate &date)
{
    QString purchaseDate = date.toString();
}
