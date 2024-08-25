#include "CommandLine.h"

void cmdloadCity(Node*& root) {
    system("cls");
    
    string str_path;
    cout << "Enter file path: ";
    getline(cin, str_path);

    vector<Location> vt_city = readFile(str_path);
}

void cmdInsertCity(Node*& root) {
    system("cls");

    string str_info;
    cout << "Enter city information: ";
    getline(cin, str_info);
    stringstream ss(str_info);
    
    Location locate;

    string str_city;
    getline(ss, str_city, ':');
    locate.city = str_city;

    string str_lat;
    getline(ss, str_lat, ':');
    locate.point[0] = stod(str_lat);

    string str_lng;
    getline(ss, str_lng, ':');
    locate.point[1] = stod(str_lng);

    string str_country;
    getline(ss, str_country, ':');
    locate.country = str_country;

    string str_population;
    getline(ss, str_population, ':');
    locate.population = stoll(str_population);
}

void cmdInsertCitiesFromFile(Node*& root) {
    system("cls");

    string str_path;
    cout << "Enter file path: ";
    getline(cin, str_path);

    vector<Location> vt_location = readFile(str_path);
}

void cmdConductNearestNeighbor(Node*& root) {
    system("cls");

    string str_info;
    cout << "Enter latitude and longtitude for nearest neighbor search: ";
    getline(cin, str_info);
    stringstream ss(str_info);

    double point[2];

    string str_lat;
    getline(ss, str_lat, ':');
    point[0] = stod(str_lat);

    string str_lng;
    getline(ss, str_lng, ' ');
    point[1] = stod(str_lng);
    
    string str_output;
    getline(ss, str_output);
    if (str_output == "cmd") {
        cout << 1;
    }
    else {
        ofstream ofs(str_output);
        ofs.close();
    }
}

void cmdQueryRangeSearch(Node*& root) {
    system("cls");

    string str_info;
    cout << "Enter latitudes and longtitudes for range search: ";
    getline(cin, str_info);
    stringstream ss(str_info);

    double point1[2];

    string str_lat1;
    getline(ss, str_lat1, ':');
    point1[0] = stod(str_lat1);

    string str_lng1;
    getline(ss, str_lng1, ' ');
    point1[1] = stod(str_lng1);
    
    double point2[2];

    string str_lat2;
    getline(ss, str_lat2, ':');
    point2[0] = stod(str_lat2);

    string str_lng2;
    getline(ss, str_lng2, ' ');
    point2[1] = stod(str_lng2);

    string str_output;
    getline(ss, str_output);
    if (str_output == "cmd") {
        cout << 1;
    }
    else {
        ofstream ofs(str_output);
        ofs.close();
    }
}