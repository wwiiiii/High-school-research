#include <utility>
#include "RobotClass.h"
#define DATA int///��Ÿ �߰� �ڷ���
#define dT 0.001

//��ġ�� ���� �ۿ��ϴ� �� ��� �Լ�
//x, y�� ���� �޴� ��ü�� ��ǥ
//otherx, othery�� �����η��� �ۿ��Ű�� ��ü�� ��ǥ

//������, ��ġ�� ����, id�� ������ �־�����, data�� �־�����, �ӵ��� �־�����, �޴� ���� 0
void cRobot::init(int ID, double mas, DATA dat, double s_x, double s_y)
{
	id = ID;
	mass = mas;
	data = dat;
	speed_x = s_x; speed_y = s_y;
	force_x = force_y = coord_x = coord_y = 0;
}

///���� ��ġ ��ȯ
std::pair<double, double> cRobot::fNowCoord(void){
	return std::make_pair(coord_x, coord_y);
}
	///��ġ ���, DirectX �̿� ����
void cRobot::fShow(void){
	return;
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
	coord_x += speed_x * dT;
	coord_y += speed_y * dT;
}
