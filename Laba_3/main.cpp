#include <iostream>
#include <vector>
#include "Human.h"
#include "Member_of_commision.h"
#include "Prepod.h"
#include "Prepod_from_commision.h"

using namespace std;

int main() {

    vector<Human> humans;
    vector<Member_of_commision> members;
    vector<Prepod> prepods;
    vector<Prepod_from_commision> prepod_members;

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1 - Добавить Human\n";
        cout << "2 - Добавить Member_of_commision\n";
        cout << "3 - Добавить Prepod\n";
        cout << "4 - Добавить Prepod_from_commision\n";
        cout << "5 - Показать всех\n";
        cout << "6 - Изменить поле\n";
        cout << "0 - Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) {
            Human h;
            cout << "Введите: name surname birthday\n";
            cin >> h;
            humans.push_back(h);
        }
        else if (choice == 2) {
            Member_of_commision m;
            cout << "Введите: name surname birthday commision_name biography\n";
            cin >> m;
            members.push_back(m);
        }
        else if (choice == 3) {
            Prepod p;
            cout << "Введите: name surname birthday degree position works\n";
            cin >> p;
            prepods.push_back(p);
        }
        else if (choice == 4) {
            Prepod_from_commision pc;
            cout << "Введите: name surname birthday degree position works commision_name biography commision_works\n";
            cin >> pc;
            prepod_members.push_back(pc);
        }
        else if (choice == 5) {
            cout << "\n=== Humans ===\n";
            for (auto &h : humans) cout << h << endl;

            cout << "\n=== Members of commission ===\n";
            for (auto &m : members) cout << m << endl;

            cout << "\n=== Prepods ===\n";
            for (auto &p : prepods) cout << p << endl;

            cout << "\n=== Prepod_from_commision ===\n";
            for (auto &pc : prepod_members) cout << pc << endl;
        }
        else if (choice == 6) {
            cout << "Выберите класс:\n";
            cout << "1 - Human\n2 - Member_of_commision\n3 - Prepod\n4 - Prepod_from_commision\n";
            int cls; cin >> cls;

            if (cls == 1 && !humans.empty()) {
                for (size_t i=0;i<humans.size();i++) cout << i << ": " << humans[i] << endl;
                cout << "Введите индекс: "; size_t idx; cin >> idx;
                if (idx < humans.size()) {
                    string field, value;
                    cout << "Введите поле (name, surname, birthday): "; cin >> field;
                    cout << "Введите новое значение: "; cin >> value;
                    humans[idx].set(field, value);
                }
            }
            else if (cls == 2 && !members.empty()) {
                for (size_t i=0;i<members.size();i++) cout << i << ": " << members[i] << endl;
                cout << "Введите индекс: "; size_t idx; cin >> idx;
                if (idx < members.size()) {
                    string field, value;
                    cout << "Введите поле (name, surname, birthday, commision_name, biography): "; cin >> field;
                    cout << "Введите новое значение: "; cin >> value;
                    members[idx].set(field, value);
                }
            }
            else if (cls == 3 && !prepods.empty()) {
                for (size_t i=0;i<prepods.size();i++) cout << i << ": " << prepods[i] << endl;
                cout << "Введите индекс: "; size_t idx; cin >> idx;
                if (idx < prepods.size()) {
                    string field, value;
                    cout << "Введите поле (name, surname, birthday, degree, position, works): "; cin >> field;
                    cout << "Введите новое значение: "; cin >> value;
                    prepods[idx].set(field, value);
                }
            }
            else if (cls == 4 && !prepod_members.empty()) {
                for (size_t i=0;i<prepod_members.size();i++) cout << i << ": " << prepod_members[i] << endl;
                cout << "Введите индекс: "; size_t idx; cin >> idx;
                if (idx < prepod_members.size()) {
                    string field, value;
                    cout << "Введите поле (name, surname, birthday, degree, position, works, commision_name, biography, commision_works): "; cin >> field;
                    cout << "Введите новое значение: "; cin >> value;
                    prepod_members[idx].set(field, value);
                }
            }
        }
    } while (choice != 0);

    return 0;
}
