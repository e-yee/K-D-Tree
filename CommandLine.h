#pragma once

#include <iostream>
#include <string>

#include "KD_Tree.h"
#include "File.h"

//3. User Interface
void cmdloadCity(Node*& root);
void cmdInsertCity(Node*& root);
void cmdInsertCitiesFromFile(Node*& root);
void cmdConductNearestNeighbor(Node*& root);
void cmdQueryRangeSearch(Node*& root);