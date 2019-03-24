/**
 *@file
 *
 *@brief The .cpp file for each of the functions found in functions.h.
 */
#include "functions.h"

using namespace std;



/***************************************************************************//**
 * @author Dennis Kovarik
 * @par Description:
 * This function takes a string and a vector by reference as arguments. The
 * string represents the filename of the file of file to be read. It will parse
 * the specified file and store the information for each city, including its
 * latitude and longitude, in a vector, called 'cities' passed by reference into
 * the function. If the function does this successfully for the entire file,
 * then the function will return true.
 *
 * @param[in] fileName - String representing the name and filepath of the file
			to parse
 * @param[out] cities - Vector of type 'city' that the information for each
 *			city will be stored in.
 *
 * @returns true if file successfully was able to parse file.
 *****************************************************************************/
bool readCities(string fileName, vector<city> &cities)
{
    ifstream fin;
    string line;
    string field;
    city newCity;
    size_t startPos = 0;
    size_t endPos = 0;

    //Open file and error checking
    fin.open(fileName.c_str());

    if(!fin.is_open())
    {
    	cout << "Could not open file reader. Quiting..." << endl;
    	exit(1);
    }

    //Read in the cities
    while(getline(fin, line))
    {
    	startPos = 0;
    	endPos = 0;

    	//Find latitude
    	endPos = line.find("|", endPos);
    	field = line.substr(startPos, endPos - startPos);
    	newCity.latitude = stod(field, nullptr)/1000.0;

    	//Find longitude
    	startPos = endPos + 1;
    	endPos = line.find("|", endPos + 1);
    	field = line.substr(startPos, endPos - startPos);
    	newCity.longitude = stod(field, nullptr)/1000.0;

    	//Find city name
    	startPos = endPos + 1;
    	endPos = line.find("|", endPos + 1);
    	newCity.name = line.substr(startPos, endPos - startPos);

    	//Find city county
    	startPos = endPos + 1;
    	endPos = line.find("|", endPos + 1);
    	newCity.county = line.substr(startPos, endPos - startPos);

    	//Find city state
    	startPos = endPos + 1;
    	endPos = line.find("|", endPos + 1);
    	newCity.state = line.substr(startPos);

    	cities.push_back(newCity);
    }

    return true;
}

/***************************************************************************//**
 * @author Dennis Kovarik, Spencer Drach
 * @par Description:
 * This function takes a string and a vector by reference as arguments. The
 * string represents the filename of the file of file to be read. It will parse
 * the specified file and store the information for each city, not including its
 * latitude and longitude, in a vector, called 'cities' passed by reference into
 * the function. If the function does this successfully for the entire file,
 * then the function will return true.
 *
 * @param[in] fileName - String representing the name and filepath of the file
			to parse
 * @param[out] cities - Vector of type 'city' that the information for each
 *			city will be stored in.
 *
 * @returns true if file successfully was able to parse file.
 *****************************************************************************/
bool readVisit(string fileName, vector<city> &cities)
{
    ifstream fin;
    string line;
    string field;
    city newCity;
    size_t startPos = 0;
    size_t endPos = 0;

    //Open file and error checking
    fin.open(fileName.c_str());

    if(!fin.is_open())
    {
    	cout << "Could not open file reader. Quiting..." << endl;
    	exit(1);
    }

    //Read in the cities
    while(getline(fin, line))
    {
    	startPos = 0;
    	endPos = 0;

    	//Find city name
    	endPos = line.find("|", endPos + 1);
    	newCity.name = line.substr(startPos, endPos - startPos);

    	//Find city county
    	startPos = endPos + 1;
    	endPos = line.find("|", endPos + 1);
    	newCity.county = line.substr(startPos, endPos - startPos);

    	//Find city state
    	startPos = endPos + 1;
    	endPos = line.find("|", endPos + 1);
    	newCity.state = line.substr(startPos);

    	cities.push_back(newCity);
    }

    if(cities.size()<3)
    {
        return false;
    }
    //Sort the cities based on name
    //sort(cities.begin(), cities.end(), citySort);

    return true;
}


