// Kursach_aka_speedrun.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "Types.h"
#include "Def.h"
using namespace std;

int main()
{
    ifstream f;
    ofstream f_out;
    form_poly_list pol;
    form_mono_list *sort;
    setlocale(LC_ALL, "");
    OpenFile(f, f_out);
    Input(pol,f, f_out);
    Output(pol, f_out);
    Del_Null(pol,f_out);
    Sort_Input(sort, pol);
    Del_Null(pol,f_out);
    Menu(f_out, pol);
    Del_All(pol);
    CloseFile(f, f_out);
    system("pause");
    return 0;
}