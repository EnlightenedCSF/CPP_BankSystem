using namespace std;

#ifndef INDIVIDUALCLIENT_H
#define INDIVIDUALCLIENT_H

#include <string>

#include "client.h"

class IndividualClient : public virtual Client
{
public:
    IndividualClient(string name);

    bool TransferFunds(double amount, int fromId, int toId) override;
};

#endif // INDIVIDUALCLIENT_H