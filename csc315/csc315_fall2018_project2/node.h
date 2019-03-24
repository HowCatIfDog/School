/**
 *@file
 *
 *@brief The header file that contains the node Structure
 */



#ifndef NODE_H
/*!
* @brief the define to prevent duplication of the header file
*/
#define NODE_H

using namespace std;
/*!
* @brief Defines a node used to hold the name of an actor or movie and all
* connections to it. As well as isActor, isVisited, level, and previous.
*/
struct node
{
    /*!
    * @brief Hold the name of the actor/movie
    */
    string name;

    /*!
    * @brief Holds a T/F value if the node is for an actor or not
    */
    bool isActor;

    /*!
    * @brief Holds the array of pointers to connections for this node
    */
    vector<node*>* connections;

    /*!
    * @brief Holds a T/F value if the node has been visited
    */
    bool isVisited;

    /*!
    * @brief Holds the closest distance away from startName
    */
    int level;

    /*!
    * @brief Holds the pointer to the closest node to startName
    */
    node* previous;
};

#endif
