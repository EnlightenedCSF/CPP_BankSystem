using namespace std;

#include <string>

#include "individualclient.h"
#include "account.h"
#include "bank.h"

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

    Account* account = accounts_->at(fromId);
    Bank* bank = account->GetBank();
    double forfeit = bank->GetForfeit();


  //  accounts_->at(fromId)->GetBank()->Charge(amount / 100.0 * forfeit);
  //  accounts_->at(toId)->DepositFunds(amount / 100.0 * (100 - forfeit));

    return true;
}
