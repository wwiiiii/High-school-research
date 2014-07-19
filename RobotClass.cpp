#ifndef __Robot_Class_Cpp
#define __Robot_Class_Cpp
#include <utility>
#include "RobotClass.h"
#define DATA int///��Ÿ �߰� �ڷ���
#define dT 0.001

//��ġ�� ���� �ۿ��ϴ� �� ��� �Լ�
//x, y�� ���� �޴� ��ü�� ��ǥ
//otherx, othery�� �����η��� �ۿ��Ű�� ��ü�� ��ǥ

//������, ��ġ�� ����, id�� ������ �־�����, data�� �־�����, �޴� ���� 0
void cRobot::init(int ID, double mas, DATA dat, int from, int to)
{
	id = ID;	mass = mas;	data = dat;
	speed_x = speed_y = force_x = force_y = NowCoord.x = NowCoord.y = 0; isAutoDriving = true;
	fFindRoute(from, to);
}

///���� ��ġ ��ȯ
coord cRobot::fNowCoord(void){
	return NowCoord;
}

	///�� ���� - �ٸ� ��ü�� ��ȣ�ۿ�
void cRobot::fRenewForce(double dX, double dY){
	force_x += dX;
	force_y += dY;
	///��� ��ġ�� �޾Ƽ� �� �����ϴ°� �߰��ؾߵ�
}
	///�ӵ� ����
void cRobot::fRenewVelocity(void){
	speed_x += (force_x / mass) * dT;
	speed_y += (force_y / mass) * dT;
}
	///��ġ ����
void cRobot::fRenewCoord(void){
	NowCoord.x += speed_x * dT;
	NowCoord.y += speed_y * dT;
}

void cRobot::fFindRoute(int from, int to)
{
	return;
}

#endif