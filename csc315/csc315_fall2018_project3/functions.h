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
#include <bits/stdc++.h>
#include "city.h"


using namespace std;

// Constant for pi
const double Pi = atan(1) * 4;


/******************************************************************************
*                            Function Prototypes
******************************************************************************/
bool readCities(string fileName, vector<city> &cities);
bool readVisit(string fileName, vector<city> &cities);
double calcDistance( double lat1, double lon1, double lat2, double lon2);
double toRadians(double deg);
double calcTotalDistance (vector<city> cities, vector<int> order);
int findCity(city name, vector<city> cities);
void bestPath(vector<city> cities);
bool citySort(city lhs, city rhs);
bool fillCities(vector<city> &cities,vector<city> &citiesToVisit);
void greedy(vector<city> cities);
bool greedyOrder(vector<city> cities, vector<int> &order);
void clCity(city &name, string clName);
void genetic(vector<city> cities);
void mutate(vector<int> &order);
void calcFitness( double &bestDist, vector<double> &fitness, vector<city> cities, int &bestLocation);
#endif
