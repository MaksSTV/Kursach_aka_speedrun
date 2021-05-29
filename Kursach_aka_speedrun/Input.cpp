#include <iostream>
#include <fstream>
#include "Types.h"
#include "Def.h"
using namespace std;
void OpenFile(ifstream& f, ofstream& f_out) {
    f.open("in.txt");
    f_out.open("protocol.txt");
}
void Input(form_poly_list& pol, ifstream& f, ofstream& f_out) {
    char sym;
    pol.head = new poly;
    pol.cur = pol.head;
    pol.cur->mon.head = new mono;
    pol.cur->mon.cur = pol.cur->mon.head;
    unsigned pos;
    while (true) {
        if (f.peek() == EOF) {
            f_out << "File empty\n";
            break;
        }
        else {
            while (f.peek() != EOF) {

                f >> pol.cur->mon.cur->a;
                if (pol.cur->mon.cur->a != 0) {
                    f_out << pol.cur->mon.cur->a << ' ';
                    f >> pol.cur->mon.cur->p;
                    f_out << pol.cur->mon.cur->p << ' ';
                    pos = f.tellg();
                    f >> sym;
                    if (sym == pol.mark)
                    {
                        pol.cur->mon.last = pol.cur->mon.cur;
                        pol.cur->mon.cur->next = NULL;
                        f_out << "\n";
                        break;

                    }
                    else {
                        pol.cur->mon.cur->next = new mono;
                        pol.cur->mon.cur = pol.cur->mon.cur->next;
                    }
                    f.seekg(pos, ios::beg);
                }
                else {
                    f >> sym;
                }
                char s = f.get();
                if (f.peek() == pol.mark) {
                    pol.cur->mon.cur->next = NULL;
                    pol.cur->mon.last = pol.cur->mon.cur;
                    f_out << "\n";
                    break;
                }

            }
            if (f.peek() == EOF) {
                pol.last = pol.cur;
                pol.cur->next = NULL;
                return;
            }
            else {

                /*хотим проверить что после маркера конец файла либо есть еще полиномы*/
                if (f.peek() == pol.mark) {
                    f >> sym;
                    pos = f.tellg();
                    f >> sym;
                    if (f.eof())
                    {
                        pol.last = pol.cur;
                        pol.cur->next = NULL;
                        pol.cur->mon.cur->next = NULL;
                        return;
                    }
                    f.seekg(pos, ios::beg);
                }
            }
            pol.cur->next = new poly;
            pol.cur = pol.cur->next;
            pol.cur->mon.head = new mono;
            pol.cur->mon.cur = pol.cur->mon.head;
        }
    }
}
void Sort_Input(form_mono_list*& tmp, form_poly_list& pol) {
    mono* prev;
    prev = new mono;
    pol.cur = pol.head;
    pol.cur->mon.cur = pol.cur->mon.head;
    while (pol.cur->next != NULL) {
        int lenght = 0;
        int i = 0;
        while (pol.cur->mon.cur->next != NULL) {
            i++;
            pol.cur->mon.cur = pol.cur->mon.cur->next;
        }
        i++;
        lenght = i;
        int j = 0;
        pol.cur->mon.cur = pol.cur->mon.head;
        prev = pol.cur->mon.head;
        while (j < i - 1) {
            if (pol.cur->mon.cur->next != NULL)
                if (pol.cur->mon.cur->next->p > pol.cur->mon.cur->p) {
                    if (pol.cur->mon.cur == pol.cur->mon.head)
                    {
                        pol.cur->mon.head = pol.cur->mon.head->next;
                        pol.cur->mon.cur->next = pol.cur->mon.head->next;
                        pol.cur->mon.head->next = pol.cur->mon.cur;
                        prev = pol.cur->mon.head;
                    }
                    else
                    {

                        prev->next = pol.cur->mon.cur->next;
                        pol.cur->mon.cur->next = pol.cur->mon.cur->next->next;
                        prev->next->next = pol.cur->mon.cur;
                        prev = prev->next;
                    }
                }
                else
                {
                    prev = pol.cur->mon.cur;
                    pol.cur->mon.cur = pol.cur->mon.cur->next;
                }
            j++;
            if (j == i - 1)
            {
                i--;
                j = 0;
                pol.cur->mon.cur = pol.cur->mon.head;
            }
        }
        pol.cur->mon.cur = pol.cur->mon.head;
        for (i = 0; i < lenght; i++) {
            if (pol.cur->mon.cur->next == NULL)
                break;
            while (pol.cur->mon.cur->p == pol.cur->mon.cur->next->p) {
                pol.cur->mon.cur->a += pol.cur->mon.cur->next->a;
                lenght--;
                pol.cur->mon.cur->next = pol.cur->mon.cur->next->next;
                if (lenght == i + 1)
                    break;
            }
            pol.cur->mon.cur = pol.cur->mon.cur->next;
        }
        pol.cur->mon.cur = pol.cur->mon.head;
        while (pol.cur->mon.cur->a == 0) {
            pol.cur->mon.head = pol.cur->mon.cur->next;
            delete pol.cur->mon.cur;
            pol.cur->mon.cur = pol.cur->mon.head;
            lenght--;
            if (pol.cur->mon.cur == NULL)
                break;
        }
        for (i = 0; i < lenght; i++)
        {
            if (pol.cur->mon.cur == NULL)
                break;
            if (pol.cur->mon.cur->a == 0)
            {
                prev->next = pol.cur->mon.cur->next;
                delete pol.cur->mon.cur;
                pol.cur->mon.cur = prev->next;
            }
            else
            {
                prev = pol.cur->mon.cur;
                pol.cur->mon.cur = pol.cur->mon.cur->next;
            }
        }
        pol.cur = pol.cur->next;
        pol.cur->mon.cur = pol.cur->mon.head;
    }
    int lenght = 0;
    int i = 0;
    while (pol.cur->mon.cur->next != NULL) {
        i++;
        pol.cur->mon.cur = pol.cur->mon.cur->next;
    }
    i++;
    lenght = i;
    int j = 0;
    pol.cur->mon.cur = pol.cur->mon.head;
    prev = pol.cur->mon.head;
    while (j < i - 1) {
        if (pol.cur->mon.cur->next != NULL)
            if (pol.cur->mon.cur->next->p > pol.cur->mon.cur->p) {
                if (pol.cur->mon.cur == pol.cur->mon.head)
                {
                    pol.cur->mon.head = pol.cur->mon.head->next;
                    pol.cur->mon.cur->next = pol.cur->mon.head->next;
                    pol.cur->mon.head->next = pol.cur->mon.cur;
                    prev = pol.cur->mon.head;
                }
                else
                {

                    prev->next = pol.cur->mon.cur->next;
                    pol.cur->mon.cur->next = pol.cur->mon.cur->next->next;
                    prev->next->next = pol.cur->mon.cur;
                    prev = prev->next;
                }
            }
            else
            {
                prev = pol.cur->mon.cur;
                pol.cur->mon.cur = pol.cur->mon.cur->next;
            }
        j++;
        if (j == i - 1)
        {
            i--;
            j = 0;
            pol.cur->mon.cur = pol.cur->mon.head;
        }
    }
    pol.cur->mon.cur = pol.cur->mon.head;
    for (i = 0; i < lenght; i++) {
        if (pol.cur->mon.cur->next == NULL)
            break;
        while (pol.cur->mon.cur->p == pol.cur->mon.cur->next->p) {
            pol.cur->mon.cur->a += pol.cur->mon.cur->next->a;
            lenght--;
            pol.cur->mon.cur->next = pol.cur->mon.cur->next->next;
            if (lenght == i + 1)
                break;
        }
        pol.cur->mon.cur = pol.cur->mon.cur->next;
    }
    pol.cur->mon.cur = pol.cur->mon.head;
    while (pol.cur->mon.cur->a == 0) {
        pol.cur->mon.head = pol.cur->mon.cur->next;
        delete pol.cur->mon.cur;
        pol.cur->mon.cur = pol.cur->mon.head;
        lenght--;
        if (pol.cur->mon.cur == NULL)
            break;
    }
    for (i = 0; i < lenght; i++)
    {
        if (pol.cur->mon.cur == NULL)
            break;
        if (pol.cur->mon.cur->a == 0)
        {
            prev->next = pol.cur->mon.cur->next;
            delete pol.cur->mon.cur;
            pol.cur->mon.cur = prev->next;
        }
        else
        {
            prev = pol.cur->mon.cur;
            pol.cur->mon.cur = pol.cur->mon.cur->next;
        }
    }
}