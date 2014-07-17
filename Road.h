#ifndef __Road_H__
#define __Road_H__
#include <utility>
#include <vector>
#include "RobotClass.h"
typedef struct{ int x, y; }coord;
typedef struct{ double a, b, c; coord from, to; }line; ///always a>=0, segment [from, to]

class cRoad{
public:
	std::vector<line> Lines;
	std::vector<coord> CheckPoints;
	std::pair<double, double> RoadForce(cRobot& target);
};

#endif