using namespace std;

#include <string>

#include "bank.h"

Bank::Bank(string name, double forfeit)
{
    name_ = name;
    funds_ = 0;
    forfeit_ = forfeit;

    accounts_ = new vector<Account*>();
}

Bank::~Bank()
{
    accounts_->clear();
    delete(accounts_);
}

bool Bank::RegisterNewClient(Client *client) {
    return RegisterNewClientWithSum(client, 0);
}

bool Bank::RegisterNewClientWithSum(Client *client, double sum) {
    Account* account = new Account(this, client);
    account->DepositFunds(sum);
    client->AddNewAccount(account);
    accounts_->push_back(account);
    return true;
}
