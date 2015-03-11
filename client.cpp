using namespace std;

#include <string>

#include "client.h"

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

bool Client::DepositFunds(double amount) {

}

bool Client::WithdrawFunds(double amount) {

}

bool Client::TransferFunds(double amount, long id) {

}

void Client::AddNewAccount(Account *account) {
    accounts_->push_back(account);
}
