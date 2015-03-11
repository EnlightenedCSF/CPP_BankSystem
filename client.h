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

    string GetName() { return name_; }

    bool DepositFunds(double amount, int accountId);    // положить деньги на счет, возвращает правду, если все опрерация прошла успешно
    bool WithdrawFunds(double amount, int accountId);   // снять деньги со счета
    virtual bool TransferFunds(double amount, int fromId, int toId) = 0; // абстрактный метод перевода средств (реализован в детях)

    void AddNewAccount(Account* account);
    int GetAccountCount() { return accounts_->size(); }

protected:
    bool IsIdCorrect(int id);

private:
    string name_;
    vector<Account*>* accounts_;
};

#endif // CLIENT_H
