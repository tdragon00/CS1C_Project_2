#include "itemtype.h"

//CONSTRUCTOR

// this default constructor sets all strings to "NOT SET" and double to 0
itemType::itemType()
{
    name = "NOT SET";
    quantity = 0;
    cost = 0;
    totalRevenue = 0;
    qtySold = 0;
}


//SETTERS

// Sets the item's name
void itemType::setName(QString passedName)
{
    name = passedName;
}

// Sets the item's number of quantity
void itemType::setQuantity(int passedQuantity)
{
    if (passedQuantity < 0)
        quantity = 0;
    else
        quantity = passedQuantity;
}

// Sets the item's cost
void itemType::setCost(double passedCost)
{
    if (passedCost < 0)
        cost = 0;
    else
        cost = passedCost;
}

// Sets the item's total revenue
void itemType::setTotalRevenue(double passedRevenue)
{
    if (passedRevenue < 0)
        totalRevenue = 0;
    else
        totalRevenue = passedRevenue;
}

// Sets the item's number of quantity sold
void itemType::setQuantitySold(int passedSold)
{
    if (passedSold < 0)
        qtySold = 0;
    else
        qtySold = passedSold;
}


//GETTERS
// Returns the item's name
QString itemType::getName()
{
    return name;
}

// Returns the item's number of quantity
int itemType::getQuantity()
{
    return quantity;
}

// Returns the item's cost
double itemType::setCost()
{
    return cost;
}

// Returns the item's total revenue
double itemType::setTotalRevenue()
{
    return totalRevenue;
}

// Returns the item's number of quantity sold
int itemType::setQuantitySold()
{
    return qtySold;
}
