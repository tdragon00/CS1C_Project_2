/** @file member.h
*	@brief Contains data in regard to members within the databse.
*/

#ifndef MEMBER_H
#define MEMBER_H

#include <QDate>

enum MemberType {REGULAR, EXECUTIVE};
const double REBATE_RATE = 0.04;

/**
* @brief Contains property values of a member from the database.
*/
class Member
{
private:
    QString     memberName;
    int         memberID;
    MemberType  membership;
    QDate       expirationDate;
    double      rebate;
    double      totalSpent;
    int         memberRenewal;
public:
    Member(QString name, int id, int renewCost);
    Member(QString name, int id, double rebateAmt);
    Member(QString name, int id, MemberType mType, QDate expDate);
    Member(QString name, int id, MemberType mType, QDate expDate, double rebateAmt, double totSpent);

    QString GetMemberName() const;
    int GetID() const;
    QString GetMembershipTypeString() const;
    QString GetExpirationDateString() const;
    double GetRebate() const;
    double GetTotalSpent() const;
    int GetRenewCost() const;
    bool isExecutive() const;
};

#endif // MEMBER_H
