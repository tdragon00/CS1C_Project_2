#include "member.h"

Member::Member(QString name, int id, MemberType mType, QDate expDate)
{
    memberName      = name;
    memberID        = id;
    membership      = mType;
    expirationDate  = expDate;
    rebate          = 0.00;
    totalSpent      = 0.00;
}

Member::Member(QString name, int id, int renewCost)
{
    memberName      = name;
    memberID        = id;
    memberRenewal   = renewCost;
    rebate          = 0.00;
    totalSpent      = 0.00;
}

Member::Member(QString name, int id, MemberType mType, QDate expDate, double rebateAmt, double totSpent)
{
    memberName      = name;
    memberID        = id;
    membership      = mType;
    expirationDate  = expDate;
    rebate          = rebateAmt;
    totalSpent      = totSpent;
}

Member::Member(QString name, int id, double rebateAmt)
{
    memberName = name;
    memberID   = id;
    rebate     = rebateAmt;
    totalSpent = 0.0;
}

QString Member::GetMemberName() const
{
    return memberName;
}

int Member::GetID() const
{
    return memberID;
}

QString Member::GetMembershipTypeString() const
{
    QString membershipType;

    switch(membership)
    {
    case REGULAR:
        membershipType = "Regular";
        break;
    case EXECUTIVE:
        membershipType = "Executive";
        break;
    };

    return membershipType;
}

QString Member::GetExpirationDateString() const
{
    return expirationDate.toString("MM/dd/yyyy");
}

double Member::GetRebate() const
{
    return rebate;
}

double Member::GetTotalSpent() const
{
    return totalSpent;
}

bool Member::isExecutive() const
{
    bool executiveMember;

    if(membership == EXECUTIVE)
    {
        executiveMember = true;
    }
    else
    {
        executiveMember = false;
    }

    return executiveMember;
}

int Member::GetRenewCost() const
{
    return memberRenewal;
}
