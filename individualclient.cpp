using namespace std;

#include <string>

#include "individualclient.h"

IndividualClient::IndividualClient(string name) : Client(name)
{

}

bool IndividualClient::TransferFunds(double amount, int fromId, int toId) {
    if (!IsIdCorrect(fromId) || !IsIdCorrect(toId))
        return false;

    if (accounts_->at(fromId)->GetBankName().compare(accounts_->at(toId)->GetBankName()) != 0)
        return false;

    if (accounts_->at(fromId)->GetFundsAmount() < amount)
        return false;

    accounts_->at(toId)->DepositFunds(amount);
    accounts_->at(fromId)->WithdrawFunds(amount);
    return true;
}
