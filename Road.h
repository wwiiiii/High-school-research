#ifndef __Road_H__
#define __Road_H__
#include <utility>
#include <vector>
#include "RobotClass.h"
#include "CONST.h"
typedef struct{ double a, b, c; coord from, to; }line; ///always a>=0, segment [from, to]

class cRoad{
public:
	int PassiveID;///PassiveID�� ������������ ���� id
	double scalex, scaley;
	std::vector<line> Lines;			
	std::vector<coord> CheckPoints;
	std::vector<std::vector<int> > Directions;///Directions[i]'s component j => there is route [i] -> [j]
	std::vector<coord> Obstacles;		///coords of obstacles
	std::pair<double, double> fRoadForce(cRobot& target);
};
///�����ϰ� �ִ� ������ ��ũ��� 8000*6400(�̰� �� coord�� ��)
///���� ���÷��̴� 1920 * 1080(�̰� ���� ����Ϳ� ������ ��ǥ)
///��ô �����ؼ� ��ǥ������ ���(coord * ��ô)
#endif