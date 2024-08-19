#include <iostream>

#include "K-DTree.h"

using namespace std;

int main() {
    string filename = "worldcities-20210313-population-50000+.csv";
    vector<Location> vt_location = readFile(filename);

    cout << vt_location[0].city << "\n";   
    return 0;
}