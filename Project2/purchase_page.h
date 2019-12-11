#ifndef PURCHASE_PAGE_H
#define PURCHASE_PAGE_H

#include <QDialog>
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QSignalMapper>
#include <QMessageBox>
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

    void Refresh();                                         // DONE
    void Load_Customer_Boxes();                             // DONE
    void Load_Item_Boxes();

private slots:

    void on_Return_Button_clicked();
    void on_loadButton_clicked();                                   // DONE
    void on_Item_Combo_Box_currentIndexChanged();                   // DONE
    void on_Customer_Combo_Box_currentIndexChanged();               // DONE
    void on_Item_Count_Selector_valueChanged(int arg1);             // DONE
    void on_Date_Selector_userDateChanged(const QDate &date);       // DONE
    void on_Purchase_Button_clicked();                              // DONE

private:
    Ui::Purchase_Page *ui;
};

#endif // PURCHASE_PAGE_H
