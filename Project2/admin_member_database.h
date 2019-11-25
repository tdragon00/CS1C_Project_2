#ifndef ADMIN_MEMBER_DATABASE_H
#define ADMIN_MEMBER_DATABASE_H

#include <QDialog>
#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QFileInfo>
#include <QKeyEvent>

namespace Ui {
class Admin_Member_Database;
}

class Admin_Member_Database : public QDialog
{
    Q_OBJECT

public:
    explicit Admin_Member_Database(QWidget *parent = nullptr);
    ~Admin_Member_Database();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Admin_Member_Database *ui;
};

#endif // ADMIN_MEMBER_DATABASE_H
