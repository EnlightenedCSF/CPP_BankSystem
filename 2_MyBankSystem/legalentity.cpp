#include <string>

#include "bank.h"
#include "legalentity.h"

LegalEntity::LegalEntity(std::string name) : Client(name)
{

}

bool LegalEntity::TransferFunds(double amount, int fromId, int toId) {
    if (!IsIdCorrect(fromId) || !IsIdCorrect(toId))
        return false;

	if ((*accounts_)[fromId]->GetFundsAmount() < amount)
        return false;

	(*accounts_)[fromId]->WithdrawFunds(amount);
	double forfeit = (*accounts_)[fromId]->GetBank().GetForfeit();
	(*accounts_)[fromId]->GetBank().Charge(amount / 100.0 * forfeit);
	(*accounts_)[toId]->DepositFunds(amount / 100.0 * (100 - forfeit));
    return true;
}