#ifndef Types
#define Types
#pragma once
#include <iostream>
#include <fstream>
using namespace std;

struct Poli {
	form_monom mon;
	Poli *next;
};
struct Form_poli {
	Poli *head, *cur, *last;
	char mark = '@';
};
struct monom {
	float a;
	float p;
	monom *next;
};
struct form_monom {
	monom *head, *cur, *last;
};

#endif // !Types