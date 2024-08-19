#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Location {
    string city;
    double point[2];//point[0] = lat, point[1] = lng
    string country;
    long long population;
};
struct Node {
    Location key;
    Node* left;
    Node* right;

    Node() {
        left = right = NULL;
    }
};

//1. Prepare the dataset
vector<Location> readFile(string filename);