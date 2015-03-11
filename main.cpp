using namespace std;

#include <stdio.h>
#include <iostream>
#include <vector>

#include "bank.h"
#include "client.h"
#include "individualclient.h"
#include "legalentity.h"
#include "terminal.h"

int main()
{
    Terminal* terminal = new Terminal();
    terminal->LoadDemoData();
    terminal->ShowDemo();

    terminal->Start();

    delete(terminal);
    return 0;
}
