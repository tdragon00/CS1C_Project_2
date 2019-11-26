#include "totalpurchases.h"

class totalPurchasesData : public QSharedData
{
public:

};

totalPurchases::totalPurchases() : data(new totalPurchasesData)
{

}

totalPurchases::totalPurchases(const totalPurchases &rhs) : data(rhs.data)
{

}

totalPurchases &totalPurchases::operator=(const totalPurchases &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

totalPurchases::~totalPurchases()
{

}
