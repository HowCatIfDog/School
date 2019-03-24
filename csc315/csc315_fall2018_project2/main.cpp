/***************************************************************************//**
 * @file main.cpp
 *
 * @mainpage CSC 315 - Fall 2018
 *
 * @brief Main function for project 2 - Bacon number
 *
 * @section course_section Course Information
 *
 * @authors Ezra Grothe, Spencer Drach
 *
 * @date Nov. 14, 2018
 *
 * @par Professor: Dr. Qiao
 *
 * @par Course: CSC 315 - Section 1 - Fall 2018
 *
 * @section program_section Program Description
 *
 * @par Description
 *   This Program is for implementing the Bacon Number Game where the game is
 * to find the shortest path between any actor and Kevin Bacon. We have changed
 * the parameters of the game to allow any actor to be the center of attention.
 * This program had 3 main functions: 1st to find the shortest distance between
 * two actors. 2nd, to build a histogram of the connections to a given actor.
 * And finally to find notably far away people from the given starting point.
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
 ./main inFile startName endName/-h/-l
@endverbatim
 *
 * @section todo_bugs_modification_section To Do, Bugs, and Modifications
 *
 * No known bugs or todos.
 *
 * @par Revision History
 * Go <a href="https://gitlab.mcs.sdsmt.edu/7244094/csc315_fall2018_project2">here</a>
 * to see git commit history.<br>A brief timeline is as follows:<br>
 * 11/04/18: Initial work has begun. Structure of the program is laid out and
 * the necessary function definitions have been written.<br>
 * 11/11/18: Finished project, cleaned up bugs, commented code
 *
 *****************************************************************************/

#include "functions.h"

using namespace std;

/***************************************************************************//**
 * @author Ezra Grothe, Spencer Drach
 * @par Description:
 * Contains the entry point to the program. Takes the command line arguments and
 * either encodes or decodes the input file. Handles bad input gracefully.
 *
 * @param[in] argc - The command line argument count
 * @param[in] argv - A pointer to the command line arguments array
 *
 * @returns 0 if program ran successfully, a non-zero value if it failed
 *****************************************************************************/
int main(int argc, char *argv[])
{
    // Handle usage and file errors
    if (argc != 4)
    {
        cout << "Usage: " << argv[0] << " <infile> <startName> <endName/modifier>\n";
        return -1;
    }

    //put command line arguments into their own string
    char * inFile = argv[1];
    char * startName = argv[2];
    char * third = argv[3];

    //open file and check for errors
    ifstream fin (inFile);
    if (!fin)
    {
        cout << "Unable to open input file, \"" << inFile << "\"\n";
        return -2;
    }

    //builds a graph of the actors and movies
    vector<string>* lines = readFile(fin);
    umap* graph = generateGraph(lines);

    //if the user wants a histogram of the graph it will use the histogram function
    if(strcmp(third,"-h") == 0)
    {
        histogram(new string(startName), graph);
        return 0;
    }

    //this will find any nodes of the longest distance away
    else if(strcmp(third,"-l") == 0)
    {
        longestPath(new string(startName), graph);
        return 0;
    }

    //this will find the distance between startName and given name in third
    else
    {
        distance(new string(startName), new string(third), graph);
        return 0;
    }

    //close file and exit
    fin.close();
    return 0;

}
