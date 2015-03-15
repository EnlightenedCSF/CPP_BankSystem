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
    vector<Bank*>* banks_;
    vector<Client*>* clients_;

    string command_;
    bool IsCommandValid(string regexp);

	void AddBank();
	void DeleteBank();
	void ShowBanks();
	void AddClient();
	void DeleteClient();
	
	void ShowClient(int index);
	void ShowClients();

	void DepositFunds(int index);
	void WithdrawFunds(int index);
	void TransferFunds(int index);
};

#endif // TERMINAL_H
