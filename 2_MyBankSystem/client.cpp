#include "bank.h"

#include <algorithm>

#include "client.h"

Client::Client(std::string name)
{
    name_ = name;
    accounts_ = new std::vector<Account*>();
}

Client::~Client()
{
	for (int i = 0; i < accounts_->size(); i++)
	{
		(*accounts_)[i]->GetBank().DeleteAccount((*accounts_)[i]);
	}

    accounts_->clear();
    delete accounts_;
}

Account& Client::GetAccountAtIndex(int index)
{
	if (IsIdCorrect(index))
		return *(*accounts_)[index];

	Account *p = 0;
	return *p;
}

void Client::DeleteAccount(Account* account)
{
	auto pos = find(accounts_->begin(), accounts_->end(), account);
	if (pos != accounts_->end())
		accounts_->erase(pos);
}

bool Client::IsIdCorrect(int id) {
    bool a = accounts_->size() == 0;
    bool b = static_cast<unsigned int>(id) >= accounts_->size();
    return !(a || b);
}

bool Client::DepositFunds(double amount, int accountId) {
    if (!IsIdCorrect(accountId))
        return false;

	(*accounts_)[accountId]->DepositFunds(amount);
    return true;
}


bool Client::WithdrawFunds(double amount, int accountId) {
    if (!IsIdCorrect(accountId))
        return false;

	return (*accounts_)[accountId]->WithdrawFunds(amount);
}

void Client::AddNewAccount(Account *account) {
    accounts_->push_back(account);
}

std::ostream& operator << (std::ostream& out, Client* client) {
	return client->print(out, client);
}