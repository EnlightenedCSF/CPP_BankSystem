#include "bank.h"
using namespace std;

#include <string>
#include <algorithm>

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

Account* Client::GetAccountAtIndex(int index)
{
	if (IsIdCorrect(index))
		return accounts_->at(index);
	
	return nullptr;
}

void Client::DeleteAccount(Account* account)
{
	auto pos = find(accounts_->begin(), accounts_->end(), account);
	if (pos != accounts_->end())
		accounts_->erase(pos);
}

void Client::ClearData()
{
	for (int i = 0; i < accounts_->size(); i++)
	{
		accounts_->at(i)->GetBank()->DeleteAccount(accounts_->at(i));
	}
}

bool Client::IsIdCorrect(int id) {
    bool a = accounts_->size() == 0;
    bool b = static_cast<unsigned int>(id) >= accounts_->size();
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

