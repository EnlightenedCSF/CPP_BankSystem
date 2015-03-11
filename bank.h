using namespace std;

#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>

#include "client.h"
#include "account.h"

class Bank
{
public:
    Bank(string name);
    ~Bank();

    string GetName();

    bool RegisterNewClient(Client* client); // регистрируем нового клиента = открываем счет
    bool RegisterNewClientWithSum(Client* client, double sum); // регистрируем нового клиента = открываем счет

    int GetAccountCount() {return accounts_->size(); }

private:
    string name_;
    double funds_;

    vector<Account*>* accounts_;
};

#endif // BANK_H
