#include "membertype.h"

memberType::memberType()
{
    name = new QString;
    *name = "NOT SET";
    idNumber = 0;
    membershipType =  "NOT SET";
    expirationDate =  "1900/01/01";
    totalPurchases = 0;
    totalRebate = 0;
}

// copy constructor
memberType::memberType(const memberType & otherMember)
{
    name = new QString;
    *name = otherMember.getName();
    idNumber = otherMember.idNumber;
    membershipType =   otherMember.membershipType;
    expirationDate =   otherMember.expirationDate;
    totalPurchases = otherMember.totalPurchases;
    totalRebate = otherMember.totalRebate;
}

//DESTRUCTORS
memberType::~memberType()
{
    delete name;
}

//SETTERS
// Sets the member's first and last name
void memberType::setName(QString passedName)
{
    delete name;

    name = new QString;
    *name = passedName;
}

// Sets the member's ID number
void memberType::setID(int passedId)
{
    if (passedId < 0)
        idNumber = 0;
    else
        idNumber = passedId;
}

// Sets the member's membership type
void memberType::setMemberType(QString passedMember)
{
    membershipType = passedMember;
}

// Sets the member's expiration date
void memberType::setExpDate(QString passedDate)
{
    expirationDate = passedDate;
}

// Sets the member's total purchases
void memberType::setPurchases(double passedPurchase)
{
    if (passedPurchase < 0)
        totalPurchases = 0;
    else
        totalPurchases = passedPurchase;
}

// Sets the member's total rebate from the total purchases
void memberType::setRebate(double passedRebate)
{
    if (passedRebate < 0)
        totalRebate = 0;
    else
        totalRebate = passedRebate;
}

 //GETTERS
// Returns the member's first and last name
QString memberType::getName() const
{
    return *name;
}

// Returns the member's ID number
int memberType::getID() const
{
    return idNumber;
}

// Returns the member's membership type
QString memberType::getMemberType() const
{
    return membershipType;
}

// Returns the member's expiration date
QString memberType::getExpDate() const
{
    return expirationDate;
}

// Returns the member's total purchases
double memberType::getPurchase() const
{
    return totalPurchases;
}

// Returns the member's total rebate from the total purchases
double memberType::getRebate() const
{
    return totalRebate;
}

//OVERLOAD
memberType memberType::operator = ( memberType const & otherMember)
{
    delete name;
    name = new QString;
    *name=otherMember.getName();

    idNumber = otherMember.idNumber;
    membershipType =  otherMember.membershipType;
    expirationDate =   otherMember.expirationDate;
    totalPurchases = otherMember.totalPurchases;
    totalRebate = otherMember.totalRebate;

    return *this;
}

