using namespace std;

#ifndef INDIVIDUALCLIENT_H
#define INDIVIDUALCLIENT_H

#include <string>

#include "client.h"

class IndividualClient : public virtual Client
{
public:
    IndividualClient(string name);
    ~IndividualClient();

    bool TransferFunds(double amount, long id);
};

#endif // INDIVIDUALCLIENT_H
