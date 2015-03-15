using namespace std;

#include <string>

#include "bank.h"
#include "legalentity.h"

LegalEntity::LegalEntity(string name) : Client(name)
{

}

bool LegalEntity::TransferFunds(double amount, int fromId, int toId) {
    if (!IsIdCorrect(fromId) || !IsIdCorrect(toId))
        return false;

    if (accounts_->at(fromId)->GetFundsAmount() < amount)
        return false;

    accounts_->at(fromId)->WithdrawFunds(amount);
    double forfeit = accounts_->at(fromId)->GetBank()->GetForfeit();
    accounts_->at(fromId)->GetBank()->Charge(amount / 100.0 * forfeit);
    accounts_->at(toId)->DepositFunds(amount / 100.0 * (100 - forfeit));
    return true;
}
