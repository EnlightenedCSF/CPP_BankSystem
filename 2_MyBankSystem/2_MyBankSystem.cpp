#include <stdio.h>
#include <iostream>
#include <locale>

#include "terminal.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	Terminal* terminal = new Terminal();
	terminal->LoadDemoData();
	terminal->ShowDemo();

	terminal->Start();

	delete(terminal);
	return 0;
}
