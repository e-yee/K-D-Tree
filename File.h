#pragma once

#include "KD_Tree.h"

Location getLocation(string data);

//1. Prepare the dataset
vector<Location> readFile(string filename);

void serialize(Node* root, ofstream &ofs);
void deserialize(Node*& root, ifstream &ifs);