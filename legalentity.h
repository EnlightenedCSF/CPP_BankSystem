using namespace std;

#ifndef LEGALENTITY_H
#define LEGALENTITY_H

#include <string>

#include "client.h"

class LegalEntity : public virtual Client
{
public:
    LegalEntity(string name);

    bool TransferFunds(double amount, int fromId, int toId);
};

#endif // LEGALENTITY_H
