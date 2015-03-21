#ifndef LEGALENTITY_H
#define LEGALENTITY_H

#include "client.h"

class LegalEntity : public virtual Client
{
public:
	explicit LegalEntity(std::string name);

    bool TransferFunds(double amount, int fromId, int toId) override;
};

#endif // LEGALENTITY_H
