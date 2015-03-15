using namespace std;

#include <iostream>
#include <stdio.h>
#include <string>
#include <regex>

#include "individualclient.h"
#include "legalentity.h"
#include "terminal.h"


Terminal::Terminal()
{
    banks_ = new vector<Bank*>();
    clients_ = new vector<Client*>();
}

Terminal::~Terminal()
{
    banks_->clear();
    clients_->clear();

    delete banks_;
    delete clients_;
}

void Terminal::LoadDemoData() {
    banks_->push_back(new Bank("Sberbank", 2));
    banks_->push_back(new Bank("MoskInBank", 1));

    clients_->push_back(new IndividualClient("John Doe"));
    clients_->push_back(new IndividualClient("Marry Smith"));

    clients_->push_back(new LegalEntity("OOO Gasprom"));

    banks_->at(1)->RegisterNewClient(clients_->at(0));
    banks_->at(1)->RegisterNewClientWithSum(clients_->at(1), 1000);
    banks_->at(1)->RegisterNewClient(clients_->at(0));

    banks_->at(0)->RegisterNewClientWithSum(clients_->at(2), 1000000);
    banks_->at(1)->RegisterNewClientWithSum(clients_->at(2), 1000000);

    banks_->at(0)->RegisterNewClient(clients_->at(0));
}

void Terminal::ShowDemo() {
    if (clients_->at(1)->WithdrawFunds(50, 0))
        cout << clients_->at(1)->GetName() << ": Withdrawn\n";

    if (!clients_->at(0)->WithdrawFunds(10000000, 0))
        cout << clients_->at(0)->GetName() << ": Error! Not enough money or wrong id!\n";

    if (clients_->at(0)->DepositFunds(900, 0))
        cout << "Successfully added\n";

    if (clients_->at(0)->TransferFunds(900, 0, 1))
        cout << "Successfully transferred\n";

    if (clients_->at(2)->TransferFunds(500000, 1, 0))
        cout << "Legal entity can tranfer between different banks!\n";

    if (!clients_->at(0)->TransferFunds(100, 0, 2))
        cout << "But individual clients can't transfer between banks\n";

    cout << "\n\n";
}

void Terminal::AddBank()
{
	cout << "\nCREATING A BANK\nInsert bank name: ";
	string name;
	getline(cin, name);

	try
	{
		cout << "Insert bank's forfeit (1 to 99): ";
		string forfeit;
		getline(cin, forfeit);
		double bankForfeit = stod(forfeit);
		if (bankForfeit < 1 || bankForfeit > 99)
			throw invalid_argument("Bank fofeit must be between 1 and 99!");

		banks_->push_back(new Bank(name, bankForfeit));
	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
		cout << "\nError adding a bank!\n\n";
		ShowBanks();
	}
	catch (...)
	{
		cout << "Error adding a bank!\n\n";
		ShowBanks();
	}

	cout << "Added!\n\n";
	ShowBanks();
}

void Terminal::DeleteBank()
{
	cout << "\nDELETING A BANK\nInsert bank index: \n";
	string strIndex;
	getline(cin, strIndex);
	int index = 0;
	try {
		 index = stoi(strIndex);
		 if (index >= banks_->size() || index < 1)
			 throw;
	}
	catch (...)
	{
		cout << "Index must be correct!\n\n";
		ShowBanks();
	}

	index--;
	Bank* bank = banks_->at(index);
	bank->ClearData();
	banks_->erase(banks_->begin() + index);
	cout << "Successfully deleted!\n\n";
	ShowBanks();
}

void Terminal::RegisterNewClient(int index)
{
	cout << "\nREGISTRATION\n\tClient list:\n";
	for (int i = 0; i < clients_->size(); i++)
	{
		cout << i + 1 << ")\t" << clients_->at(i)->GetName() << '\n';
	}
	cout << "\nInput client index to register: ";
	getline(cin, command_);

	try
	{
		int id = stoi(command_);
		if (id < 1 || id > clients_->size())
			throw;

		cout << "Input a starting sum: ";
		getline(cin, command_);
		double sum = stod(command_);
		if (sum < 0)
			throw;

		if (banks_->at(index)->RegisterNewClientWithSum(clients_->at(--id), sum))
			cout << "Success!\n\n";
		else
			cout << "Error!\n\n";
	}
	catch (...)
	{
		cout << "Error!\n\n";
	}
	ShowBank(index);
}

