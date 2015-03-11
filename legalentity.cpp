using namespace std;

#include <string>

#include "legalentity.h"

LegalEntity::LegalEntity(string name) : Client(name)
{

}

LegalEntity::~LegalEntity()
{

}

bool LegalEntity::TransferFunds(double amount, int fromId, int toId) {
    return true;
}
