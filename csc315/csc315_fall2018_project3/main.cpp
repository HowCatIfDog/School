/***************************************************************************//**
 * @file main.cpp
 *
 * @mainpage CSC 315 - Fall 2018
 *
 * @brief Main function for project 3 - traveling salesperson
 *
 * @section course_section Course Information
 *
 * @authors Dennis Kovarik, Spencer Drach
 *
 * @date Dec. 5, 2018
 *
 * @par Professor: Dr. Qiao
 *
 * @par Course: CSC 315 - Section 1 - Fall 2018
 *
 * @section program_section Program Description
 *
 * @par Description
 *   This Program is for implementing the Traveling salesperson problem using
 * 2 meathods: brute force and minimum spanning tree(MST). The pregram expects
 * allCities.txt to have at least all cities that you want to visit with all
 * information included. citiesToVisit.txt only needs the name,county,state.
 * this program will compute the shortest possible loop with the brute force
 * meathod then a greedyer approach  with the MST meathod. It will output the
 * paths and distances to the command line.
 *
 * @section compile_section Compile Section
 *
 * @par Build
   @verbatim
% make
   @endverbatim
 * @par Run
 * @verbatim
% ./main
   @endverbatim
 * @par Usage
 *
@verbatim
 ./main allCities.txt citiesToVisit.txt
@endverbatim
 *
 * @section todo_bugs_modification_section To Do, Bugs, and Modifications
 *
 * No known bugs or todos.
 *
 * @par Revision History
 * Go <a href="https://gitlab.mcs.sdsmt.edu/1985937/csc315_fall2018_project3">here</a>
 * to see git commit history.<br>A brief timeline is as follows:<br>
 * 12/01/18: Initial work has begun. Structure of the program is laid out and
 * the necessary function definitions have been written.<br>
 * 12/03/18: continued to create functins, cleaned up bugs, commented code
 *
 *****************************************************************************/

#include "functions.h"

using namespace std;

void usageStatement(string fileName)
{
	cout << "Incorrect number of command line arguments." << endl;
	cout << "Other than the executable file, this program requires 2 input files.\n";
	cout << "The first is a list of all cities in the world, and the second is a ";
	cout << "file for all the cities that the use wishes to visit.\n" << endl;
    cout << "Usage: " << fileName << " <all cities file> <cities to visit file> \n";
}

/***************************************************************************//**
 * @author Dennis Kovarik, Spencer Drach
 * @par Description:
 * Contains the entry point to the program. Takes the command line arguments and
 * asks user for the starting city, then fills in the missing Information
 * from the allCities.txt and then it computes a solution usung brute force
 * and MST algorithms
 *
 * @param[in] argc - The command line argument count
 * @param[in] argv - A pointer to the command line arguments array
 *
 * @returns 0 if program ran successfully, a non-zero value if it failed
 *****************************************************************************/
int main(int argc, char *argv[])
{
    // Handle usage and file errors
    if (argc != 3)
    {
	     usageStatement(argv[0]);
         return -1;
    }

    string fileName = argv[1];
    string fileName2 = argv[2];
    vector<city> cities;
    vector<city> citiesToVisit;


    //Read and store cities in all cities file in allCities vector
    readCities(fileName, cities);

    //Read the cities to visit input file and store in citiesToVisit vector
    readVisit(fileName2, citiesToVisit);
    if(citiesToVisit.size() <= 2)
    {
		cout << "not enough cities to visit" << endl;
	    return -2;
    }
	cout << citiesToVisit.size();
    bool temp = fillCities(cities, citiesToVisit);
    if(!temp)
    {
        cout << "could not find all cities" << endl;
        return -3;
    }

    city startCity;
    string cityName;

    cout << "enter starting city name | city county | state abbreviation" << endl;
    getline(cin,cityName);

	clCity(startCity, cityName);

    int location = findCity(startCity, citiesToVisit);
    if(location < 0)
    {
        cout << "could not find the starting city" << endl;
        return -4;
    }
    swap(citiesToVisit.at(0), citiesToVisit.at(location));


    bestPath(citiesToVisit);
	greedy(citiesToVisit);

    return 0;
}