void Terminal::DeleteAccount(int index)
{
	try
	{
		cout << "\nACCOUNT DELETING\n";
		cout << "Input index of an account to delete: ";
		getline(cin, command_);
		int id = stoi(command_);
		if (id < 1 || id > banks_->at(index)->GetAccountCount())
			throw;

		banks_->at(index)->DeleteAccount(banks_->at(index)->GetAccountAtIndex(--id));
		cout << "Success!\n\n";
	}
	catch (...)
	{
		cout << "Error!\n\n";
	}
	ShowBank(index);
}

void Terminal::ShowBank(int index)
{
	auto bank = banks_->at(index);
	cout << "\nBank:\n\t" << bank->GetName() << '\n';
	cout << "Accounts:\n";
	for (int i = 0; i < bank->GetAccountCount(); i++)
	{
		cout << i + 1 << ")\t" << bank->GetAccountAtIndex(i)->GetClientName() << "\t"; // << client->GetAccountAtIndex(i)->GetFunds() << '\n';
		printf("%5.2f\n", bank->GetAccountAtIndex(i)->GetFunds());
	}
	cout << "----------\nTotal: " << bank->GetAccountCount() << '\n';

	cout << "\n[+] Register new client\n[-] Delete account\n[q] Back\n";

	do
	{
		getline(cin, command_);

		if (command_.compare("+") == 0)
			RegisterNewClient(index);
		else if (command_.compare("-") == 0)
			DeleteAccount(index);
		else if (command_.compare("q") == 0)
			ShowBanks();
	} while (1);
}

void Terminal::ShowBanks() {
    cout << "============== Bank list: ==============\n";
    cout << "#\tTitle\t\tAcc. count\tBank funds\tForfeit, %\n";

    if (banks_->size() == 0)
        cout << "Empty\n";
    else {
        for (unsigned int i = 0; i < banks_->size(); i++) {
            cout << i+1 << ")\t" << banks_->at(i)->GetName() << "\t\t" << banks_->at(i)->GetAccountCount()
                 << "\t\t" << banks_->at(i)->GetFundsAmount() << "\t\t" << banks_->at(i)->GetForfeit() << '\n';
        }
    }
    cout << "\n\n";

    cout << "[+] Add new Bank\n[-] Delete bank\n[<number>] Switch to chosen bank\n[q] Back\n";
    do {
        getline(cin, command_);

		if (command_.compare("+") == 0)
			AddBank();
		else if (command_.compare("-") == 0)
			DeleteBank();
		else if (command_.compare("q") == 0)
			Start();
		else
		{
			int index = stoi(command_);
			if (index < 1 || index > clients_->size())
				throw;

			ShowBank(--index);
		}
    } while (1);
}

void Terminal::AddClient()
{
	cout << "\nCREATING A CLIENT\nInsert client name: ";
	string name;
	getline(cin, name);

	try
	{
		cout << "Insert 'i' if individual client and 'l' if legal entity: ";
		string type;
		getline(cin, type);
		if (type.compare("l") && type.compare("i"))
			throw invalid_argument("Only 'i' and 'l' please!");

		if (type.compare("i") == 0)
			clients_->push_back(new IndividualClient(name));
		else
			clients_->push_back(new LegalEntity(name));
	}
	catch (const invalid_argument& e)
	{
		cout << e.what() << "\nError adding a client!\n\n";
		ShowClients();
	}
	catch (...)
	{
		cout << "Error adding a client!\n\n";
		ShowClients();
	}

	cout << "Successfully added!\n\n";
	ShowClients();
}

void Terminal::DeleteClient()
{
	cout << "\nDELETING A CLIENT\nInsert client index: \n";
	string strIndex;
	getline(cin, strIndex);
	int index = 0;
	try {
		index = stoi(strIndex);
		if (index >= clients_->size() || index < 1)
			throw;
	}
	catch (...)
	{
		cout << "Index must be correct!\n\n";
		ShowBanks();
	}

	index--;
	auto client = clients_->at(index);
	client->ClearData();
	clients_->erase(clients_->begin() + index);
	cout << "Successfully deleted!\n\n";
	ShowClients();
}

