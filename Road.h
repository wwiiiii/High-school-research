#ifndef __Road_H__
#define __Road_H__

typedef struct{ double a, b, c; }line;

class cRoad{
public:
	std::vector<line> Lines;
	std::pair<double, double> RoadForce(cRobot& target);
};

#endif