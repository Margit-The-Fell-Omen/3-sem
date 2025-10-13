#include <iostream>
#include <vector>
#include "Human.h"
#include "Member_of_commision.h"
#include "Prepod.h"
#include "Prepod_from_commision.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    vector<Human*> people;
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1 - Добавить Human\n";
        cout << "2 - Добавить Member_of_commision\n";
        cout << "3 - Добавить Prepod\n";
        cout << "4 - Добавить Prepod_from_commision\n";
        cout << "5 - Показать всех\n";
        cout << "0 - Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) {
            Human* h = new Human();
            cout << "Введите: name surname birthday\n";
            cin >> *h;
            people.push_back(h);
        }
        else if (choice == 2) {
            Member_of_commision* m = new Member_of_commision();
            cout << "Введите: name surname birthday commision_name biography\n";
            cin >> *m;
            people.push_back(m);
        }
        else if (choice == 3) {
            Prepod* p = new Prepod();
            cout << "Введите: name surname birthday degree position works\n";
            cin >> *p;
            people.push_back(p);
        }
        else if (choice == 4) {
            Prepod_from_commision* pc = new Prepod_from_commision();
            cout << "Введите: name surname birthday degree position works commision_name biography commision_works\n";
            cin >> *pc;
            people.push_back(pc);
        }
        else if (choice == 5) {
            if (!people.empty()) {
                cout << "\nСписок объектов:\n";
                people[0]->printHeader(cout);
                cout << endl;
                for (auto p : people) {
                    cout << *p << endl;
                }
            } else {
                cout << "Список пуст.\n";
            }
        }
    } while (choice != 0);

    for (auto p : people) delete p;
    return 0;
}
