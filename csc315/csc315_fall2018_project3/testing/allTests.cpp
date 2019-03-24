#include "catch/catch.h"
#include "../functions.h"
#include "../city.h"

using namespace std;




/******************************************************************************
*  Testing the readCities function in functions.cpp file
*    (This is the test case purpse)
*
*  Author(s): Dennis Kovarik
*  Parameters:  (These are parameters the test uses in all sections)
*    fileName - String representing the name of the file
*    cities   - Vector used to contain all cities
*    
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case tests the readCities() function. It will make sure the 
*  function can open the input file and read its contents into the vector
*  named cities.
*                                                   
********************************************************************************/
TEST_CASE( "Tests if the 'getFileInput()' function correctly initiates ASCIIarray" )
{
    string fileName = "testFile2.txt";
    vector<city> allCities;
    ifstream fin;

    SECTION("Testing that the readCities function")
    {
	REQUIRE(readCities(fileName, allCities) == true);
	REQUIRE(allCities.size() >= 9);

	CHECK(abs(allCities[0].latitude - 33100.9540 / 1000) < 0.0001);
	CHECK(abs(allCities[0].longitude - 85529.6753 / 1000) < 0.0001);
	CHECK(allCities[0].name == "Abanda");
	CHECK(allCities[0].county == "Chambers");
	CHECK(allCities[0].state == "AL");

	CHECK(abs(allCities[8].latitude - 32121.5366 / 1000) < 0.0001);
	CHECK(abs(allCities[8].longitude - 87906.1227 / 1000) < 0.0001);
	CHECK(allCities[8].name == "Aimwell");
	CHECK(allCities[8].county == "Marengo");
	CHECK(allCities[8].state == "AL");
    }
}


/******************************************************************************
*  Testing the calcDistance function in functions.cpp file
*    (This is the test case purpse)
*
*  Author(s): Dennis Kovarik
*  Parameters:  (These are parameters the test uses in all sections)
*    
*  Return Value:
*    Returns the number of failed section tests.
*
*  This test case tests the tha calcDistance function is returning the correct
*  distance between two cities. 
*                                                   
********************************************************************************/
TEST_CASE( "Tests the calcDistance function" )
{
    double lat1 = 33.6131588;
    double long1 = 86.1183061;
    double lat2 = 33.1009540;
    double long2 = 85.5296753;
    SECTION("Cal distance between 2 cites just given latitude and longitude.")
    {
	CHECK(abs(calcDistance(lat1, long1, lat2, long2) - 78.9468) < 0.1);
    }
}
