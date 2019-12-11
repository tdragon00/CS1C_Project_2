#ifndef PURCHASE_PAGE_H
#define PURCHASE_PAGE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Purchase_Page;
}

class Purchase_Page : public QDialog
{
    Q_OBJECT

public:
    MainWindow conn;
    explicit Purchase_Page(QWidget *parent = nullptr);
    ~Purchase_Page();

//    void Setup_Boxes();
    void Refresh();

    void Load_Customer_Boxes();

private slots:
    void on_Return_Button_clicked();
    void on_loadButton_clicked();


    void on_Customer_Combo_Box_currentIndexChanged();

private:
    Ui::Purchase_Page *ui;
};

#endif // PURCHASE_PAGE_H
