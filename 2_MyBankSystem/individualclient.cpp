using namespace std;

#include <string>

#include "individualclient.h"
#include "bank.h"
#include "account.h"

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

    accounts_->at(fromId)->WithdrawFunds(amount);
    double forfeit = accounts_->at(fromId)->GetBank()->GetForfeit();
    accounts_->at(fromId)->GetBank()->Charge(amount / 100.0 * forfeit);
    accounts_->at(toId)->DepositFunds(amount / 100.0 * (100 - forfeit));
    return true;
}
