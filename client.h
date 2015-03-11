using namespace std;

#ifndef CLIENT_H
#define CLIENT_H

#include <account.h>

#include <string>
#include <vector>

class Client
{
public:
    Client(string name);
    ~Client();

    bool DepositFunds(double amount); // положить деньги на счет, возвращает правду, если все опрерация прошла успешно
    bool WithdrawFunds(double amount); // снять деньги со счета
    virtual bool TransferFunds(double amount, long id) = 0; // абстрактный метод перевода средств

    void AddNewAccount(Account* account);

private:
    string name_;

    vector<Account*>* accounts_;
};

#endif // CLIENT_H
