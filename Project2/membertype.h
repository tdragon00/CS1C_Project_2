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
    QString*  name;
    int           idNumber;
    QString   membershipType;
    QString   expirationDate;
    double    totalPurchases;
    double    totalRebate;

public:
    memberType();
    memberType(const memberType & otherMember);

    void setName(QString passedName);
    void setID(int passedId);
    void setMemberType(QString passedMember);
    void setExpDate(QString passedDate);
    void setPurchases(double passedPurchase);
    void setRebate(double passedRebate);

    QString getName() const;
    int getID() const;
    QString getMemberType() const;
    QString getExpDate() const;
    double getTotalSpent() const;
    double getRebate() const;
};

#endif // MEMBERTYPE_H
