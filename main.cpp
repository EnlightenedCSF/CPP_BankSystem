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
    banks.push_back(new Bank("Сбербанк"));
    banks.push_back(new Bank("МИБ"));

    vector<Client*> clients;
    clients.push_back(new IndividualClient("Александр Ольферук"));
    clients.push_back(new IndividualClient("Машка Старкина"));

    banks.at(1)->RegisterNewClient(clients.at(0));
    banks.at(1)->RegisterNewClientWithSum(clients.at(1), 1000);

    if (clients.at(1)->WithdrawFunds(50, 0))
        cout << clients.at(1)->GetName() << ": Деньги списаны со счета\n";
    else
        cout << clients.at(1)->GetName() << ": Ошибка! Недостаточно средств или неверен id!\n";

    if (clients.at(0)->WithdrawFunds(10000, 0))
        cout << clients.at(0)->GetName() << ": Деньги списаны со счета\n";
    else
        cout << clients.at(0)->GetName() << ": Ошибка! Недостаточно средств или неверен id!\n";


    cout << "============== Список банков: ==============\n";
    cout << "#\tНазвание\t\tКоличество клиентов\n";

    if (banks.size() == 0)
        cout << "Банков нет\n";
    else {
        for (unsigned int i = 0; i < banks.size(); i++) {
            cout << i+1 << ")\t" << banks.at(i)->GetName() << "\t\t" << banks.at(i)->GetAccountCount() << '\n';
        }
    }
    cout << "\n\n";


    cout << "============== Список клиентов: ==============\n";
    cout << "#\tИмя/Название\t\tКоличество счетов\n";

    if (clients.size() == 0)
        cout << "Клиентов нет\n";
    else {
        for (unsigned int i = 0; i < clients.size(); i++) {
            cout << i+1 << ")\t" << clients.at(i)->GetName() << "\t\t" << clients.at(i)->GetAccountCount() << '\n';
        }
    }
    cout << '\n';


    return 0;
}
