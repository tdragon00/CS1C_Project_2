#ifndef TOTALPURCHASES_H
#define TOTALPURCHASES_H

#include <QDialog>
#include "mainwindow.h"

class totalPurchasesData;

class totalPurchases
{
public:
    MainWindow conn;
    totalPurchases();
    totalPurchases(const totalPurchases &);
    totalPurchases &operator=(const totalPurchases &);
    ~totalPurchases();

private:
    QSharedDataPointer<totalPurchasesData> data;
};

#endif // TOTALPURCHASES_H
