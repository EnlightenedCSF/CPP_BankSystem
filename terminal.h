#ifndef TERMINAL_H
#define TERMINAL_H

#include <vector>
#include <string>

#include "bank.h"
#include "client.h"

class Terminal
{
public:
    Terminal();
    ~Terminal();

    void LoadDemoData();
    void ShowDemo();

    void Start();

private:
    vector<Bank*>* banks_;
    vector<Client*>* clients_;

    string command_;
    bool IsCommandValid(string regexp);

    void ShowBanks();
    void ShowClients();

};

#endif // TERMINAL_H
