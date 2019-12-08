/** @file itemType.h
*	@brief Contains data in regard to items within the database.
*/

#ifndef ITEMTYPE_H
#define ITEMTYPE_H

#include <QString>

//!  A class to contain item information.
/*!
  This class contains all item information.
*/
class itemType
{    
private:
     //VARIABLES
    //! the item's name-INPUT
    QString name;

    //! the item's number of quantity-INPUT
    int quantity;

    //! the item's cost-INPUT
    double cost;

    //! the item's total revenue-INPUT
    double totalRevenue;

    //! the item's number of quantity sold-INPUT
    int qtySold;

public:
    //CONSTRUCTOR
    //! this default constructor sets all strings to "NOT SET" and double to 0
    itemType();

    //DESTRUTOR
    ~itemType();


    //SETTERS
    //! Sets the item's name
    void setName(QString passedName);

    //! Sets the item's number of quantity
    void setQuantity(int passedQuantity);

    //! Sets the item's cost
    void setCost(double passedCost);

    //! Sets the item's total revenue
    void setTotalRevenue(double passedRevenue);

    //! Sets the item's number of quantity sold
    void setQuantitySold(int passedSold);


    //GETTERS
    //! Returns the item's name
   QString getName();

   //! Returns the item's number of quantity
    int getQuantity();

    //! Returns the item's cost
    double setCost();

    //! Returns the item's total revenue
    double setTotalRevenue();

    //! Returns the item's number of quantity sold
    int setQuantitySold();
};


#endif // ITEMTYPE_H
