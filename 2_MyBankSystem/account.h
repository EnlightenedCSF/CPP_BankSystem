using namespace std;

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Bank;
class Client;

class Account
{
public:
    Account(Bank* bank, Client* client);
    ~Account();

    string GetBankName();
	string GetClientName();

	double GetFunds();
    void DepositFunds(double amount);
    bool WithdrawFunds(double amount);
    double GetFundsAmount() { return funds_; }

    Bank* GetBank();
	Client* GetClient();

private:
    double funds_;

    Bank* bank_;
    Client* client_;
};

#endif // ACCOUNT_H
