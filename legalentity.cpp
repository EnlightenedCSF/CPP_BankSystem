using namespace std;

#include <string>

#include "legalentity.h"

LegalEntity::LegalEntity(string name) : Client(name)
{

}

bool LegalEntity::TransferFunds(double amount, int fromId, int toId) {
    if (!IsIdCorrect(fromId) || !IsIdCorrect(toId))
        return false;

    if (accounts_->at(fromId)->GetFundsAmount() < amount)
        return false;

    accounts_->at(toId)->DepositFunds(amount);
    accounts_->at(fromId)->WithdrawFunds(amount);
    return true;
}
