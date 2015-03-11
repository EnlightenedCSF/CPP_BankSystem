using namespace std;

#include <string>

#include "individualclient.h"

IndividualClient::IndividualClient(string name) : Client(name)
{

}

IndividualClient::~IndividualClient()
{

}

bool IndividualClient::TransferFunds(double amount, int fromId, int toId) {
    return true;
}
