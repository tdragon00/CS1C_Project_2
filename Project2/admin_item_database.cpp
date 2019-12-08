#include "admin_item_database.h"
#include "ui_admin_item_database.h"

admin_item_database::admin_item_database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin_item_database)
{
    ui->setupUi(this);
<<<<<<< HEAD

    if (!conn.connOpen())
        ui->statusLine->setText("Failed to open the database");
    else
        ui->statusLine->setText("Database Connected...");
=======
>>>>>>> Lamson
}

admin_item_database::~admin_item_database()
{
    delete ui;
}
<<<<<<< HEAD

void admin_item_database::on_returnButton_clicked()
{
    hide();
    adminLogin *administratorLogin = new adminLogin;
    administratorLogin -> show();
}
=======
>>>>>>> Lamson
