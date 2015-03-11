using namespace std;

#include <string>

#include "client.h"
#include "account.h"

Client::Client(string name)
{
    name_ = name;
    accounts_ = new vector<Account*>();
}

Client::~Client()
{
    accounts_->clear();
    delete(accounts_);
}

bool Client::IsIdCorrect(int id) {
    bool a = accounts_->size() == 0;
    bool b = ((unsigned int) id) >= accounts_->size();
    return !(a || b);
}

bool Client::DepositFunds(double amount, int accountId) {
    if (!IsIdCorrect(accountId))
        return false;

    accounts_->at(accountId)->DepositFunds(amount);
    return true;
}


bool Client::WithdrawFunds(double amount, int accountId) {
    if (!IsIdCorrect(accountId))
        return false;

    return accounts_->at(accountId)->WithdrawFunds(amount);
}

void Client::AddNewAccount(Account *account) {
    accounts_->push_back(account);
}

