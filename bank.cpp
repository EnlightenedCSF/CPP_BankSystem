using namespace std;

#include <string>

#include "bank.h"

Bank::Bank(string name)
{
    name_ = name;
    funds_ = 0;

    accounts_ = new vector<Account*>();
}

Bank::~Bank()
{
    accounts_->clear();
    delete(accounts_);
}

bool Bank::RegisterNewClient(Client *client) {
    Account* account = new Account(this, client);
    client->AddNewAccount(account);
    accounts_->push_back(account);
}

string Bank::GetName() {
    return name_;
}
