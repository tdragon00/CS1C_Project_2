/** @file Manager_Sales_Report.h
*	@brief Displays a window for the administrator and manager to view the sales report.
*/

#ifndef MANAGER_SALES_REPORT_H
#define MANAGER_SALES_REPORT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Manager_Sales_Report;
}

/**
*	@brief Displays the sales report.
*/
class Manager_Sales_Report : public QDialog
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit Manager_Sales_Report(QWidget *parent = nullptr);
    ~Manager_Sales_Report();

private slots:
    void on_return_2_clicked();

private:
    Ui::Manager_Sales_Report *ui;
};

#endif // MANAGER_SALES_REPORT_H
