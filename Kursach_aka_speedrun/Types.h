#pragma once
#ifndef Types
#define Types

struct mono
{
	float a;
	int p;
	mono* next;
};

struct form_mono_list
{
	mono* head, * cur, * last;
};

struct poly
{
	form_mono_list mon;
	poly* next;
};

struct form_poly_list
{
	poly* head, * cur, * last;
	char mark = '@';
};
#endif // !Types