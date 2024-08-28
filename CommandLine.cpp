#include "CommandLine.h"
#include "KD_Tree.h"

void cmdloadCity(Node*& root) {
    system("cls");
    
    string str_path;
    cout << "Enter file path: ";
    getline(cin, str_path);

    vector<Location> vt_city = readFile(str_path);
    insertListCity(root, vt_city, 0);
    return;
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

    insertOneCity(root, locate, 0);
}

void cmdInsertCitiesFromFile(Node*& root) {
    system("cls");

    string str_path;
    cout << "Enter file path: ";
    getline(cin, str_path);

    vector<Location> vt_location = readFile(str_path);
    insertListCity(root, vt_location, 0);
    return;
}

void cmdConductNearestNeighbor(Node*& root) {
    system("cls");

    string str_info;
    cout << "Enter latitude and longtitude for nearest neighbor search: ";
    getline(cin, str_info);
    stringstream ss(str_info);

    Location query;

    string str_lat;
    getline(ss, str_lat, ':');
    query.point[0] = stod(str_lat);

    string str_lng;
    getline(ss, str_lng, ' ');
    query.point[1] = stod(str_lng);
    
    double min_dis = 1e9;
    Location result;
    findNearestNeighbor(root, query, min_dis, result, 0);

    string str_output;
    getline(ss, str_output);
    if (str_output == "cmd") {
        cout << "======================\n";
        cout << "Result:\n";
        cout << "City: " << result.city << '\n';
        cout << "Country: " << result.country << '\n';
        cout << "Population: " << result.population << '\n'; 
    }
    else {
        ofstream ofs(str_output);
        ofs << "city,country,population\n";
        ofs << result.city << ',' << result.country << ',' << result.population << '\n';
        ofs.close();
    }
}

void cmdQueryRangeSearch(Node*& root) {
    system("cls");

    string str_info;
    cout << "Enter latitudes and longtitudes for range search: ";
    getline(cin, str_info);
    stringstream ss(str_info);

    pair<double, double> bot_left;

    string str_lat1;
    getline(ss, str_lat1, ':');
    bot_left.first = stod(str_lat1);

    string str_lng1;
    getline(ss, str_lng1, ' ');
    bot_left.second = stod(str_lng1);
    
    pair<double, double> top_right;

    string str_lat2;
    getline(ss, str_lat2, ':');
    top_right.first = stod(str_lat2);

    string str_lng2;
    getline(ss, str_lng2, ' ');
    top_right.second = stod(str_lng2);

    if (bot_left.second > top_right.second) swap(bot_left, top_right);

    vector<Location> result;
    rangeSearch(root, result, bot_left, top_right, 0);

    string str_output;
    getline(ss, str_output);
    if (str_output == "cmd") {
        cout << "======================\n";
        cout << "Result:\n";
        for (int i = 0; i < result.size(); i++) {
            cout << i + 1 << "/\n";
            cout << "City: " << result[i].city << '\n';
            cout << "Country: " << result[i].country << '\n';
            cout << "Population: " << result[i].population << '\n';
            cout << "------------------------\n";
        }
    }
    else {
        ofstream ofs(str_output);
        ofs << "city,country,population\n";
        for (int i = 0; i < result.size(); i++) 
            ofs << result[i].city << ',' << result[i].country << ',' << result[i].population << '\n';
        ofs.close();
    }
}