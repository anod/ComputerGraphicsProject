#ifndef GENERAL_H_
#define GENERAL_H_


#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>
#include <vector>
#include <stack>
#include <unordered_map>
#include <iterator>

#include "glut.h"
#include "Pixel.h"

#define PI 3.1415926
static const int GRID_SIZE = 200;
static const int WIDTH = 600;
static const int HEIGHT = WIDTH;
static const int WINDOW_OFFSET = (WIDTH/2.0f);

static const int GRID_OFFSET = (GRID_SIZE/2.0f);
static const int GRID_KOEF = WIDTH/float(GRID_SIZE);

/**
 * Coordinates in 3d
 */ 
typedef struct {
	double x,y,z;
} THREE;

/**
 * City information
 */
typedef struct
{
	int id;
	int x,y;
	int type;
	int connectedTo;
} CITY;

/**
 * List of cities
 */
typedef std::vector<CITY> CityList;
/**
 * List of cities connected to specific city id
 */
typedef std::unordered_map<int, CityList> CityMap;
/**
 * List of waypoints
 */
typedef std::vector<THREE> WayPoints;
/**
 * Map of waypoints for a city
 */
typedef std::unordered_map<int, WayPoints> CityWayPoints;
/**
 * Map of waypoints between cities
 */
typedef std::unordered_map<int, CityWayPoints> CitiesWayPoints;

#endif