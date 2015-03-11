using namespace std;

#ifndef LEGALENTITY_H
#define LEGALENTITY_H

#include <string>

#include "client.h"

class LegalEntity : public virtual Client
{
public:
    LegalEntity(string name);
    ~LegalEntity();

    bool TransferFunds(double amount, long id);
};

#endif // LEGALENTITY_H
