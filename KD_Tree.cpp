#include "KD_Tree.h"
#include <algorithm>
#include <cmath>
#define DIMENSION 2

using namespace std;

int getHeight(Node* root) 
{
    if (root == NULL) return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

int getBalanceFactor(Node* root) 
{
    if (root == NULL) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

void getSubList (Node* root, vector<Location> &sublist)
{
    if (root == NULL) return;

    getSubList(root->left, sublist);
    getSubList(root->right, sublist);
    sublist.push_back(root->key);
    return;
}

// Rebalancing The Tree
void setBalance(Node* &root, int depth) 
{
    if (root == NULL) return;
    setBalance(root->left, depth + 1);
    setBalance(root->right, depth + 1);

    int balance = getBalanceFactor(root);

    if (balance >= -1 && balance <= 1) return;

    vector<Location> sublist;
    getSubList(root, sublist);
    deleteList(root);
    insertListCity(root, sublist, depth);
    return;
}

// Insert One City Into A KD_Tree
void insertOneCity(Node* &root, Location data, int depth)
{
    if (root == NULL)
    {
        root = new Node(data);
        return; 
    }

    if (data.point[depth % DIMENSION] < root->key.point[depth % DIMENSION]) 
        insertOneCity(root->left, data, depth + 1);
    else insertOneCity(root->right, data, depth + 1);
}

// Sort Condition For Node In X Axis
bool sortInXAxis(Location a, Location b) {
    return a.point[0] < b.point[0];
}

// Sort Condition For Node In Y Axis
bool sortInYAxis(Location a, Location b) {
    return a.point[1] < b.point[1];
}

// Insert Multiple Cities Into A KD_Tree
void insertListCity(Node* &root, vector<Location> &list, int depth) {
    if (list.empty()) return;

    int axis = depth % DIMENSION;

    // Sort The List By Axis
    if (axis == 0)
        sort(list.begin(), list.end(), sortInXAxis);
    else sort(list.begin(), list.end(), sortInYAxis);

    // Choose The Middle Element As A Median And Add It Into Tree
    int median = list.size() / 2;
    insertOneCity(root, list[median], depth);

    // Seperate The List Into 2 Sublists Left And Right
    vector<Location> left(list.begin(), list.begin() + median);
    vector<Location> right(list.begin() + median + 1, list.end());

    insertListCity(root->left, left, depth + 1);
    insertListCity(root->right, right, depth + 1);
    return;
}

// Search Cities Inside The Given Range
void rangeSearch(Node* root, vector<Location> &result, pair<double, double> bot_left,
pair<double, double> top_right, int depth)
{
    if (root == NULL) return;

    // Traverse Through All The Node In Tree
    rangeSearch(root->left, result, bot_left, top_right, depth);
    rangeSearch(root->right, result, bot_left, top_right, depth);

    if (root->key.point[1] >= bot_left.second && root->key.point[1] <= top_right.second)
    {
        if (bot_left.first > top_right.first)
        {
            if (root->key.point[0] >= bot_left.first && root->key.point[0] <= 180)
                result.push_back(root->key);

            if (root->key.point[0] >= -180 && root->key.point[0] <= top_right.first)
                result.push_back(root->key);
        } else {
            if (root->key.point[0] >= bot_left.first && root->key.point[0] <= top_right.first)
                result.push_back(root->key);
        }
    } 

    return;
}

// Calculate The Distance Between Location src And dst
double calculateDistance(Location src, Location dst)
{
    // Using Haversine Formula
    double dlat = (src.point[0] - dst.point[0]) * M_PI / 180.0;
    double dlon = (src.point[1] - dst.point[1]) * M_PI / 180.0;

    src.point[0] = src.point[0] * M_PI / 180.0;
    dst.point[0] = dst.point[0] * M_PI / 180.0;

    double a = pow(sin(dlat / 2), 2) + pow(sin(dlon / 2), 2) * cos(src.point[0]) * cos(dst.point[0]);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void calculateDistanceTest(Node* root, Location query, double &min_distance, Location &result, int depth)
{
    if (root == NULL) return;
    calculateDistanceTest(root->left, query, min_distance, result, depth + 1);
    calculateDistanceTest(root->right, query, min_distance, result, depth + 1);

    double dis = calculateDistance(root->key, query);
    if (dis < min_distance) {
        min_distance = dis;
        result = root->key;
    }
    return;
}

void calculateDistanceInAnotherRegion(Node* root, Location query, double &min_distance,
Location &result, int depth)
{
    if (root == NULL) return;

    double dis = calculateDistance(root->key, query);
    if (dis < min_distance) {
        min_distance = dis;
        result = root->key;
    }

    int axis = depth % DIMENSION;
    if (axis == 0) // X Axis
    {
        if (abs(query.point[depth % DIMENSION]) < abs(root->key.point[depth % DIMENSION]))
        calculateDistanceInAnotherRegion(root->left, query, min_distance, result, depth + 1);
    else calculateDistanceInAnotherRegion(root->right, query, min_distance, result, depth + 1);
    } else {
        if (query.point[depth % DIMENSION] < root->key.point[depth % DIMENSION])
        calculateDistanceInAnotherRegion(root->left, query, min_distance, result, depth + 1);
    else calculateDistanceInAnotherRegion(root->right, query, min_distance, result, depth + 1);
    }
    return;
}

// Find Nearest City From The Given Point
void findNearestNeighbor(Node* root, Location query, double &min_distance, Location &result, int depth)
{
    if (root == NULL) return;

    double dis = calculateDistance(root->key, query);
    if (dis < min_distance) {
        min_distance = dis;
        result = root->key;
    }

    int axis = depth % DIMENSION;

    if (query.point[axis] < root->key.point[axis])
    {
        findNearestNeighbor(root->left, query, min_distance, result, depth + 1);
        
        double distance_from_other_region;
        if (axis == 0)
        {   
            Location temp;
            temp.point[0] = -90;
            temp.point[1] = query.point[1];

            double dis1 = calculateDistance(temp, query);
            double dis2 = calculateDistance(root->key, query);

            distance_from_other_region = min(dis1, dis2);
        } else {
            Location temp;
            temp.point[0] = query.point[0];
            temp.point[1] = -180;

            double dis1 = calculateDistance(temp, query);
            double dis2 = calculateDistance(root->key, query);
            distance_from_other_region = min(dis1, dis2);
        }
        if (distance_from_other_region < min_distance)
            calculateDistanceInAnotherRegion(root->right, query, min_distance, result, depth + 1);
    }
    else {
        findNearestNeighbor(root->right, query, min_distance, result, depth + 1);

        int distance_from_other_region;
        if (axis == 0)
        {   
            Location temp;
            temp.point[0] = 90;
            temp.point[1] = query.point[1];

            double dis1 = calculateDistance(temp, query);
            double dis2 = calculateDistance(root->key, query);

            distance_from_other_region = min(dis1, dis2);
        } else {
            Location temp;
            temp.point[0] = query.point[0];
            temp.point[1] = 180;

            double dis1 = calculateDistance(temp, query);
            double dis2 = calculateDistance(root->key, query);
            distance_from_other_region = min(dis1, dis2);
        }
        if (distance_from_other_region < min_distance)
            calculateDistanceInAnotherRegion(root->left, query, min_distance, result, depth + 1);
    }

    return;
}

// Deallocate KD_tree
void deleteList(Node* &root)
{
    if (root == NULL) return;
    deleteList(root->left);
    deleteList(root->right);
    delete root;
    root = NULL;
    return;
}