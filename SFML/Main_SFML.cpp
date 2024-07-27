// SFML.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
// SFML.cpp : This file contains the 'main' function. Program execution begins and ends there.f

#include <iostream>
#include "WinClass.h"

using namespace std;

WinClass winClass_;

int main()
{
    srand(static_cast<unsigned>(time(NULL)));
    winClass_.falling_square();

    return 0;
}


