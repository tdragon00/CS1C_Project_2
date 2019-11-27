#include "manager_item_database.h"
#include "ui_manager_item_database.h"
#include "managerlogin.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>

manager_item_database::manager_item_database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager_item_database)
{
    ui->setupUi(this);
}

manager_item_database::~manager_item_database()
{
    delete ui;
}

void manager_item_database::on_returnButton_clicked()
{
    hide();
    managerLogin *managerALogin = new managerLogin;
    managerALogin -> show();
}
