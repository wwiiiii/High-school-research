#ifndef __Road_Cpp
#define __Road_Cpp

#include "Road.h"
#include <cmath>
#include <cstdio>


std::pair<double, double > cRoad::fRoadForce(cRobot& target){

	double force, forcex, forcey, distance;
	std::pair<double, double> ret = std::make_pair(0.0,0.0);
	coord targetCoord = target.fNowCoord();
	for (int i = 0; i < Lines.size(); ++i)
	{
		distance = abs(Lines[i].a * targetCoord.x + Lines[i].b * targetCoord.y + Lines[i].c) / std::sqrt(Lines[i].a * Lines[i].a + Lines[i].b * Lines[i].b);
		force = ProportionConstant / distance; //�о
		if (distance > Threshold) force = 0;
		/*
			decompose Force vector into X component, Y component
			forcex = Gx(force);
			forcey = Gy(force);
		*/
		ret.first += forcex, ret.second += forcey;
	}
	return ret;
}

#endif