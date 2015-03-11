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

    banks.at(0)->RegisterNewClient(clients.at(0));


    cout << "============== Список банков: ==============\n";
    cout << "#\tНазвание\t\tКоличество клиентов\n";

    if (banks.size() == 0)
        cout << "Банков нет\n";
    else {
        for (unsigned int i = 0; i < banks.size(); i++) {
            cout << i+1 << ")\t" << banks.at(i)->GetName() << "\t\t" << banks.at(i)->GetAccountCount();
        }
    }
    cout << '\n';

    return 0;
}
