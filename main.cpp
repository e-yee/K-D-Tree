#include <iostream>

#include "KD_Tree.h"
#include "CommandLine.h"

using namespace std;

int main() {
    string str_continue;
    Node* root = NULL;
    do {
        system("cls");
        
        cout << "                                   Command Line Options\n"
            << "0. Exit\n"
            << "1. Load the list of cities from a CSV file.\n"
            << "2. Insert a new city into the KD-Tree directly via the command line.\n"
            << "3. Insert multiple new cities into the KD-Tree from a specified CSV file path.\n"
            << "4. Conduct a nearest neighbor search by providing latitude and longitude coordinates\n"
            << "5. Query all cities within a specified rectangular region defined by its geographical boundaries.\n"
            << "====================================================================================================\n"
            << "Choose option: ";

        int option = -1;
        do {
            cin >> option;
            if (option < 0 || option > 5)
                cout << "Option is invalid, please choose another option!\n"
                    << "Choose option: ";
        } while (option < 0 || option > 5);
        cin.ignore();

        switch (option) {
            case 0:
                system("cls");
                cout << "Exit\n";
                return 0;
            case 1:
                cmdloadCity(root);
                break;
            case 2:
                cmdInsertCity(root);
                break;
            case 3:
                cmdInsertCitiesFromFile(root);
                break;
            case 4:
                cmdConductNearestNeighbor(root);
                break;
            case 5:
                cmdQueryRangeSearch(root);
                break;
        }

        cout << "Do you want to continue (Yes/No): ";
        getline(cin, str_continue);
    } while (str_continue == "Yes");

    cout << "Exit\n";
    return 0;
}