/***************************************************************************//**
 * @author Spencer Drach
 * @par Description:
 * The latitude and longitude for two points are passed into this function.
 * Using this information, this function will use the Haversine formula to
 * calculate the distance between these two points in kilometers. The function
 * returns this distance as a double. The equation for the Haversine formula
 * used in this function was obtained from the following url address:
 * https://www.movable-type.co.uk/scripts/latlong.html.
 *
 * @param[in] lat1 - Double representing the latitude of the first point.
 * @param[in] long1 - Double representing the longitude of the first point.
 * @param[in] lat2 - Double representing the latitude of the second point.
 * @param[in] long2 - Double representing the longitude of the second point.
 *
 * @returns the distance between the two points in kilometers as a double.
 *****************************************************************************/
double calcDistance( double lat1, double lon1, double lat2, double lon2)
{
    double R = 6373; //radius of the earth in kilometers
    double sig1 = toRadians(lat1);
    double sig2 = toRadians(lat2);
    double deltaSig = toRadians(lat2-lat1);
    double deltaLam = toRadians(lon2-lon1);

    double a = sin(deltaSig/2) * sin(deltaSig/2) + cos(sig1) * cos(sig2) *
     sin(deltaLam/2) * sin(deltaLam/2);

    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return R*c;
}

/***************************************************************************//**
 * @author Spencer Drach
 * @par Description:
 * A double is passed into this function which represents a value in degrees.
 * This function will convert this value from degrees to radians and then return
 * this value as a double.
 *
 * @param[in] deg - Value represented in degrees to be converted into radians.
 *
 * @returns the value of the variable 'deg', passed into the function,
 * 	    converted into radians.
 *****************************************************************************/
double toRadians(double deg)
{
    return (deg*Pi/180);
}

/***************************************************************************//**
 * @author Spencer Drach
 * @par Description:
 * This function will calculate the total distance through a list of cities for
 * for the traveling saleperson problem. A vector of type 'city', which
 * represents the cities a person wishes to visit, and a vector of ints, which
 * represents the order in which to visit the cities. Each value inthe order
 * vector corresponds to an index in the cities vector. For example the starting
 * city is in the 0 index of the order vector, and the value held at that index
 * is the index of the starting city found in the cities vector. The next city
 * to visit is found at index 1 in the order vector, and the value at that index
 * is the index of the city in the cities vector. This function will repeatedly
 * call the calcDistance function to calculat the distance between 2 cities,
 * it will add that distance to a running total. This function will then return
 * that distance as a double.
 *
 * @param[in] cities - A vector representing the list of cities to visit.
 * @param[in] order - A vector representing the order in which to visit each of
 * 		      the cities in the cities vector..
 *
 * @returns the distance to travel to all the cities in the cities vector as a
 *          double.
 *****************************************************************************/
double calcTotalDistance (vector<city> cities, vector<int> order)
{
    double sum = 0;
    for(unsigned int i=0; i<(order.size()-1); i++)
    {
        sum += calcDistance(cities.at(order.at(i)).latitude, cities.at(order.at(i)).longitude,
		cities.at(order.at(i+1)).latitude, cities.at(order.at(i+1)).longitude);
    }
    return sum;
}

/***************************************************************************//**
 * @author Spencer Drach
 * @par Description:
 * Given a city, this function will search the vector cities, containing a list
 * of all cities, for that city and return the index in which that city can be
 * found at. If the city could not be found, then it will return -1.
 *
 * @param[in] name - A var of type 'city' representing the city to search for.
 * @param[in] cities - A vector containing a list of all cities.
 *
 * @returns the index in which the specified city can be found in the cities
 * 	    vector.
 *****************************************************************************/
int findCity(city name, vector<city> cities)
{
    for(unsigned int i = 0; i<cities.size(); i++)
    {
        if((cities.at(i).name == name.name)  &&
        (cities.at(i).county == name.county)  &&  (cities.at(i).state == name.state))
            return i;
    }

    return -1;
}

/***************************************************************************//**
 * @author Spencer Drach
 * @par Description:
 * This is the brute force algorithm used to solve the traveling salesperson
 * problem. It will calculate the distance for all possible Hamiltonian circuits
 * for a list of cities, and it will output to the screen the route with the
 * shortest distance.
 *
 * @param[in] cities - A vector containing a list of cities to visit.
 *
 * @returns void
 *****************************************************************************/
