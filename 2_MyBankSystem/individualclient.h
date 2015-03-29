#ifndef INDIVIDUALCLIENT_H
#define INDIVIDUALCLIENT_H

#include "client.h"

class IndividualClient : public virtual Client
{
public:
	explicit IndividualClient(std::string name);

    bool TransferFunds(double amount, int fromId, int toId) override;

	virtual std::ostream& print(std::ostream& out, Client* client) override
	{
		out << client->GetName() << "\t\t" << client->GetAccountCount() << '\n';
		return out;
	}
};

#endif // INDIVIDUALCLIENT_H
