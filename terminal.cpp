using namespace std;

#include <iostream>
#include <string>
#include <regex>

#include "individualclient.h"
#include "legalentity.h"
#include "terminal.h"


Terminal::Terminal()
{
    banks_ = new vector<Bank*>();
    clients_ = new vector<Client*>();
}

Terminal::~Terminal()
{
    banks_->clear();
    clients_->clear();

    delete(banks_);
    delete(clients_);
}

void Terminal::LoadDemoData() {
    banks_->push_back(new Bank("Сбербанк", 2));
    banks_->push_back(new Bank("МоскИндБанк", 1));

    clients_->push_back(new IndividualClient("Александр Ольферук"));
    clients_->push_back(new IndividualClient("Машка Старкина"));

    clients_->push_back(new LegalEntity("ВГУ"));

    banks_->at(1)->RegisterNewClient(clients_->at(0));
    banks_->at(1)->RegisterNewClientWithSum(clients_->at(1), 1000);
    banks_->at(1)->RegisterNewClient(clients_->at(0));

    banks_->at(0)->RegisterNewClientWithSum(clients_->at(2), 1000000);
    banks_->at(1)->RegisterNewClientWithSum(clients_->at(2), 1000000);

    banks_->at(0)->RegisterNewClient(clients_->at(0));
}

void Terminal::ShowDemo() {
    if (clients_->at(1)->WithdrawFunds(50, 0))
        cout << clients_->at(1)->GetName() << ": Деньги списаны со счета\n";

    if (!clients_->at(0)->WithdrawFunds(10000000, 0))
        cout << clients_->at(0)->GetName() << ": Ошибка! Недостаточно средств или неверен id!\n";

    if (clients_->at(0)->DepositFunds(900, 0))
        cout << "Ольферук теперь тоже богатенький\n";

    if (clients_->at(0)->TransferFunds(900, 0, 1))
        cout << "Успешно перечислены на другой счет\n";

    if (clients_->at(2)->TransferFunds(500000, 1, 0))
        cout << "А ВГУ может и между банками пересылать денежки!\n";

    if (!clients_->at(0)->TransferFunds(100, 0, 2))
        cout << "Между банками индивидуальному лицу нельзя передать деньги\n";

    cout << "\n\n";
}

bool Terminal::IsCommandValid(string regexp) {
    regex rgx(regexp);
    return regex_match(command_, rgx);
}

void Terminal::ShowBanks() {
    command_ = "";

    cout << "============== Список банков: ==============\n";
    cout << "#\tНазвание\t\tКоличество счетов\t\tCредства банка\n";

    if (banks_->size() == 0)
        cout << "Банков нет\n";
    else {
        for (unsigned int i = 0; i < banks_->size(); i++) {
            cout << i+1 << ")\t" << banks_->at(i)->GetName() << "\t\t" << banks_->at(i)->GetAccountCount()
                 << "\t\t\t\t" << banks_->at(i)->GetFundsAmount() << '\n';
        }
    }
    cout << "\n\n";

    bool isCommandCorrect = true;
    cout << "[+] Добавить новый банк\n[-<номер>] Удалить банк\n[<номер>] Перейти к существующему банку\n[q] Назад\n";
    do {
        getline(cin, command_);

        cout << "ping\n";

        if (IsCommandValid("^(-)(\\d)+$")) {
            cout << "matched!";
            isCommandCorrect = false;
        }

    } while (/*command_.compare("+") && command_.compare("q") &&*/ isCommandCorrect);
}


void Terminal::ShowClients() {
    cout << "============== Список клиентов: ==============\n";
    cout << "#\tИмя/Название\t\tКоличество счетов\n";

    if (clients_->size() == 0)
        cout << "Клиентов нет\n";
    else {
        for (unsigned int i = 0; i < clients_->size(); i++) {
            cout << i+1 << ")\t" << clients_->at(i)->GetName() << "\t\t" << clients_->at(i)->GetAccountCount() << '\n';
        }
    }
    cout << '\n';
}

void Terminal::Start() {
    //string command;

    cout << "Добро пожаловать!\nВыберите режим работы:\n"
         << "[0] Работать с банками \n"
         << "[1] Работать с клиентами\n";

    do {
        getline(cin, command_);

        if (command_.compare("0") == 0)
            ShowBanks();
        else if (command_.compare("1") == 0)
            ShowClients();
    } while (command_.compare("0") && command_.compare("1"));
}
