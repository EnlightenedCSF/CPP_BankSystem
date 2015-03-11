using namespace std;

#include <string>

#include "bank.h"

Bank::Bank(string name)
{
    name_ = name;
    funds_ = 0;
}

Bank::~Bank()
{

}

bool Bank::RegisterNewClient(Client *client) {

}
