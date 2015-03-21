#ifndef TERMINAL_H
#define TERMINAL_H

#include <vector>

#include "bank.h"

class Terminal
{
public:
    Terminal();
    ~Terminal();

    void LoadDemoData();
    void ShowDemo();

    void Start();

private:
	std::vector<Bank*>* banks_;
	std::vector<Client*>* clients_;

	std::string command_;

	void AddBank();
	void DeleteBank();
	void RegisterNewClient(int index);
	void DeleteAccount(int index);
	void ShowBank(int index);
	int GetBankIndex(std::string bankName);
	void ShowBanks();
	
	void AddClient();
	void DeleteClient();
	int GetClientIndex(std::string clientNam);
	void ShowClient(int index);
	void ShowClients();

	void DepositFunds(int index);
	void WithdrawFunds(int index);
	void TransferFunds(int index);
};

#endif // TERMINAL_H
