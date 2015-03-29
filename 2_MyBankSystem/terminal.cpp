#include <iostream>
#include <stdio.h>
#include <string>
#include <regex>
#include <stdlib.h>
#include <chrono>
#include <thread>

#include "individualclient.h"
#include "legalentity.h"
#include "terminal.h"


Terminal::Terminal()
{
    banks_ = new std::vector<Bank*>();
    clients_ = new std::vector<Client*>();
}

Terminal::~Terminal()
{
    banks_->clear();
    clients_->clear();

    delete banks_;
    delete clients_;
}

void Terminal::LoadDemoData() {
	auto b1 = new Bank("Sberbank", 2);
	auto b2 = new Bank("MoskInBank", 1);

    banks_->push_back(b1);
    banks_->push_back(b2);

	auto c1 = new IndividualClient("John Doe");
	auto c2 = new IndividualClient("Marry Smith");
	auto c3 = new LegalEntity("OOO Gasprom"); 

    clients_->push_back(c1);
    clients_->push_back(c2);
    clients_->push_back(c3);

	b2->RegisterNewClient(c1);
	b2->RegisterNewClientWithSum(c2, 1000);
	b2->RegisterNewClient(c1);

	b1->RegisterNewClientWithSum(c3, 1000000);
	b2->RegisterNewClientWithSum(c3, 1000000);

	b1->RegisterNewClient(c1);
}

void Terminal::ShowDemo() {
	if ((*clients_)[1]->WithdrawFunds(50, 0))
		std::cout << (*clients_)[1]->GetName() << ": Withdrawn\n";

	if (!(*clients_)[0]->WithdrawFunds(10000000, 0))
		std::cout << (*clients_)[0]->GetName() << ": Error! Not enough money or wrong id!\n";

	if ((*clients_)[0]->DepositFunds(900, 0))
		std::cout << "Successfully added\n";

	if ((*clients_)[0]->TransferFunds(900, 0, 1))
		std::cout << "Successfully transferred\n";

	if ((*clients_)[2]->TransferFunds(500000, 1, 0))
		std::cout << "Legal entity can tranfer between different banks!\n";

	if (!(*clients_)[0]->TransferFunds(100, 0, 2))
		std::cout << "But individual clients can't transfer between banks\n";

	std::cout << "\n\n";
}

void Terminal::AddBank()
{
	std::cout << "\nCREATING A BANK\nInsert bank name: ";
	std::string name;
	getline(std::cin, name);

	try
	{
		std::cout << "Insert bank's forfeit (1 to 99): ";
		std::string forfeit;
		getline(std::cin, forfeit);
		double bankForfeit = stod(forfeit);
		if (bankForfeit < 1 || bankForfeit > 99)
			throw std::invalid_argument("Bank fofeit must be between 1 and 99!");

		banks_->push_back(new Bank(name, bankForfeit));
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what();
		std::cout << "\nError adding a bank!\n\n";
		ShowBanks();
	}
	catch (...)
	{
		std::cout << "Error adding a bank!\n\n";
		ShowBanks();
	}

	std::cout << "Added!\n\n";
	ShowBanks();
}

