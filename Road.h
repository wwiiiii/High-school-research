#ifndef __Road_H__
#define __Road_H__
#include <utility>
#include <vector>
#include "RobotClass.h"
#include "CONST.h"
typedef struct{ double a, b, c; coord from, to; }line; ///always a>=0, segment [from, to]

class cRoad{
public:
	int PassiveID;///PassiveID는 수동조작중인 차의 id
	double scalex, scaley;
	std::vector<line> Lines;			
	std::vector<coord> CheckPoints;
	std::vector<std::vector<int> > Directions;///Directions[i]'s component j => there is route [i] -> [j]
	std::vector<coord> Obstacles;		///coords of obstacles
	std::pair<double, double> fRoadForce(cRobot& target);
};
///저장하고 있는 가상의 맵크기는 8000*6400(이게 각 coord의 값)
///실제 디스플레이는 1920 * 1080(이게 실제 모니터에 나오는 좌표)
///축척 적용해서 좌표지정해 출력(coord * 축척)
#endif