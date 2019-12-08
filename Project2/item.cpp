#include "item.h"

Item::Item()
{
    itemName = "";
    itemPrice = 0.00;
}
Item::Item(QString name, double price)
{
    itemName = name;
    itemPrice = price;
}

QString Item::GetItemName() const
{
    return itemName;
}

double Item::GetItemPrice() const
{
    return itemPrice;
}
