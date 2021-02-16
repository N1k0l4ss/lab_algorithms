#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string.h>
#include <cstdio>
using namespace std;
const int sl = 15;

struct trains
{
    int number;
    char destination[sl];
    int starttimeMIN;
    int starttimeHOUR;
    char startpoint[sl];
    int coupe;
    int reservedsit;
    int fullquantity;
    trains* next;
};

string path;
void menu(trains* train);
void printbypar(trains* train);
void startfrom(trains* train);
void goingtotime(trains* train);
void printlist(trains* train);
void add(trains* train);
void goingtowitchreserved(trains* train);

void dellist(trains* train) {
    while (train->next) {
        trains* t = train->next;
        train->next = t->next;
        delete t;
    }
}
// done

void trainsdel(trains* train){
    system("cls");
    trains* p;
    p = train->next;
    while (p != NULL)
    {
        printlist(p);
        p = p->next;
    }
    cout << "=======================================================================" << endl;
    cout << "Введите номер поезда, который желаете удалить ";
    int number;
    bool fnumber = false;
    while (true)
    {
        cin >> number;
        p = train->next;
        while (p)
        {
            if (p->number == number)
                fnumber = true;
            if (fnumber)
                break;
            p = p->next;
        }
        if (fnumber)
            break;
        else
            cout << "Неверный ввод, повторите! ";

    }
   

    system("cls");
    
    
    
    //
    if (p->next!=nullptr) {
        p->number = p->next->number;
        p->destination, p->next->destination;
        p->starttimeMIN = p->next->starttimeMIN;
        p->starttimeHOUR = p->next->starttimeHOUR;
        p->startpoint, p->next->startpoint;
        p->coupe = p->next->coupe;
        p->reservedsit = p->next->reservedsit;
        p->fullquantity = p->next->fullquantity;
        trains* t = p->next;
        p->next = p->next->next;
        delete t;
    }
    else {
        trains* t = p;
        delete t;
        t = NULL;
    }
}
//done

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    trains *train = new trains;
    train->next = NULL;
    train->number = 0;
    while (true)
    {
        int sel;
        cout << "Введите\n";
        cout << "1. Чтобы добавить поезд\n";
        cout << "2. Чтобы загрузить список из файла\t\t\t\t";
        cin >> sel;
        if (sel == 1)
        {
            system("cls");
            cout << "Добавьте поезд в список\n";
            add(train);
            break;
        }
        if (sel == 2)
        {
            system("cls");
            //fload(train, size);
            break;
        }
        system("cls");
        cout << "Неверный ввод, повторите!\n";
    }
    menu(train);
    dellist(train);
}
//done

void printbypar(trains *train)
{
    system("cls");
    cout << "=======================================================================" << endl;
    int sel;
    cout << "Введите:\n1 - Чтобы посмотреть поезда, которые отправляются из заданного пункта." << endl;
    cout << "2 - Чтобы посмотреть поезда, которые отправляются в заданный пункт после указанного времени\n";
    cout << "3 - Чтобы посмотреть поезда, которые отправляются в заданный пункт и имеют плацкартные места\t";
    while (true)
    {
        cin >> sel;
        if (sel == 1)
        {
            startfrom(train);
            break;
        }
        if (sel == 2)
        {
            goingtotime(train);
            break;
        }
        if (sel == 3)
        {
            goingtowitchreserved(train);
            break;
        }

        cout << "Неверный ввод, попробуйте снова" << endl;
    }
    menu(train);
}
//done

void goingtowitchreserved(trains* train)
{
    cout << "Введите пункт назначения: ";
    char dest[sl];
    bool founded = false;
    cin.getline(dest, sl);
    cin.getline(dest, sl);
    //
    trains* p;
    p = train;
    while (p->next)
    {
        if (strcmp(p->destination, dest) == 0 && p->reservedsit > 0)
        {
            printlist(p);
            founded = true;
        }
        p = p->next;
    }
    if (!founded)
    {
        cout << "Совпадений не найдено, или неверный ввод" << endl;
    }
}
//done

void goingtotime(trains* train)
{
    cout << "Введите пункт назначения: ";
    char dest[sl];
    bool founded = false;
    int timeHour, timeMin, min;
    cin.getline(dest, sl);
    cin.getline(dest, sl);
    while (true)
    {
        cout << "Время отправления (Часы и минуты через пробел): ";
        cin >> timeHour >> timeMin;
        if ((timeHour >= 0 && timeHour < 24) && (timeMin >= 0 && timeMin < 60))
        {
            break;
        }
        else
        {
            cout << "Неверный ввод времени. Повторите попытку\n";
        }
    }
    min = timeHour * 60 + timeMin;
    //
    trains* p;
    p = train;
    while (p->next)
    {
        if (strcmp(p->destination, dest) == 0 && (p->starttimeHOUR * 60 + p->starttimeMIN) >= min)
        {
            printlist(p);
            founded = true;
        }
        p = p->next;
    }
    if (!founded)
    {
        cout << "Совпадений не найдено, или неверный ввод" << endl;
    }
}
//done

