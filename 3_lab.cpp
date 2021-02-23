#include <iostream>
using namespace std;

template <typename T>
class List {
private:
    struct MyStruct {
        T x;
        MyStruct* next;
        MyStruct* prev;
    };
    MyStruct* head;
public:
    List() { head = new MyStruct; head->prev = NULL; head->next = NULL; }
    ~List() {
        while (head->next) {
            MyStruct* t = head->next;
            head->next = t->next;
            delete t;
        }
    }

    void app(T value) {
        MyStruct* tmp = new MyStruct;
        tmp->x = value;
        tmp->next = head->next;
        tmp->prev = head;
        if (head->next)
            head->next->prev = tmp;
        head->next = tmp;
    }

    void app(T value, T beforeThe) {
        MyStruct* p = head->next;
        while (p && beforeThe != p->x)
            p = p->next;
        MyStruct* tmp = new MyStruct;
        tmp->x = value;
        tmp->next = p;
        tmp->prev = p->prev;
        p->prev->next = tmp;
        p->prev = tmp;
    }

    void print() {
        MyStruct* p = head->next;
        while (p != NULL) {
            cout << p->x << '\t';
            p = p->next;
        }
        cout << endl;
    }
};

int main() {
    setlocale(0, "");
    List<int> arr;
    for (int i = 0; i < 10; i++) {
        arr.app(i + 1);
    }
    arr.print();
    cout << "Добавить перед: ";
    int value, beforeThe;
    cin >> beforeThe;
    cout << "\nЗначение: ";
    cin >> value;
    arr.app(value, beforeThe);
    arr.print();
    return 0;
}
