using namespace std;

#include <stdio.h>
#include <iostream>
#include <vector>

#include "bank.h"
#include "client.h"
#include "individualclient.h"
#include "legalentity.h"

int main()
{
    vector<Bank*> banks;
    banks.push_back(new Bank("Sberbank"));

    vector<Client*> clients;
    clients.push_back(new IndividualClient("Vasilii Pupkin"));
    clients.push_back(new LegalEntity("OOO \"Gasprom\""));

    cout << banks.size() << '\n' << clients.size() << '\n';
    return 0;
}
