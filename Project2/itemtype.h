/** @file itemType.h
*	@brief Contains data in regard to items within the database.
*/

#ifndef ITEMTYPE_H
#define ITEMPE_H

#include <QString>


class itemType
{    
private:
    QString name;
    int quantity;
    double cost;
    double totalRevenue;

public:
    itemType();

    void setName(QString passedName);
    void setQuantity(int passedQuantity);
    void setCost(double passedCost);
    void setTotalRevenue(double passedRevenue);

   QString getName();
    int getQuantity();
    double setCost();
    double setTotalRevenue();
};


#endif // ITEMTYPE_H
