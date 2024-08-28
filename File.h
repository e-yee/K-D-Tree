#pragma once

#include "KD_Tree.h"

Location getLocation(string data);

//1. Prepare the dataset
vector<Location> readFile(string filename);