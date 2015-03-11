using namespace std;

#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client
{
public:
    Client(string name);
    ~Client();

    bool DepositFunds(double amount);
    bool WithdrawFunds(double amount);
    virtual bool TransferFunds(double amount, long id) = 0; // pure virtual

private:
    string name_;
};

#endif // CLIENT_H
