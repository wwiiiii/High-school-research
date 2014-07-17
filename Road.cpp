#include "Road.h"
#include <cmath>
double abs(double a){ if (a < 0)return -a; return a; }

std::pair<double, double > cRoad::RoadForce(cRobot& target){

	std::pair<double, double> ret = std::make_pair(0.0,0.0);
	std::pair<int, int> targetCoord = target.fNowCoord()
	for (int i = 0; i < Lines.size(); ++i)
	{
		double distance = abs(Lines[i].a * targetCoord.x + Lines[i].b * targetCoord.y + Lines[i].c) / std::sqrt(Lines[i].a * Lines[i].a + Lines[i].b * Lines[i].b);
		

	
	}
}