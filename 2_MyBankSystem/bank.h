#ifndef BANK_H
#define BANK_H

#include <vector>

#include "account.h"

class Bank
{
public:
    Bank(std::string name, double forfeit);
    ~Bank();

	std::string GetName() { return name_; }
    double GetFundsAmount() { return funds_; }

    bool RegisterNewClient(Client* client); // регистрируем нового клиента = открываем счет
    bool RegisterNewClientWithSum(Client* client, double sum); // регистрируем нового клиента = открываем счет

    int GetAccountCount() { return accounts_->size(); }
    double GetForfeit() { return forfeit_; }

    void Charge(double amount) { funds_ += amount; }

	void DeleteAccount(Account* account);
	Account& GetAccountAtIndex(int index);

private:
	std::string name_;
    double funds_;
    double forfeit_;

	std::vector<Account*>* accounts_;
};

#endif // BANK_H
