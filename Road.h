#ifndef __Road_H__
#define __Road_H__
#include <utility>
#include <vector>
#include "RobotClass.h"
typedef struct{ double a, b, c; }line;
typedef struct{ int x, y; }coord;
class cRoad{
public:
	std::vector<line> Lines;
	std::vector<coord> CheckPoints;
	std::pair<double, double> RoadForce(cRobot& target);
};

#endif