void bestPath(vector<city> cities)
{
    vector<int> order;
    vector<int> bestOrder;
    double bestDist = 99999999;


    for(unsigned int i=0; i<cities.size(); i++)
    {
        order.push_back(i);
    }
    order.push_back(0);
    bestDist = calcTotalDistance(cities, order);

    //find the shortest route
    while (next_permutation(order.begin()+1,order.end()-1))
    {
        double current = calcTotalDistance(cities, order);
        if(bestDist > current)
        {
            bestDist = current;
            bestOrder = order;
        }
    }
    cout << endl << "Tour computed by brute force algorithm:" << endl;
    for( int i = 0; i < int(bestOrder.size()); i++)
	{

	    cout << cities.at(bestOrder.at(i)).name << endl;
	}

    cout << "Shortest distance: " << bestDist << "km" << endl << endl;

}

/***************************************************************************//**
 * @author Dennis
 * @par Description:
 * This is function will compare to variables of type 'city'. It was intended to
 * be used by the STL sort function. This function will compare the names to two
 * cities passed into this function, and it will return a bool indicating the
 * the name for lhs is less than rhs.
 *
 * @param[in] lhs - var of type city
 * @param[in] rhs - var of type city
 *
 * @returns true if the name for lhs is less than that of rhs. Otherwise it
 *      	 will return false.
 *****************************************************************************/
bool citySort(city lhs, city rhs)
{
    return lhs.name < rhs.name;
}

/***************************************************************************//**
 * @author Spencer Drach
 * @par Description:
 * This function will search for each city found in the citiesToVisti vector,
 * and it will will in the latitude and longitude for each city in the
 * citiesToVisit from the cities vector. This function will return true if it
 * was successfully able to do this, otherwise it will return false.
 *
 * @param[in] cities - A vector containing a list of all cities.
 * @param[in,out] cities - A vector containing a list of cities to visit.
 *
 * @returns true if it was successfully able to find all fill in the latitudes
 * 		 and longitudes for each city in the citiesToVisit vector
 * 		 using the cities vector.
 *****************************************************************************/
bool fillCities(vector<city> &cities,vector<city> &citiesToVisit)
{
    for(int i=0; i<int(citiesToVisit.size()); i++)
    {
        city currentCity = citiesToVisit.at(i);
        int temp = findCity(currentCity, cities);
        if(temp < 0)
        {
            return false;
        }
        citiesToVisit.at(i).latitude = cities.at(temp).latitude;
        citiesToVisit.at(i).longitude = cities.at(temp).longitude;
    }

    return true;
}

/***************************************************************************//**
 * @author Spencer Drach, Dennis Kovarik
 * @par Description:
 * This is the MST algorithm used to solve the traveling salesperson problem.
 * It will build a minimum spanning tree for the cites found in the cities
 * vector. It will then call the function greedyOrder to find the preorder
 * traversal of the minimum spanning tree. It will then output to the screen
 * distance of the resulting route.
 *
 * @param[in] cities - A vector containing a list of cities to visit.
 *
 * @returns void
 *****************************************************************************/
void greedy(vector<city> cities)
{
    vector<city> visitedCities;
    cities.at(0).visited = true;
    visitedCities.push_back(cities.at(0));

    while(visitedCities.size() != cities.size())
    {
        double shortest = 9999999;
        int shortCity;
        int shortVisitCity;

        for(int i=0; i<int(visitedCities.size()); i++)
        {
            for(int j=0; j<int(cities.size()); j++)
            {
                if(!cities.at(j).visited)
                {
                    double latt1 = visitedCities.at(i).latitude;
                    double long1 = visitedCities.at(i).longitude;
                    double latt2 = cities.at(j).latitude;
                    double long2 = cities.at(j).longitude;
                    double current = calcDistance(latt1, long1, latt2, long2);
                    if(current < shortest)
                    {
                        //cout << i << "    " << j << endl;
                        shortCity = j;
                        shortest = current;
                        shortVisitCity = i;
                    }
                }
                else
                {
                    //do nothing
                }

                //cout << "J: " << j << endl;
            }
            //cout << "i: " << i << endl;
        }
        cities.at(shortCity).visited = true;
        visitedCities.at(shortVisitCity).next.push_back(cities.at(shortCity));
        visitedCities.push_back(cities.at(shortCity));
        //cout << "added " << cities.at(shortCity).name << " to " << visitedCities.at(shortVisitCity).name << endl;

    }
    vector<int> order;
    greedyOrder(visitedCities, order);
    order.push_back(0);

    double dist = calcTotalDistance(visitedCities, order );


    cout << "Tour computed by MST algorithm:" << endl;
    for( int i = 0; i < int(order.size()); i++)
	{

	    cout << visitedCities.at(order.at(i)).name << endl;
	}

    cout << "distance: " << dist << "km" << endl;

    return;
}

