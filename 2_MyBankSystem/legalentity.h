#ifndef LEGALENTITY_H
#define LEGALENTITY_H

#include "client.h"

class LegalEntity : public virtual Client
{
public:
	explicit LegalEntity(std::string name);

    bool TransferFunds(double amount, int fromId, int toId) override;

	virtual std::ostream& print(std::ostream& out, Client* client) override
	{
		out << client->GetName() << "\t\t" << client->GetAccountCount() << '\n';
		return out;
	}
};

#endif // LEGALENTITY_H
