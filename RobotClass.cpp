#ifndef __Robot_Class_Cpp
#define __Robot_Class_Cpp
#include <utility>
#include "RobotClass.h"
#define DATA int///기타 추가 자료형
#define dT 0.001

//위치에 따라 작용하는 힘 계산 함수
//x, y가 힘을 받는 물체의 좌표
//otherx, othery가 만유인력을 작용시키는 물체의 좌표

//생성자, 위치는 랜덤, id와 질량은 주어지고, data도 주어지고, 받는 힘은 0
void cRobot::init(int ID, double mas, DATA dat, int from, int to)
{
	id = ID;	mass = mas;	data = dat;
	speed_x = speed_y = force_x = force_y = NowCoord.x = NowCoord.y = 0; isAutoDriving = true;
	fFindRoute(from, to);
}

///현재 위치 반환
coord cRobot::fNowCoord(void){
	return NowCoord;
}

	///힘 갱신 - 다른 객체랑 상호작용
void cRobot::fRenewForce(double dX, double dY){
	force_x += dX;
	force_y += dY;
	///상대 위치를 받아서 힘 갱신하는거 추가해야됨
}
	///속도 갱신
void cRobot::fRenewVelocity(void){
	speed_x += (force_x / mass) * dT;
	speed_y += (force_y / mass) * dT;
}
	///위치 갱신
void cRobot::fRenewCoord(void){
	NowCoord.x += speed_x * dT;
	NowCoord.y += speed_y * dT;
}

void cRobot::fConstForce(std::vector<coord>&CheckPoints){
	force_x += BasicForceX;
	force_y += BasicForceY;
	coord NextCP = CheckPoints[BasicRoute[RouteNowAt]];
	if (NextCP.x - 100 <= NowCoord.x && NowCoord.x <= NextCP.x + 100 && NextCP.y - 100 <= NowCoord.y && NowCoord.y <= NextCP.y + 100)
	{
		BasicForceX = 0;
		BasicForceY = 0;
		RouteNowAt++;
	}
}

void cRobot::fFindRoute(int from, int to)
{
	return;
}

#endif