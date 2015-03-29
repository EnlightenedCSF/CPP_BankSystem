#include <string>

#include "individualclient.h"
#include "bank.h"
#include "account.h"

IndividualClient::IndividualClient(std::string name) : Client(name)
{

}

bool IndividualClient::TransferFunds(double amount, int fromId, int toId) {
	if (!IsIdCorrect(fromId) || !IsIdCorrect(toId))
		return false;

	if ((*accounts_)[fromId]->GetBankName().compare((*accounts_)[toId]->GetBankName()) != 0)
		return false;

	if ((*accounts_)[fromId]->GetFundsAmount() < amount)
		return false;

	(*accounts_)[fromId]->WithdrawFunds(amount);
	double forfeit = (*accounts_)[fromId]->GetBank().GetForfeit();
	(*accounts_)[fromId]->GetBank().Charge(amount / 100.0 * forfeit);
	(*accounts_)[toId]->DepositFunds(amount / 100.0 * (100 - forfeit));
	return true;
}