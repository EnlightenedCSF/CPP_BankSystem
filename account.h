#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Bank;
class Client;

class Account
{
public:
    Account(Bank* bank, Client* client);
    ~Account();

    string GetBankName();
    string GetClientName();

    void DepositFunds(double amount);
    bool WithdrawFunds(double amount);
    double GetFundsAmount() { return funds_; }

    Bank* GetBank();

private:
    double funds_;

    Bank* bank_;
    Client* client_;
};

#endif // ACCOUNT_H
