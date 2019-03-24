/**
 *@file
 *
 *@brief The header file that contains the city Structure
 */



#ifndef CITY_H
#include <string>
/*!
* @brief the define to prevent duplication of the header file
*/
#define CITY_H

/*!
* @brief Defines a node used to hold the name of the city, its longitude and
* latitude, its county, state, and if it has been visited
*/
struct city
{
    /*!
    * @brief Hold the name of the city
    */
    std::string name;

    /*!
    * @brief Holds the latitude of the city
    */
    double latitude;

    /*!
    * @brief Holds the longitude of the city
    */
    double longitude;

    /*!
    * @brief Hold the county of the city
    */
    std::string county;

    /*!
    * @brief Hold the state of the city
    */
    std::string state;

    /*!
    * @brief Holds the closest distance away from startName
    */
    std::vector<city> next;

    /*!
    * @brief Hold the visited state of the city
    */
    bool visited = false;

    bool operator==(city rhs) const
    {
	if(name == rhs.name && county == rhs.county && state == rhs.state)
	{
 	    return true;
	}

	return false;
    }
};

#endif
