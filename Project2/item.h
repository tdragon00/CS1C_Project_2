/** @file item.h
*	@brief Contains data in regard to items within the databse.
*/

#ifndef ITEM_H
#define ITEM_H

#include <QObject>

/**
* @brief Contains property values of an item from the database.
*/
class Item
{
private:
    QString itemName;
    double  itemPrice;
public:
    Item();
    Item(QString name, double price);

    QString GetItemName() const;
    double GetItemPrice() const;
};

#endif // ITEM_H
