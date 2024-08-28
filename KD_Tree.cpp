#include "KD_Tree.h"
#include <algorithm>
#include <cmath>

using namespace std;

int dimension = 2;

Node* rotateLeft(Node* &root)
{
    if (root == NULL) return NULL;
    Node* right_child = root->right;
    Node* left_subchild = right_child->left;
    right_child->left = root;
    root->right = left_subchild;
    return right_child;
}

Node* rotateRight(Node* &root)
{
    if (root == NULL) return NULL;
    Node* left_child = root->left;
    Node* right_subchild = left_child->right;
    left_child->right = root;
    root->left = right_subchild;
    return left_child;
}

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

void setBalance(Node* &root, Location key, int depth) 
{
    if (root == NULL) return;
    int balance = getBalanceFactor(root);

    if (balance > 1)
        if (key.point[depth % dimension] < root->left->key.point[depth % dimension])
            root = rotateRight(root);
        else if (key.point[depth % dimension] >= root->left->key.point[depth % dimension])
        {
            root->left = rotateLeft(root->left);
            root = rotateRight(root);
        }
    else if (balance < -1)
        if (key.point[depth % dimension] >= root->right->key.point[depth % dimension])
            root = rotateLeft(root);
        else if (key.point[depth % dimension] < root->right->key.point[depth % dimension])
        {
            root->right = rotateRight(root->right);
            root = rotateLeft(root);
        }
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

    if (data.point[depth % dimension] < root->key.point[depth % dimension]) 
        insertOneCity(root->left, data, depth + 1);
    else insertOneCity(root->right, data, depth + 1);
    
    // setBalance(root, data, depth);
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

    int axis = depth % dimension;

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
    double dlat = abs(src.point[0] - dst.point[0]) * M_PI / 180.0;
    double dlon = abs(src.point[1] - dst.point[1]) * M_PI / 180.0;

    src.point[0] = src.point[0] * M_PI / 180.0;
    dst.point[0] = dst.point[0] * M_PI / 180.0;

    double a = pow(sin(dlat / 2), 2) + pow(sin(dlon / 2), 2) * cos(src.point[0]) * cos(dst.point[0]);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
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

    if (query.point[depth % dimension] < root->key.point[depth % dimension])
        findNearestNeighbor(root->left, query, min_distance, result, depth + 1);
    else findNearestNeighbor(root->right, query, min_distance, result, depth + 1);
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