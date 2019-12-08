#ifndef ADMIN_SALES_REPORT_H
#define ADMIN_SALES_REPORT_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class admin_sales_report;
}

class admin_sales_report : public QWidget
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit admin_sales_report(QWidget *parent = nullptr);
    ~admin_sales_report();

    void refreshDb();

private slots:
    void on_returnButton_clicked();

    void on_dateFilter_currentIndexChanged();

    void on_memberFilter_currentIndexChanged();

    void on_checkMemberFilter_stateChanged();

    void on_checkDateFilter_stateChanged();

    void on_originalSort_clicked();

    void on_idAscSort_clicked();

    void on_idDescSort_clicked();

    void on_checkItemFilter_stateChanged();

    void on_itemFilter_currentIndexChanged();

private:
    Ui::admin_sales_report *ui;
};

#endif // ADMIN_SALES_REPORT_H
