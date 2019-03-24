/**
 *@file
 *
 *@brief The header file that contains the functions for functions.cpp.
 */

#ifndef FUNCTIONS_H
/*!
* @brief the define to prevent duplication of the header file
*/
#define FUNCTIONS_H

//included functions
#include <algorithm>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <queue>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <stdio.h>
#include <cstring>
#include <cmath>
#include <unordered_map>
#include "node.h"

typedef unordered_map<string, node*> umap;

using namespace std;


/******************************************************************************
*                            Function Prototypes
******************************************************************************/
vector<string>* readFile(ifstream& fin);
umap* generateGraph(vector<string>* lines);
void histogram(string* name, umap* graph);
void longestPath(string* name, umap* graph);
void distance(string* name, string* name2, umap* graph);

#endif
