#include "client.h"

#include <string>

#include "bank.h"

Bank::Bank(std::string name, double forfeit)
{
    name_ = name;
    funds_ = 0;
    forfeit_ = forfeit;

    accounts_ = new std::vector<Account*>();
}

Bank::~Bank()
{
	for (int i = 0; i < accounts_->size(); i++)
	{
		(*accounts_)[i]->GetClient().DeleteAccount((*accounts_)[i]);
	}

    accounts_->clear();
    delete accounts_;
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


void Bank::DeleteAccount(Account* account)
{
	auto pos = find(accounts_->begin(), accounts_->end(), account);
	
	if (pos != accounts_->end())
	{
		account->GetClient().DeleteAccount(account);
		accounts_->erase(pos);
	}
}

Account& Bank::GetAccountAtIndex(int index)
{
	return *(*accounts_)[index];
}


std::ostream& operator << (std::ostream& out, Bank* bank){
	out << bank->GetName() << "\t\t" << bank->GetAccountCount() << "\t\t" << bank->GetFundsAmount() << "\t\t" << bank->GetForfeit() << '\n';
	return out;
}