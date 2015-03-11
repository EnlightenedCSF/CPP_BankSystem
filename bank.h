using namespace std;

#ifndef BANK_H
#define BANK_H

#include <string>

#include "client.h"

class Bank
{
public:
    Bank(string name);
    ~Bank();

    bool RegisterNewClient(Client* client);

private:
    string name_;
    double funds_;
};

#endif // BANK_H
