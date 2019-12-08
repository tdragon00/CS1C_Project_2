#include "manager_item_database.h"
#include "ui_manager_item_database.h"

manager_item_database::manager_item_database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager_item_database)
{
    ui->setupUi(this);

    if (!conn.connOpen())
        ui->statusLine->setText("Failed to open the database");
    else
        ui->statusLine->setText("Database Connected...");
}

manager_item_database::~manager_item_database()
{
    delete ui;
}
