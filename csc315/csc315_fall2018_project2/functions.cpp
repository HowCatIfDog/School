/*************************************************************************//*
 * @file Contains helper functions not involving the Bacon number
 *
****************************************************************************/

#include "functions.h"


using namespace std;

/***************************************************************************//**
 * @author Ezra Grothe
 *
 *
 * @brief Pass in a file stream to be split up into its individual Lines
 * then add each line in a vector of strings.
 *
 * @param[in] fin - ifstream of input file
 *
 * @returns fileLines - Vector of strings that make up each line of the input
 * file
 ******************************************************************************/
vector<string>* readFile(ifstream& fin)
{
    //array of movies+actors
    vector<string>* fileLines = new vector<string>();
    string str;
    while (getline(fin, str))
    {
        fileLines->push_back(str);
    }
    return fileLines;
}

/***************************************************************************//**
 * @author Ezra Grothe
 *
 *
 * @brief This function splits up the lines stored in the vector lines into
 * actors and the movies they're connected to. Then it builds a connected graph
 * of all actors and the movies they are connected to.
 *
 * @param[in] lines - input file split up into stings of each line
 *
 * @returns umap - the unordered map of all actors and movies
 ******************************************************************************/
umap* generateGraph(vector<string>* lines)
{
    umap* nodes = new umap();

    for (int i = 0; i < int(lines->size()); i++)
    {
        vector<std::string> names;
        istringstream       ss(lines->at(i));
        string              name;

        while(getline(ss, name, '/'))
           names.push_back(name);
        // Only proceed if there is at least one actor in the movie
        if (names.size() > 1)
        {
            node* movie = new node();
            movie->name = names[0];
            movie->isActor = false;

            movie->connections = new vector<node*>();

            for (int k = 1; k < int(names.size()); k++)
            {
                if (nodes->find(names[k]) == nodes->end())
                {
                    node* actor = new node();
                    actor->name = names[k];
                    actor->isActor = true;
                    actor->connections = new vector<node*>();
                    (*nodes)[names[k]] = actor;
                }
                (*nodes)[names[k]]->connections->push_back(movie);
                movie->connections->push_back((*nodes)[names[k]]);
            }
            (*nodes)[names[0]] = movie;
        }
    }
    return nodes;
}

/***************************************************************************//**
 * @author Spencer Drach
 *
 *
 * @brief This function builds a histogram of the people connected to string
 * name. It will walk through the unordered map and record how far away each
 * person is and makes a histogram of the data. It displays this Information to
 * the command line
 *
 * @param[in] graph - unordered map of all the actors and movies
 * @param[in] name  - name of the person the histogram starts with
 *
 * @returns nothing
 ******************************************************************************/
void histogram(string* name, umap* graph)
{

    queue<node*>  q;
    map<int, int> hist;
    node*         current;
    int           infinityCount = 0;

    graph->at(*name)->level = 0;
    q.push(graph->at(*name));

    hist[0] = 1;

    //for if the actor is not connected at all
    for (umap::iterator it = graph->begin(); it != graph->end(); it++)
        if (it->second->isActor)
            infinityCount++;

    //walk through the entire graph
    while(q.empty() == false)
    {
        current = q.front();
        q.pop();

        //add all connections to the q that haven't been visited
        for(int i = 0; i < int(current->connections->size()); i++)
        {
            if(current->connections->at(i)->isVisited == false)
            {
                //only iterate if the nade is an actor node
                current->connections->at(i)->level = current->level;
                if (current->connections->at(i)->isActor)
                {
                    infinityCount--;
                    current->connections->at(i)->level++;
                    if (hist.count(current->connections->at(i)->level) == 0)
                        hist[current->connections->at(i)->level] = 0;
                    hist[current->connections->at(i)->level]++;
                }
                current->connections->at(i)->isVisited = true;
                q.push(current->connections->at(i));
            }
        }
        current->isVisited = true;

        //make sure we don't count the same node twice and add it to the histogram
    }

    hist[-1] = infinityCount;

    //compute avg path length
    double path = 0;
    int pathCount = 0;
    
    cout << "Histogram of actor " << *name << endl;
    cout << "#\tFrequency" << endl;
    cout << "-------------------------" << endl;
    for(map<int, int>::iterator it = hist.begin(); it != hist.end(); it++ )
    {
        if (it->first != -1)
        {
            cout << it->first << "\t" << it->second << endl;
            path += it->first * it->second;
            pathCount += it->second;
        }
    }
    path /= pathCount;
    cout << "Inf\t" << hist[-1] << endl;
    cout << endl << "average path length: " << path << endl;

    return;
}

/***************************************************************************//**
 * @author Ezra Grothe
 *
 *
 * @brief This function will find any individuals with the longest shortest path
 * to the starting name.
 *
 * @param[in] graph - unordered map of all the actors and movies
 * @param[in] name  - name of the person the histogram starts with
 *
 * @returns nothing
 ******************************************************************************/
void longestPath(string* name, umap* graph)
{

    queue<node*> q;
    node*        current;
    int          longest = 0;

    graph->at(*name)->level = 0;
    q.push(graph->at(*name));

    vector<node*> longestEndNodes;

    while(q.empty() == false)
    {
        current = q.front();
        q.pop();

        //update array of the longest shortest path
        if(current->level == longest)
            longestEndNodes.push_back(current);
        else if (current->level > longest)
        {
            longestEndNodes.clear();
            longestEndNodes.push_back(current);
            longest = current->level;
        }

        //add all connections to the q that haven't been visited
        for(int i = 0; i < int(current->connections->size()); i++)
        {
            if(current->connections->at(i)->isVisited == false)
            {
                current->connections->at(i)->level = current->level;

                //increase the level if the node is an actor node
                if (current->connections->at(i)->isActor)
                    current->connections->at(i)->level++;

                //add the node to the queue
                q.push(current->connections->at(i));
            }
            current->connections->at(i)->isVisited = true;
        }

        //make sure we don't count the same node twice
        current->isVisited = true;
    }

    //display Information
    cout << "Longest shortest path -- path length = " << longest << endl;
    cout << "---------------------------------------------------" << endl;
    for(int p; p < int(longestEndNodes.size()); p++)
    {
        cout << longestEndNodes.at(p)->name << endl;
    }

    return;
}

/***************************************************************************//**
 * @author Spencer Drach
 *
 *
 * @brief This function finds the distance between starting name (name) and
 * the given name (name2), then it outputs the sortest path between the two.
 *
 * @param[in] graph - unordered map of all the actors and movies
 * @param[in] name  - name of the person the histogram starts with
 * @param[in] name2 - name of the person the function finds the distance to
 *
 * @returns nothing
 ******************************************************************************/
void distance(string* name, string* name2, umap* graph)
{

    queue<node*> q;
    node*        current;

    q.push(graph->at(*name));

    while(q.empty() == false)
    {
        current = q.front();
        q.pop();

        //if it finds the person we're looking for
        if(current->name == *name2)
        {
            //output all the names going back to the starting name
            while(current->name != *name)
            {
                cout << current->name << endl;
                current = current->previous;
            }
            cout << *name << endl;
            return;
        }

        //add all connections to the q that haven't been visited
        for(int i = 0; i < int(current->connections->size()); i++)
        {

            if(current->connections->at(i)->isVisited == false)
            {
                current->connections->at(i)->previous = current;
                q.push(current->connections->at(i));
            }
            current->connections->at(i)->isVisited = true;
        }

        //make sure we don't count the same node twice
        current->isVisited = true;

    }

    //if there is no path found
    cout << "No path found between " << name << " and " << name2 << endl;
    return;
}