void Terminal::ShowClient(int index)
{
	auto client = clients_->at(index);
	cout << "\nClient:\n\t" << client->GetName() << '\n';
	cout << "Accounts:\n";
	for (int i = 0; i < client->GetAccountCount(); i++)
	{
		cout << i + 1 << ")\t" << client->GetAccountAtIndex(i)->GetBankName() << "\t";// << client->GetAccountAtIndex(i)->GetFunds() << '\n';
		printf("%5.2f\n", client->GetAccountAtIndex(i)->GetFunds());
	}
	cout << "----------\nTotal: " << client->GetAccountCount() << '\n';

	cout << "\n[+] Deposit funds\n[-] Withdraw funds\n[*] Transfer funds\n[q] Back\n";

	do
	{
		getline(cin, command_);

		if (command_.compare("+") == 0)
			DepositFunds(index);
		else if (command_.compare("-") == 0)
			WithdrawFunds(index);
		else if (command_.compare("*") == 0)
			TransferFunds(index);
		else if (command_.compare("q") == 0)
			ShowClients();
	} while (1);
}

void Terminal::ShowClients() {
    cout << "\n============== Client list: ==============\n";
    cout << "#\tName/Title\t\tAccount count\n";

    if (clients_->size() == 0)
        cout << "Empty\n";
    else {
        for (unsigned int i = 0; i < clients_->size(); i++) {
            cout << i+1 << ")\t" << clients_->at(i)->GetName() << "\t\t" << clients_->at(i)->GetAccountCount() << '\n';
        }
    }
    cout << "\n\n";

	cout << "[+] Add new client\n[-] Delete client\n[<number>] Switch to chosen client\n[q] Back\n";
	do {
		getline(cin, command_);

		if (command_.compare("+") == 0)
			AddClient();
		else if (command_.compare("-") == 0)
			DeleteClient();
		else if (command_.compare("q") == 0)
			Start();
		else try
		{
			int index = stoi(command_);
			if (index < 1 || index > clients_->size())
				throw;

			ShowClient(--index);
		}
		catch (...) { }
		

	} while (1);
}

void Terminal::DepositFunds(int index)
{
	try
	{
		cout << "Insert how much to deposit: ";
		getline(cin, command_);
		double sum = stod(command_);

		cout << "Input the index of account to add money to: ";
		getline(cin, command_);
		int id = stoi(command_);
		if (!clients_->at(index)->IsIdCorrect(--id))
			throw;

		if (clients_->at(index)->DepositFunds(sum, id))
			cout << "Success!\n\n";
		else
			cout << "Error\n\n";
	}
	catch (...)
	{
		cout << "Error\n\n";
	}
	
	ShowClient(index);
}

void Terminal::WithdrawFunds(int index)
{
	try
	{
		cout << "Input how much to withdraw: ";
		getline(cin, command_);
		double sum = stod(command_);

		cout << "Input the index of account to withdraw money from: ";
		getline(cin, command_);
		int id = stoi(command_);
		if (!clients_->at(index)->IsIdCorrect(--id))
			throw;

		if (clients_->at(index)->WithdrawFunds(sum, id))
			cout << "Success!\n\n";
		else
			cout << "Not enough funds to perform this operation!\n\n";
	}
	catch (...)
	{
		cout << "Error\n\n";
	}

	ShowClient(index);
}

void Terminal::TransferFunds(int index)
{
	try
	{
		cout << "Input how much to transfer: ";
		getline(cin, command_);
		double sum = stod(command_);

		cout << "Input the index of account to transfer money from: ";
		getline(cin, command_);
		int idFrom = stoi(command_);
		if (!clients_->at(index)->IsIdCorrect(--idFrom))
			throw;

		cout << "Input the index of account to transfer money to: ";
		getline(cin, command_);
		int idTo = stoi(command_);
		if (!clients_->at(index)->IsIdCorrect(--idTo))
			throw;

		if (clients_->at(index)->TransferFunds(sum, idFrom, idTo))
			cout << "Success!\n\n";
		else
			cout << "Error\n\n";
	}
	catch (...)
	{
		cout << "Error\n\n";
	}

	ShowClient(index);
}

void Terminal::Start() {
	cout << "\n\t=== Welcome! ===\n\tChoose mode:\n"
		<< "[0] Work with banks \n"
		<< "[1] Work with clients\n"
		<< "[q] Exit\n";

    do {
        getline(cin, command_);

        if (command_.compare("0") == 0)
            ShowBanks();
		else if (command_.compare("1") == 0)
			ShowClients();
		else if (command_.compare("q") == 0)
			exit(EXIT_SUCCESS);
    } while (1);
}
