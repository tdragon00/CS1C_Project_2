/** @file memberType.h
*	@brief Contains data in regard to members within the databse.
*/

#ifndef MEMBERTYPE_H
#define MEMBERTYPE_H

#include <QString>

/**
*	@brief Contains data in regard to members within the databse.
*/
class memberType
{
private:
    //VARIABLES
    //! the member's first and last name-INPUT
    QString*  name;

    //! the member's ID number-INPUT
    int idNumber;

    //! the member's member type (Regular or Executive)-INPUT
    QString   membershipType;

    //! the member's expiration date-INPUT
    QString   expirationDate;

    //! the member's total purchases-INPUT
    double    totalPurchases;

    //! the member's total rebate from the total purchases-INPUT
    double    totalRebate;

public:
    //CONSTRUCTORS
     //! this default constructor sets all strings to "NOT SET" and the total purchases and rebate
    memberType();

    //! copy constructor
    memberType(const memberType & otherMember);

    //DESTRUCTORS
    ~memberType();

    //SETTERS
    //! Sets the member's first and last name
    void setName(QString passedName);

    //! Sets the member's ID number
    void setID(int passedId);

    //! Sets the member's membership type
    void setMemberType(QString passedMember);

    //! Sets the member's expiration date
    void setExpDate(QString passedDate);

    //! Sets the member's total purchases
    void setPurchases(double passedPurchase);

    //! Sets the member's total rebate from the total purchases
    void setRebate(double passedRebate);

     //GETTERS
    //! Returns the member's first and last name
    QString getName() const;

    //! Returns the member's ID number
    int getID() const;

    //! Returns the member's membership type
    QString getMemberType() const;

    //! Returns the member's expiration date
    QString getExpDate() const;

    //! Returns the member's total purchases
    double getPurchase() const;

    //! Returns the member's total rebate from the total purchases
    double getRebate() const;

    //OVERLOAD
    memberType operator = ( memberType const & other);
};

#endif // MEMBERTYPE_H