void startfrom(trains* train)
{
    cout << "Введите точку отправления: ";
    char outpoint[sl];
    bool founded = false;
    cin.getline(outpoint, sl);
    cin.getline(outpoint, sl);
    trains* p;
    p = train;
    while(p->next)
    {
        if (strcmp(p->startpoint, outpoint) == 0)
        {
            printlist(p);
            founded = true;
        }
        p = p->next;
    }
    if (!founded)
    {
        cout << "Совпадений не найдено, или неверный ввод" << endl;
    }
}
//done

void add(trains* train)
{
    trains* temp = new trains;
    system("cls");
    cout << "=======================================================================" << endl;
    cout << "Введите данные\n";
    cout << "Пункт назначения: ";
    cin.ignore();
    cin.clear();
    cin.getline(temp->destination, sl);
    cout << "Точка отправления: ";
    cin.getline(temp->startpoint, sl);
    while (true)
    {
        cout << "Время отправления (Часы и минуты через пробел): ";
        cin >> temp->starttimeHOUR >> temp->starttimeMIN;
        if ((temp->starttimeHOUR >= 0 && temp->starttimeHOUR < 24) && (temp->starttimeMIN >= 0 && temp->starttimeMIN < 60))
        {
            break;
        }
        else
        {
            cout << "Неверный ввод времени. Повторите попытку\n";
        }
    }
    cout << "Количество мест купэ: ";
    cin >> temp->coupe;
    cout << "Количество плацкартных мест: ";
    cin >> temp->reservedsit;
    temp->fullquantity = temp->coupe + temp->reservedsit;

    int id = 0;
    trains* vrtmp = train;
    while (vrtmp->next)
    {
        id++;
        vrtmp = vrtmp->next;
    }

    temp->number = id + 1;
    temp->next = train->next;
    train->next = temp;
    system("cls");
} 
//done

void printlist(trains* train)
{
    if (train == NULL) return;
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "Номер: " << train->number << endl;
    cout << "Пункт назначения: " << train->destination << endl;
    cout << "Пункт отправления: " << train->startpoint << endl;
    cout << "Время отправление: " << train->starttimeHOUR << ":" << train->starttimeMIN << endl;
    cout << "Количество мест купэ: " << train->coupe << endl;
    cout << "Количество плацкартный мест: " << train->reservedsit << endl;
    cout << "Всего мест: " << train->fullquantity << endl;
}
// done

void menu(trains* train)
{
    cout << "=======================================================================" << endl;
    cout << "Чтобы посмотреть поезда по по параметру, введите 1\n";
    cout << "Чтобы посмотреть все поезда, введите 2\nЧтобы добавить поезд, введите 3" << endl;
    cout << "Чтобы удалить поезд, введите 4\n";
    cout << "Чтобы сохранить запись в файл, введите 5\n";
    cout << "Чтобы очистить окно, введите 6\n";
    cout << "Чтобы удалить файл, введите 7\n";
    cout << "Чтобы загрузить из файла, введите 8\t\t\t\t";
    int sel;
    while (true)
    {
        cin >> sel;
        if (sel == 1)
        {
            system("cls");
            trains* p;
            p = train;
            while (p->next) 
            {
                printbypar(p);
                p = p->next;
            }
            cout << "-----------------------------------------------------------------------" << endl;
            system("pause");
            system("cls");
            break;
        }
        if (sel == 2)
        {
            system("cls");
            trains* p;
            p = train;
            while (p!=NULL)
            {
                if (p->number!=0)
                    printlist(p);
                p = p->next;
            }
            cout << "-----------------------------------------------------------------------" << endl;
            system("pause");
            system("cls");
            break;
        }
        if (sel == 3)
        {
            add(train);
            break;
        }
        if (sel == 4)
        {
            trainsdel(train);
            break;
        }
        if (sel == 5)
        {
            //fwrite(train);
            break;
        }
        if (sel == 6)
        {
            system("cls");
            break;
        }
        if (sel == 7)
        {
            system("cls");
            cout << "Введите название файла" << endl;
            while (true)
            {
                cin >> path;
                fstream file;
                file.open(path, fstream::in);
                if (!file.is_open())
                {
                    cout << "Файл с таким именем не найден! Повторите попытку\n";
                }
                else
                {
                    file.close();
                    remove(path.c_str());
                    break;
                }
            }
            break;
        }
        if (sel == 8)
        {
            system("cls");
            //fload(train, size);
            break;
        }
        cout << "Неверный ввод, пожалуйста, повторите!\n";
    }
    menu(train);
}
//done, except files