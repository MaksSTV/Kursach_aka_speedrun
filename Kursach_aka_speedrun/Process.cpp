#include <iostream>
#include <fstream>
#include "Types.h"
#include "Def.h"
using namespace std;
void Sort_Poly(form_mono_list*& p)
{
    if (p->head->next != NULL)
        if ((p->head->a == 0) && (p->head->next->a == 0))
            return;
    mono* prev;
    prev = new mono;
    p->cur = p->head;
    int i = 0;
    while (p->cur != NULL)
    {
        p->cur = p->cur->next;
        i++;
    }
    int len = i;
    int j = 0;
    p->cur = p->head;
    prev = p->head;
    while (j < i - 1)
    {
        if (p->cur->next != NULL)
            if (p->cur->next->p > p->cur->p)
            {
                if (p->cur == p->head)
                {
                    p->head = p->head->next;
                    p->cur->next = p->head->next;
                    p->head->next = p->cur;
                    prev = p->head;
                }
                else
                {
                    prev->next = p->cur->next;
                    p->cur->next = p->cur->next->next;
                    prev->next->next = p->cur;
                    prev = prev->next;
                }
            }
            else
            {
                prev = p->cur;
                p->cur = p->cur->next;
            }
        j++;
        if (j == i - 1)
        {
            i--;
            j = 0;
            p->cur = p->head;
        }
    }
    p->cur = p->head;
    for (i = 0; i < len - 1; i++)
    {
        if (p->cur->next == NULL) break;
        while (p->cur->p == p->cur->next->p)
        {
            len--;
            p->cur->a += p->cur->next->a;
            p->cur->next = p->cur->next->next;
            if (len == i + 1) break;
        }
        p->cur = p->cur->next;
    }
    p->cur = p->head;
    while (p->cur->a == 0)
    {
        p->head = p->cur->next;
        delete p->cur;
        p->cur = p->head;
        len--;
        if (p->cur == NULL) break;
    }
    for (i = 0; i < len - 1; i++)
    {
        if (p->cur == NULL) break;
        if (p->cur->a == 0)
        {
            prev->next = p->cur->next;
            delete p->cur;
            p->cur = prev->next;
        }
        else
        {
            prev = p->cur;
            p->cur = p->cur->next;
        }
    }
    p->last = p->cur;
}
void Get_Poly(form_poly_list pol, form_mono_list*& p, int num, ofstream& f_out) {
    p = new form_mono_list;
    pol.cur = pol.head;
    int i = 1;
    while (i < num) {
        pol.cur = pol.cur->next;
        i++;
        if ((pol.cur == pol.last) && (i < num)) {
            p = NULL;
            return;
        }
    }
    p->head = pol.cur->mon.head;
    p->last = pol.cur->mon.last;
}
void Set_Poly(form_poly_list& pol, form_mono_list*& res) {
    pol.cur = pol.last;
    pol.cur->next = new poly;
    pol.cur = pol.cur->next;
    pol.cur->next = NULL;
    pol.last = pol.cur;
    pol.cur->mon.head = res->head;
    pol.cur->mon.last = res->last;
}
void Sum(form_mono_list*& p1, form_mono_list*& p2, form_mono_list*& res, int sign) {
    res = new form_mono_list;
    res->head = new mono;
    res->cur = res->head;
    p1->cur = p1->head;
    p2->cur = p2->head;
    while (p1->cur != NULL) {
        res->cur->a = p1->cur->a;
        res->cur->p = p1->cur->p;
        res->cur->next = new mono;
        res->cur = res->cur->next;
        p1->cur = p1->cur->next;
    }
    while (p2->cur->next != NULL) {
        res->cur->a = p2->cur->a * sign;
        res->cur->p = p2->cur->p;
        res->cur->next = new mono;
        res->cur = res->cur->next;
        p2->cur = p2->cur->next;
    }
    res->cur->a = p2->cur->a * sign;
    res->cur->p = p2->cur->p;
    res->cur->next = NULL;
    res->last = res->cur;

}
void Multiplication(form_mono_list* p1, form_mono_list* p2, form_mono_list*& res) {
    res = new form_mono_list;
    res->head = new mono;
    res->cur = res->head;
    p1->cur = p1->head;
    p2->cur = p2->head;
    while (p1->cur != NULL)
    {
        while (p2->cur != NULL)
        {
            res->cur->a = p1->cur->a * p2->cur->a;
            res->cur->p = p1->cur->p + p2->cur->p;
            if ((p2->cur->next == NULL) && (p1->cur->next == NULL))
            {
                res->cur->next = NULL;
                res->last = res->cur;
                return;
            }
            else if (p2->cur->next != NULL)
            {
                res->cur->next = new mono;
                res->cur = res->cur->next;
                p2->cur = p2->cur->next;
            }
            else
            {
                res->cur->next = new mono;
                res->cur = res->cur->next;
                p2->cur = p2->head;
                p1->cur = p1->cur->next;
            }
        }
    }
}
void Substitution(form_mono_list* p1, form_mono_list* p2, form_mono_list*& res, form_mono_list*& tmp) {
    int flag = 0;
    res = new form_mono_list;
    form_mono_list* res_0;
    res_0 = new form_mono_list;
    tmp = new form_mono_list;
    res->head = new mono;
    res->cur = res->head;
    res_0->head = new mono;
    res_0->cur = res_0->head;
    tmp->head = new mono;
    tmp->cur = tmp->head;
    p2->cur = p2->head;
    p1->cur = p1->head;
    while (p2->cur->next != NULL)
    {
        res_0->cur->a = p2->cur->a;
        res_0->cur->p = p2->cur->p;
        res_0->cur->next = new mono;
        res_0->cur = res_0->cur->next;
        p2->cur = p2->cur->next;
    }
    res_0->cur->a = p2->cur->a;
    res_0->cur->p = p2->cur->p;
    res_0->cur->next = NULL;
    res_0->last = res_0->cur;
    p2->cur = p2->head;
    while (p2->cur->next != NULL)
    {
        res->cur->a = p2->cur->a;
        res->cur->p = p2->cur->p;
        res->cur->next = new mono;
        res->cur = res->cur->next;
        p2->cur = p2->cur->next;
    }
    res->cur->a = p2->cur->a;
    res->cur->p = p2->cur->p;
    res->cur->next = NULL;
    res->last = res->cur;
    while (p1->cur->next != NULL) {
        for (int i = 1; i < p1->cur->p; i++)
            Multiplication(p2, res, res);
        res->cur = res->head;
        while (res->cur != NULL) {
            res->cur->a = res->cur->a * p1->cur->a;
            res->cur = res->cur->next;
        }
        if (flag == 0) {
            tmp->head = res->head;
            tmp->last = res->last;
            tmp->cur = tmp->last;
            tmp->cur->next = NULL;
            flag = 1;
        }
        else {
            tmp->cur->next = res->head;
            tmp->last = res->last;
            tmp->cur = tmp->last;
            tmp->cur->next = NULL;
        }
        res->head = res_0->head;
        res->last = res_0->last;
        p1->cur = p1->cur->next;
    }
    if (p1->cur->p == 0) {
        tmp->last->next = new mono;
        tmp->last = tmp->last->next;
        tmp->last->p = 0;
        tmp->last->a = p1->cur->a;
        tmp->last->next = NULL;
    }
    else {
        for (int i = 1; i < p1->cur->p; i++)
            Multiplication(p2, res, res);
        res->cur = res->head;
        while (res->cur != NULL) {
            res->cur->a = res->cur->a * p1->cur->a;
            res->cur = res->cur->next;
        }
        if (flag == 0) {
            tmp->head = res->head;
            tmp->last = res->last;
            tmp->cur = tmp->last;
            tmp->cur->next = NULL;
            flag = 1;
        }
        else {
            tmp->cur->next = res->head;
            tmp->last = res->last;
            tmp->cur = tmp->last;
            tmp->cur->next = NULL;
        }
        p1->cur = p1->cur->next;
    }
}
void Keyboard(form_mono_list*& res, ofstream& f_out) {
    float a, p;
    cout << "Input polynom, to complete the input, enter 0.\n";
    f_out << "Input polynom, to complete the input, enter 0.\n";
    res = new form_mono_list;
    mono* prev;
    res->head = new mono;
    res->cur = res->head;
    prev = res->cur;
    cin >> a;
    f_out << a << ' ';
    if (a == 0)
    {
        res->head->a = 0;
        res->head->p = 0;
        f_out << "\n";
        return;
    }
    else
    {
        cin >> p;
        f_out << p << ' ';
        res->head->a = a;
        res->head->p = p;
        res->cur->next = new mono;
        prev = res->cur;
        res->cur = res->cur->next;
    }
    while (true)
    {
        cin >> a;
        f_out << a << ' ';
        if (a == 0)
        {
            res->last = prev;
            prev->next = NULL;
            f_out << "\n";
            return;
        }
        else
        {
            cin >> p;
            f_out << p << ' ';
            res->cur->a = a;
            res->cur->p = p;
            res->cur->next = new mono;
            prev = res->cur;
            res->cur = res->cur->next;
        }
    }
}
void Menu(ofstream& f_out, form_poly_list& pol) {
    int key = -1;
    int flag = 1;
    int num1, num2, pos;
    form_mono_list* p1, * p2, * res, * tmp;
    cout << "\nList of polynoms:\n";
    f_out << "\nList of polynoms:\n";
    Output(pol, f_out);
    while (flag == 1) {
        cout << "Hello, what do you want to do?\n 1) Sum two polynoms\n 2) Substract two polynoms\n 3) Multiplicate two polynoms\n 4) Substitute P(q(x))\n 5) Keyboard input\n 0) Exit the program\n";
        f_out << "Hello, what do you want to do?\n 1) Sum two polynoms\n 2) Substract two polynoms\n 3) Multiplicate two polynoms\n 4) Substitute P(q(x))\n 5) Keyboard input\n 0) Exit the program\n";
        cin >> key;
        f_out << key << "\n";
        switch (key) {
        case 1:
            cout << "Sum: \n";
            f_out << "Sum: \n";
            cout << "Enter the number of the first polynomial \n";
            cin >> num1;
            f_out << "Enter the number of the first polynomial \n" << num1 << "\n";
            Get_Poly(pol, p1, num1, f_out);
            if (p1 == NULL) {
                cout << "Error!!! This number does not exist.\n";
                f_out << "Error!!! This number does not exist.\n";
                break;
            }
            cout << "Enter the number of the second polynomial \n";
            cin >> num2;
            f_out << "Enter the number of the second polynomial \n" << num2 << "\n";
            Get_Poly(pol, p2, num2, f_out);
            if (p2 == NULL) {
                cout << "Error!!! This number does not exist.\n";
                f_out << "Error!!! This number does not exist.\n";
                break;
            }
            Sum(p1, p2, res, 1);
            Sort_Poly(res);
            Set_Poly(pol, res);
            Del_Null(pol, f_out);
            cout << "Summation was completed\n";
            f_out << "Summation was completed\n";
            Output(pol, f_out);
            break;
        case 2:
            cout << "Substraction: \n";
            f_out << "Substraction: \n";
            cout << "Enter the number of the first polynomial \n";
            cin >> num1;
            f_out << "Enter the number of the first polynomial \n" << num1 << "\n";
            Get_Poly(pol, p1, num1, f_out);
            if (p1 == NULL) {
                cout << "Error!!! This number does not exist.\n";
                f_out << "Error!!! This number does not exist.\n";
                break;
            }
            cout << "Enter the number of the second polynomial \n";
            cin >> num2;
            f_out << "Enter the number of the second polynomial \n" << num2 << "\n";
            Get_Poly(pol, p2, num2, f_out);
            if (p2 == NULL) {
                cout << "Error!!! This number does not exist.\n";
                f_out << "Error!!! This number does not exist.\n";
                break;
            }
            Sum(p1, p2, res, -1);
            Sort_Poly(res);
            Set_Poly(pol, res);
            Del_Null(pol, f_out);
            cout << "Substraction was completed\n";
            f_out << "Substraction was completed\n";
            Output(pol, f_out);
            break;
        case 3:
            cout << "Multiplication: \n";
            f_out << "Multiplication: \n";
            cout << "Enter the number of the first polynomial \n";
            cin >> num1;
            f_out << "Enter the number of the first polynomial \n" << num1 << "\n";
            Get_Poly(pol, p1, num1, f_out);
            if (p1 == NULL) {
                cout << "Error!!! This number does not exist.\n";
                f_out << "Error!!! This number does not exist.\n";
                break;
            }
            cout << "Enter the number of the second polynomial \n";
            cin >> num2;
            f_out << "Enter the number of the second polynomial \n" << num2 << "\n";
            Get_Poly(pol, p2, num2, f_out);
            if (p2 == NULL) {
                cout << "Error!!! This number does not exist.\n";
                f_out << "Error!!! This number does not exist.\n";
                break;
            }
            Multiplication(p1, p2, res);
            Sort_Poly(res);
            Set_Poly(pol, res);
            cout << "Multiplication was completed\n";
            f_out << "Multiplication was completed\n";
            Output(pol, f_out);
            break;
        case 4:
            cout << "Substitution: \n";
            f_out << "Substitution: \n";
            cout << "Enter the number of the first polynomial \n";
            cin >> num1;
            f_out << "Enter the number of the first polynomial \n" << num1 << "\n";
            Get_Poly(pol, p1, num1, f_out);
            if (p1->last->p < 0) {
                cout << "Impossible action\n";
                f_out << "Impossible action\n";
                break;
            }
            if (p1 == NULL) {
                cout << "Error!!! This number does not exist.\n";
                f_out << "Error!!! This number does not exist.\n";
                break;
            }
            cout << "Enter the number of the second polynomial \n";
            cin >> num2;
            f_out << "Enter the number of the second polynomial \n" << num2 << "\n";
            Get_Poly(pol, p2, num2, f_out);
            if (p2 == NULL) {
                cout << "Error!!! This number does not exist.\n";
                f_out << "Error!!! This number does not exist.\n";
                break;
            }
            Substitution(p1, p2, res, tmp);
            Sort_Poly(tmp);
            Set_Poly(pol, tmp);
            cout << "Substitution was completed\n";
            f_out << "Substitution was completed\n";
            Output(pol, f_out);
            break;
        case 5:
            cout << "Keyboard input: \n";
            f_out << "Keyboard input: \n";
            Keyboard(res, f_out);
            Sort_Poly(res);
            Set_Poly(pol, res);
            cout << "Keyboard input was completed\n";
            f_out << "Keyboard input was completed\n";
            Output(pol, f_out);
            break;
        case 0:
            cout << "Exit\n";
            f_out << "Exit\n";
            flag = 0;
            break;
        default:
            cout << "Invalid number\n";
            f_out << "Invalid number\n";
            break;
        }
    }
}