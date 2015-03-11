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
    banks.push_back(new Bank("МоскИндБанк"));

    vector<Client*> clients;
    clients.push_back(new IndividualClient("Александр Ольферук"));
    clients.push_back(new IndividualClient("Машка Старкина"));

    clients.push_back(new LegalEntity("ВГУ"));

    banks.at(1)->RegisterNewClient(clients.at(0));
    banks.at(1)->RegisterNewClientWithSum(clients.at(1), 1000);
    banks.at(1)->RegisterNewClient(clients.at(0));

    banks.at(0)->RegisterNewClientWithSum(clients.at(2), 1000000);
    banks.at(1)->RegisterNewClientWithSum(clients.at(2), 1000000);

    banks.at(0)->RegisterNewClient(clients.at(0));

    if (clients.at(1)->WithdrawFunds(50, 0))
        cout << clients.at(1)->GetName() << ": Деньги списаны со счета\n";

    if (!clients.at(0)->WithdrawFunds(10000000, 0))
        cout << clients.at(0)->GetName() << ": Ошибка! Недостаточно средств или неверен id!\n";

    if (clients.at(0)->DepositFunds(900, 0))
        cout << "Ольферук теперь тоже богатенький\n";

    if (clients.at(0)->TransferFunds(900, 0, 1))
        cout << "Успешно перечислены на другой счет\n";

    if (clients.at(2)->TransferFunds(500000, 1, 0))
        cout << "А ВГУ может и между банками пересылать денежки!\n";

    if (!clients.at(0)->TransferFunds(100, 0, 2))
        cout << "Между банками индивидуальному лицу нельзя передать деньги\n";

    cout << "\n\n";

    cout << "============== Список банков: ==============\n";
    cout << "#\tНазвание\t\tКоличество счетов\t\tCредства банка\n";

    if (banks.size() == 0)
        cout << "Банков нет\n";
    else {
        for (unsigned int i = 0; i < banks.size(); i++) {
            cout << i+1 << ")\t" << banks.at(i)->GetName() << "\t\t" << banks.at(i)->GetAccountCount()
                 << "\t\t\t\t" << banks.at(i)->GetFundsAmount() << '\n';
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