void Terminal::DeleteBank()
{
	if (banks_->size() == 0)
	{
		std::cout << "The list is empty!\n\n";
		ShowBanks();
	}

	std::cout << "\nDELETING A BANK\nInsert bank name: \n";
	getline(std::cin, command_);
	int index = GetBankIndex(command_);
	if (index >= 0)
	{
		banks_->erase(banks_->begin() + index);
		std::cout << "Successfully deleted!\n\n";
	}
	else
	{
		std::cout << "Bank name must be correct!\n\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	ShowBanks();
}

void Terminal::RegisterNewClient(int index)
{
	std::cout << "\nREGISTRATION\n\tClient list:\n";
	for (int i = 0; i < clients_->size(); i++)
	{
		std::cout << i + 1 << ")\t" << (*clients_)[i]->GetName() << '\n';
	}
	std::cout << "\nInput client index to register: ";
	getline(std::cin, command_);

	try
	{
		int id = stoi(command_);
		if (id < 1 || id > clients_->size())
			throw;

		std::cout << "Input a starting sum: ";
		getline(std::cin, command_);
		double sum = stod(command_);
		if (sum < 0)
			throw;

		if ((*banks_)[index]->RegisterNewClientWithSum((*clients_)[--id], sum))
			std::cout << "Success!\n\n";
		else
			std::cout << "Error!\n\n";
	}
	catch (...)
	{
		std::cout << "Error!\n\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	ShowBank(index);
}

void Terminal::DeleteAccount(int index)
{
	try
	{
		std::cout << "\nACCOUNT DELETING\n";
		std::cout << "Input index of an account to delete: ";
		getline(std::cin, command_);
		int id = stoi(command_);
		if (id < 1 || id > (*banks_)[index]->GetAccountCount())
			throw;

		(*banks_)[index]->DeleteAccount(&(*banks_)[index]->GetAccountAtIndex(--id));
		std::cout << "Success!\n\n";
	}
	catch (...)
	{
		std::cout << "Error!\n\n";
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	ShowBank(index);
}

void Terminal::ShowBank(int index)
{
	system("cls");

	auto bank = (*banks_)[index];
	std::cout << "\nBank:\n\t" << bank->GetName() << '\n';
	std::cout << "Accounts:\n";
	for (int i = 0; i < bank->GetAccountCount(); i++)
	{
		std::cout << i + 1 << ")\t" << (&bank->GetAccountAtIndex(i))->GetClientName() << "\t";
		printf("%5.2f\n", (&bank->GetAccountAtIndex(i))->GetFunds());
	}
	std::cout << "----------\nTotal: " << bank->GetAccountCount() << '\n';

	std::cout << "\n[+] Register new client\n[-] Delete account\n[q] Back\n";

	do
	{
		getline(std::cin, command_);

		if (command_.compare("+") == 0)
			RegisterNewClient(index);
		else if (command_.compare("-") == 0)
			DeleteAccount(index);
		else if (command_.compare("q") == 0)
			ShowBanks();
	} while (1);
}

void Terminal::ShowBanks() {
	system("cls");

	std::cout << "============== Bank list: ==============\n";
	std::cout << "#\tTitle\t\tAcc. count\tBank funds\tForfeit, %\n";

    if (banks_->size() == 0)
	    std::cout << "Empty\n";
    else {
        for (unsigned int i = 0; i < banks_->size(); i++) {
			std::cout << i + 1 << ")\t" << (*banks_)[i];
        }	    
    }
	std::cout << "\n\n";

	std::cout << "[+] Add new Bank\n[-] Delete bank\n[<number>] Switch to chosen bank\n[q] Back\n";
    do {
		command_ = "";
        getline(std::cin, command_);

		if (command_.compare("+") == 0)
			AddBank();
		else if (command_.compare("-") == 0)
			DeleteBank();
		else if (command_.compare("q") == 0)
			Start();
		else
		{
			int index = GetBankIndex(command_);
			if (index >= 0)
				ShowBank(index);
		}
    } while (1);
}

int Terminal::GetBankIndex(std::string bankName)
{
	for (int i = 0; i < banks_->size(); i++)
	{
		if ((*banks_)[i]->GetName().compare(bankName) == 0)
			return i;
	}
	return -1;
}

int Terminal::GetClientIndex(std::string clientName)
{
	for (int i = 0; i < clients_->size(); i++)
	{
		if ((*clients_)[i]->GetName().compare(clientName) == 0)
			return i;
	}
	return -1;
}

void Terminal::AddClient()
{
	std::cout << "\nCREATING A CLIENT\nInsert client name: ";
	std::string name;
	getline(std::cin, name);

	try
	{
		std::cout << "Insert 'i' if individual client and 'l' if legal entity: ";
		std::string type;
		getline(std::cin, type);
		if (type.compare("l") && type.compare("i"))
			throw std::invalid_argument("Only 'i' and 'l' please!");

		if (type.compare("i") == 0)
			clients_->push_back(new IndividualClient(name));
		else
			clients_->push_back(new LegalEntity(name));
	}
	catch (const std::invalid_argument& e)
	{
		std::cout << e.what() << "\nError adding a client!\n\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		ShowClients();
	}
	catch (...)
	{
		std::cout << "Error adding a client!\n\n";
		ShowClients();
	}

	std::cout << "Successfully added!\n\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	ShowClients();
}

void Terminal::DeleteClient()
{
	if (clients_->size() == 0)
	{
		std::cout << "List is empty!\n\n";
		ShowClients();
	}

	std::cout << "\nDELETING A CLIENT\nInsert client name: \n";
	std::getline(std::cin, command_);
	int index = GetClientIndex(command_);
	if (index >= 0)
	{
		clients_->erase(clients_->begin() + index);
		std::cout << "Successfully deleted!\n\n";
	}
	else
	{
		std::cout << "Error deleting client!\n\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	ShowClients();
}

void Terminal::ShowClients() {
	system("cls");

	std::cout << "\n============== Client list: ==============\n";
	std::cout << "#\tName/Title\t\tAccount count\n";

    if (clients_->size() == 0)
	    std::cout << "Empty\n";
    else {
        for (unsigned int i = 0; i < clients_->size(); i++) {
			std::cout << i + 1 << ")\t" << (*clients_)[i]; //(*clients_)[i]->GetName() << "\t\t" << (*clients_)[i]->GetAccountCount() << '\n';
        }
    }
	std::cout << "\n\n";

	std::cout << "[+] Add new client\n[-] Delete client\n[<number>] Switch to chosen client\n[q] Back\n";
	do {
		getline(std::cin, command_);

		if (command_.compare("+") == 0)
			AddClient();
		else if (command_.compare("-") == 0)
			DeleteClient();
		else if (command_.compare("q") == 0)
			Start();
		else 
		{
			std::getline(std::cin, command_);
			int index = GetClientIndex(command_);
			if (index >= 0)
				ShowClient(index);
		}
	} while (1);
}

void Terminal::ShowClient(int index)
{
	system("cls");

	auto client = (*clients_)[index];
	std::cout << "\nClient:\n\t" << client->GetName() << '\n';
	std::cout << "Accounts:\n";
	for (int i = 0; i < client->GetAccountCount(); i++)
	{
		std::cout << i + 1 << ")\t" << client->GetAccountAtIndex(i).GetBankName() << "\t";
		printf("%5.2f\n", client->GetAccountAtIndex(i).GetFunds());
	}
	std::cout << "----------\nTotal: " << client->GetAccountCount() << '\n';

	std::cout << "\n[+] Deposit funds\n[-] Withdraw funds\n[*] Transfer funds\n[q] Back\n";

	do
	{
		getline(std::cin, command_);

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

void Terminal::DepositFunds(int index)
{
	try
	{
		std::cout << "Insert how much to deposit: ";
		getline(std::cin, command_);
		double sum = stod(command_);

		std::cout << "Input the index of account to add money to: ";
		getline(std::cin, command_);
		int id = stoi(command_);
		if (!(*clients_)[index]->IsIdCorrect(--id))
			throw;

		if ((*clients_)[index]->DepositFunds(sum, id))
			std::cout << "Success!\n\n";
		else
			std::cout << "Error\n\n";
	}
	catch (...)
	{
		std::cout << "Error\n\n";
	}
	
	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	ShowClient(index);
}

void Terminal::WithdrawFunds(int index)
{
	try
	{
		std::cout << "Input how much to withdraw: ";
		getline(std::cin, command_);
		double sum = stod(command_);

		std::cout << "Input the index of account to withdraw money from: ";
		getline(std::cin, command_);
		int id = stoi(command_);
		if (!(*clients_)[index]->IsIdCorrect(--id))
			throw;

		if ((*clients_)[index]->WithdrawFunds(sum, id))
			std::cout << "Success!\n\n";
		else
			std::cout << "Not enough funds to perform this operation!\n\n";
	}
	catch (...)
	{
		std::cout << "Error\n\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	ShowClient(index);
}

void Terminal::TransferFunds(int index)
{
	try
	{
		std::cout << "Input how much to transfer: ";
		getline(std::cin, command_);
		double sum = stod(command_);

		std::cout << "Input the index of account to transfer money from: ";
		getline(std::cin, command_);
		int idFrom = stoi(command_);
		if (!(*clients_)[index]->IsIdCorrect(--idFrom))
			throw;

		std::cout << "Input the index of account to transfer money to: ";
		getline(std::cin, command_);
		int idTo = stoi(command_);
		if (!(*clients_)[index]->IsIdCorrect(--idTo))
			throw;

		if ((*clients_)[index]->TransferFunds(sum, idFrom, idTo))
			std::cout << "Success!\n\n";
		else
			std::cout << "Error\n\n";
	}
	catch (...)
	{
		std::cout << "Error\n\n";
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	ShowClient(index);
}

void Terminal::Start() {
	std::cout << "\n\t=== Welcome! ===\n\tChoose mode:\n"
		<< "[0] Work with banks \n"
		<< "[1] Work with clients\n"
		<< "[q] Exit\n";

	do {
		getline(std::cin, command_);

		if (command_.compare("0") == 0)
			ShowBanks();
		else if (command_.compare("1") == 0)
			ShowClients();
		else if (command_.compare("q") == 0)
			exit(EXIT_SUCCESS);
	} while (1);
}