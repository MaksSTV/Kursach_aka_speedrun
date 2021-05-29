#include <iostream>
#include <fstream>
#include "Types.h"
#include "Def.h"
using namespace std;
void CloseFile(ifstream& f, ofstream& f_out) {
    f.close();
    f_out.close();
}
void Output(form_poly_list& pol, ofstream& f_out) {
    int i = 1;
    pol.cur = pol.head;
    pol.cur->mon.cur = pol.cur->mon.head;
    while (pol.cur->next != NULL) {
        if (pol.cur->mon.cur->a == 0) {
            pol.cur = pol.cur->next;
            pol.cur->mon.cur = pol.cur->mon.head;
            continue;
        }
        f_out << i << ") ";
        cout << i << ") ";
        while (pol.cur->mon.cur->next != NULL) {
            if (pol.cur->mon.cur->next->a > 0) {
                f_out << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p << " + ";
                cout << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p << " + ";
            }
            else {
                f_out << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p << " ";
                cout << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p << " ";
            }
            pol.cur->mon.cur = pol.cur->mon.cur->next;
        }
        f_out << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p;
        cout << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p;
        pol.cur = pol.cur->next;
        pol.cur->mon.cur = pol.cur->mon.head;
        i++;
        f_out << "\n";
        cout << "\n";
    }
        f_out << i << ") ";
        cout << i << ") ";
        while (pol.cur->mon.cur->next != NULL) {
            /*if (pol.cur->mon.cur->a == 0) {
                pol.cur->mon.cur = pol.cur->mon.cur->next;
                continue;
            }*/
            if (pol.cur->mon.cur->next->a > 0) {
                f_out << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p << " + ";
                cout << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p << " + ";
            }
            else {
                f_out << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p << "  ";
                cout << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p << "  ";
            }
            pol.cur->mon.cur = pol.cur->mon.cur->next;
        }
        if (pol.cur->mon.cur->a == 0) {
            f_out << "\n";
            cout << "\n";
            return;
        }
        cout << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p;
        cout << "\n";
        f_out << pol.cur->mon.cur->a << "x^" << pol.cur->mon.cur->p;
        f_out << "\n";
    
}
void Del_Null(form_poly_list& pol, ofstream& f_out)
{
    poly* prev;
    prev = new poly;
    pol.cur = pol.head;
    pol.cur->mon.cur = pol.cur->mon.head;
    if (pol.cur->mon.head == NULL) {
        prev = pol.head->next;
        delete pol.cur;
        pol.head = prev;
        cout << "Polynom is empty!\n";
        f_out << "Polynom is empty!\n";
    }
    while (pol.head->mon.head->a == 0)
    {
        prev = pol.head->next;
        delete pol.head;
        pol.head = prev;
        cout << "Polynom is empty!\n";
        f_out << "Polynom is empty!\n";
    }
    pol.cur = pol.head;
    prev = pol.cur;
    while (pol.cur != pol.last)
    {
        if (pol.cur->mon.head == NULL) {
            prev->next = pol.cur->next;
            delete pol.cur;
            pol.cur = prev->next;

        }
        if (pol.cur->mon.head->a == 0)
        {
            cout << "Polynom is empty!\n";
            f_out << "Polynom is empty!\n";
            prev->next = pol.cur->next;
            delete pol.cur;
        }
        else
            prev = pol.cur;
        pol.cur = prev->next;
    }
    if (pol.cur->mon.head == NULL)
    {
        delete pol.cur;
        pol.last = prev;
        pol.last->next = NULL;
        cout << "Polynom is empty!\n";
        f_out << "Polynom is empty!\n";
    }
    else
        if (pol.cur->mon.head->a == 0)
        {
            delete pol.cur;
            pol.last = prev;
            pol.last->next = NULL;
            cout << "Polynom is empty!\n";
            f_out << "Polynom is empty!\n";
        }
}
void Del_All(form_poly_list& pol)
{
    poly* next_pol;
    mono* next_mon;
    pol.cur = pol.head;
    while (pol.cur != NULL)
    {
        next_pol = pol.cur->next;
        pol.cur->mon.cur = pol.cur->mon.head;
        while (pol.cur->mon.cur != NULL)
        {
            next_mon = pol.cur->mon.cur->next;
            delete pol.cur->mon.cur;
            pol.cur->mon.cur = next_mon;
        }
        delete pol.cur;
        pol.cur = next_pol;
    }

}