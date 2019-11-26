#include "manager_member_database.h"
#include "ui_manager_member_database.h"
#include "admincreate.h"
#include "adminlogin.h"
#include "managerlogin.h"
#include "accountconfirm.h"
#include "createcheck.h"
#include <QMessageBox>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
manager_member_database::manager_member_database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manager_member_database)
{
    ui->setupUi(this);
}

manager_member_database::~manager_member_database()
{
    delete ui;
}
