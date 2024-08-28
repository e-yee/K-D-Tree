#include "File.h"

#define EMPTY "NULL"

Location getLocation(string data) {
    Location location;
    stringstream ss(data);

    string str_city;
    getline(ss, str_city, ',');
    location.city = str_city;

    string str_lat;
    getline(ss, str_lat, ',');
    location.point[0] = stod(str_lat);

    string str_lng;
    getline(ss, str_lng, ',');
    location.point[1] = stod(str_lng);

    string str_country;
    getline(ss, str_country, ',');
    if (str_country[0] == '"') {
        str_country.erase(0, 1);

        string str_country_tmp;
        getline(ss, str_country_tmp, ',');
        str_country_tmp.erase(str_country_tmp.size() - 1, 1);

        str_country += str_country_tmp;
    }
    location.country = str_country;

    string str_population;
    getline(ss, str_population);
    location.population = stoll(str_population);

    return location;
}

vector<Location> readFile(string filename) {
    vector<Location> vt_location;

    ifstream ifs(filename.c_str());
    if (!ifs.good()) {
        cout << "Failed to open " << filename << "\n";
        return vt_location;
    }

    string str_ignore;
    getline(ifs, str_ignore);

    string str_data;
    Location p;
    while (!ifs.eof()) {
        getline(ifs, str_data);
        p = getLocation(str_data);

        vt_location.push_back(p);
    }

    ifs.close();
    return vt_location;
}

void serialize(Node* root, ofstream &ofs)
{
    if (root == NULL)
    {
        ofs << EMPTY << '\n';
        return;
    }

    ofs << root->key.city << ',' << root->key.point[0] << ',' << root->key.point[1] 
    << ',' << root->key.country << ',' << root->key.population << '\n';
    serialize(root->left, ofs);
    serialize(root->right, ofs);
    return;
}


void deserialize(Node*& root, ifstream &ifs)
{
    string line;
    getline(ifs, line, '\n');
    if (line == EMPTY)
    {
        root = NULL;
        return;
    }

    Location data = getLocation(line);

    root = new Node(data);
    deserialize(root->left, ifs);
    deserialize(root->right, ifs);
    return;
}