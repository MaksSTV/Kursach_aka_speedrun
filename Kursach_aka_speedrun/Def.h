#ifndef Def_h
#define Def_h
#pragma once
#include <iostream>
#include <fstream>
#include "Types.h"
using namespace std;
void OpenFile(ifstream& f, ofstream& f_out);
void CloseFile(ifstream& f, ofstream& f_out);
void Input(form_poly_list& pol, ifstream& f, ofstream& f_out);
void Output(form_poly_list& pol, ofstream& f_out);
void Sort_Input(form_mono_list*& tmp, form_poly_list& pol);
void Sort_Poly(form_mono_list*& p);
void Get_Poly(form_poly_list pol, form_mono_list*& p, int num, ofstream& f_out);
void Set_Poly(form_poly_list& pol, form_mono_list*& res);
void Del_Null(form_poly_list& pol, ofstream& f_out);
void Sum(form_mono_list*& p1, form_mono_list*& p2, form_mono_list*& res, int sign);
void Multiplication(form_mono_list* p1, form_mono_list* p2, form_mono_list*& res);
void Substitution(form_mono_list* p1, form_mono_list* p2, form_mono_list*& res, form_mono_list*& tmp);
void Keyboard(form_mono_list*& res, ofstream& f_out);
void Menu(ofstream& f_out, form_poly_list& pol);
void Del_All(form_poly_list& pol);
#endif // !Def_h