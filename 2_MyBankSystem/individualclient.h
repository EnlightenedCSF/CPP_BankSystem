#ifndef INDIVIDUALCLIENT_H
#define INDIVIDUALCLIENT_H

#include "client.h"

class IndividualClient : public virtual Client
{
public:
	explicit IndividualClient(std::string name);

    bool TransferFunds(double amount, int fromId, int toId) override;
};

#endif // INDIVIDUALCLIENT_H
