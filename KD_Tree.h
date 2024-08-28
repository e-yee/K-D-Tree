#pragma once

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

    Node() : left(NULL), right(NULL) {}
    Node(Location data) : key(data), left(NULL), right(NULL) {}
};

void setBalance(Node* &root, int depth);

void insertOneCity(Node* &root, Location data, int depth);

void insertListCity(Node* &root, vector<Location> &list, int depth);

void rangeSearch(Node* root, vector<Location> &result, pair<double, double> bot_left,
pair<double, double> top_right, int depth);

void calculateDistanceTest(Node* root, Location query, double &min_distance, Location &result, int depth);

void findNearestNeighbor(Node* root, Location query, double &min_distance, Location &result, 
int depth);

void deleteList(Node* &root);