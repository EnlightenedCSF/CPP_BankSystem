using namespace std;

#include <string>

#include "account.h"
#include "bank.h"
#include "client.h"

Account::Account(Bank *bank, Client *client) {
    bank_ = bank;
    client_ = client;
    funds_ = 0;
}

Account::~Account()
{

}

string Account::GetBankName() {

    return bank_->GetName();
}

string Account::GetClientName() {
    return client_->GetName();
}

double Account::GetFunds()
{
	return funds_;
}

void Account::DepositFunds(double amount) {
    funds_ += amount;
}

bool Account::WithdrawFunds(double amount) {
    if (funds_ - amount < 0)
        return false;

    funds_ -= amount;
    return true;
}

Bank* Account::GetBank() {
    return bank_;
}

Client* Account::GetClient()
{
	return client_;
}

void Account::ClearLinks()
{

}