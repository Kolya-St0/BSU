#include <iostream>
#include <list>
#include <map>
#include <iterator>
#include <algorithm>
#include <QList>
#include <QDebug>
#include <QtAlgorithms>

using namespace std;

void menu() {
    cout << endl;
    cout << "1. Check list state" << endl;
    cout << "2. Add element" << endl;
    cout << "3. Add many elements" << endl;
    cout << "4. Delete element" << endl;
    cout << "5. Delete by condition" << endl;
    cout << "6. Replace element" << endl;
    cout << "7. Check if the input list is a subset of the original list" << endl;
    cout << "8. Move elements from other list" << endl;
    cout << "9. Exit" << endl;
    cout << endl;
}

void printQList(const QList<int>& qList) {
    for (const auto& item : qList) {
        cout << item << " ";
    }
    cout << endl;
}

QList<int> stdListToQList(const list<int>& stdList) {
    return QList<int>(stdList.begin(), stdList.end());
}

list<int> qListToStdList(const QList<int>& qList) {
    return list<int>(qList.begin(), qList.end());
}

int main() {
    list<int> initialList{1, 2, 3, 4, 5};
    QList<int> mainQList = stdListToQList(initialList);
    QList<int> otherQList;
    map<int, int> mainmap;

    srand(time(0));
    for (int i = 0; i < 10; i++) {
        mainmap[rand() % 100] = rand() % 100;
    }

    cout << "Random generated map keys and values: " << endl;
    for (const auto& pair : mainmap) {
        cout << "Key: " << pair.first << " Value: " << pair.second << endl;
    }

    int choice;
    while (true) {
        menu();
        cout << "Choose menu option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "List state: ";
            printQList(mainQList);
            break;

        case 2: {
            int element;
            cout << "Enter element to add: ";
            cin >> element;
            mainQList.append(element);
            break;
        }

        case 3: {
            int n, element;
            cout << "Enter amount of elements to add: ";
            cin >> n;
            cout << "Enter "<<n<<" elements to add: ";
            while (n > 0) {
                cin >> element;
                mainQList.append(element);
                n--;
            }
            break;
        }

        case 4: {
            int element;
            cout << "Enter element to delete: ";
            cin >> element;
            mainQList.removeAll(element);
            break;
        }

        case 5: {
            int number;
            cout << "Enter number to delete elements greater than it: ";
            cin >> number;
            mainQList.erase(std::remove_if(mainQList.begin(), mainQList.end(),
                    [number](int x){ return x > number; }), mainQList.end());
            break;
        }

        case 6: {
            int oldvalue, newvalue;
            cout << "Enter value to replace: ";
            cin >> oldvalue;
            cout << "Enter new value: ";
            cin >> newvalue;
            std::replace(mainQList.begin(), mainQList.end(), oldvalue, newvalue);
            break;
        }

        case 7: {
            otherQList.clear();
            cout << "Enter elements for other list (end with -1): ";
            int element;
            while (cin >> element && element != -1) {
                otherQList.append(element);
            }

            QList<int> sortedMain = mainQList;
            QList<int> sortedOther = otherQList;
            std::sort(sortedMain.begin(), sortedMain.end());
            std::sort(sortedOther.begin(), sortedOther.end());

            bool check = std::includes(sortedMain.begin(), sortedMain.end(),
                                    sortedOther.begin(), sortedOther.end());

            if (check) {
                cout << "The input list is a subset of the original list" << endl;
            } else {
                cout << "The input list isn't a subset of the original list" << endl;
            }
            break;
        }

        case 8: {
            otherQList.clear();
            cout << "Enter other list elements to add (end with -1): ";
            int element;
            while (cin >> element && element != -1) {
                otherQList.append(element);
            }
            mainQList.append(otherQList);
            break;
        }

        case 9: {
            list<int> finalList = qListToStdList(mainQList);
            cout << "Exit" << endl;
            return 0;
        }

        default:
            cout << "Invalid input, try again" << endl;
            break;
        }
    }
}
