#include <vector>

#ifndef CLIENT_H
#define CLIENT_H

#include "account.h"

class Client
{
public:
	explicit Client(std::string name);
	virtual ~Client();

	std::string GetName() { return name_; }

    bool DepositFunds(double amount, int accountId);    // положить деньги на счет, возвращает правду, если все опрерация прошла успешно
    bool WithdrawFunds(double amount, int accountId);   // снять деньги со счета
    virtual bool TransferFunds(double amount, int fromId, int toId) = 0; // абстрактный метод перевода средств (реализован в детях)

    void AddNewAccount(Account* account);
    int GetAccountCount() { return accounts_->size(); }
	Account& GetAccountAtIndex(int index);

	void DeleteAccount(Account* account);
	
	bool IsIdCorrect(int id);

	virtual std::ostream& print(std::ostream& out, Client* client) = 0;

 	friend std::ostream& operator << (std::ostream& out, Client* client);

protected:
	std::string name_;
	std::vector<Account*>* accounts_;
};

#endif // CLIENT_H