/***************************************************************************//**
 * @author Spencer Drach, Dennis Kovarik
 * @par Description:
 * This function will perform a preorder traversal on the minimum spanning tree
 * found in the cities vector passed into the function and store ther results
 * in the order vector. This function will return true if the operation was
 * completed successfully.
 *
 * @param[in] cities - A vector containing a list of cities to visit.
 * @param[out] order - A vector containing the order in which each of the
 * 		       cities in the cities vector should be visitied.
 *
 * @returns true if the function was successful
 *****************************************************************************/
bool greedyOrder(vector<city> cities, vector<int> &order)
{
    stack<int> stackOrder;

    stackOrder.push(0);
    int current;

    while(!stackOrder.empty())
    {
        current = stackOrder.top();
        stackOrder.pop();

        order.push_back(current);

        for(int i = cities.at(current).next.size()-1; i >= 0; i-- )
        {
            int temp = findCity(cities.at(current).next.at(i), cities);
            if(temp < 0)
            {
                return false;
            }
            stackOrder.push(temp);
        }
    }

    return true;
}

/***************************************************************************//**
 * @author Spencer Drach
 * @par Description:
 * This function will parse a string, with '|' separated fields, and store the
 * name, county, and state for that city in the variable 'headCity' which is
 * passed into the function by reference.
 *
 * @param[in,out] headCity - Variable of type city
 * @param[out] order - A string with '|' separated fields containing
 * 		       information about a particular city.
 *
 * @returns void
 *****************************************************************************/
void clCity(city &headCity, string clName)
{
    int startPos = 0;
    int endPos = 0;

    //Find city name
    endPos = clName.find("|", endPos + 1);
    headCity.name = clName.substr(startPos, endPos - startPos);

    //Find city county
    startPos = endPos + 1;
    endPos = clName.find("|", endPos + 1);
    headCity.county = clName.substr(startPos, endPos - startPos);

    //Find city state
    startPos = endPos + 1;
    endPos = clName.find("|", endPos + 1);
    headCity.state = clName.substr(startPos);

    return;
}





void genetic(vector<city> cities)
{
    int generations = 100;
    int populationSize = 500;

    vector<int> order;
    vector<int> bestOrder;
    double currentBest = 99999999;
    double bestDist = 99999999;
    vector<double> fitness;
    int bestLocation = 0;


    for(unsigned int i=0; i<cities.size(); i++)
    {
        order.push_back(i);
    }
    order.push_back(0);
    bestOrder = order;
    vector<vector<int>> orderPop;

    for (int i = 1; i<populationSize; i++)
    {
        orderPop.push_back(order);
        mutate(orderPop.at(i));
        fitness.push_back(0);
    }

    for(int j = 0; j<generations; j++)
    {
        calcFitness( currentBest, fitness, cities, bestLocation);
        if(currentBest < bestDist)
        {
            bestOrder = orderPop.at(bestLocation);
            bestDist = currentBest;
        }
        //nextGeneration(orderPop)

    }

    return;
}

void mutate(vector<int> &order)
{
    srand(time(NULL));
    int mutationRate = 5;//% chance of a mutation
    int temp;

    for(int i=1; i<int(order.size())-2; i++)
    {
        temp = rand() % 100;
        if(temp > mutationRate)
        {
            swap (order.at(i),order.at(i+1));
        }
    }

    return;
}

void calcFitness( double &bestDist, vector<double> &fitness, vector<city> cities, int &bestLocation)
{
    double totalDist = 0;
    double temp;
    for(int i = 0; i<int(orderPop.size()); i++)
    {
        temp = calcTotalDistance(cities, orderPop.at(i));
        fitness.at(i) = -temp;
        totalDist += temp;
        fitness.at(i) = 1/(pow(temp, 8)+1);
        if(temp<bestDist)
        {
            bestDist = temp;
            bestLocation = i;
        }
    }

    for(int j = 0; j<int(fitness.size()); j++)
    {
        fitness.at(j) = fitness.at(j) / totalDist;
    }

    return;
}
