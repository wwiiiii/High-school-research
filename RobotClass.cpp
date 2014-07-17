#include <utility>
#include "RobotClass.h"
#define DATA int///기타 추가 자료형
#define dT 0.001

//위치에 따라 작용하는 힘 계산 함수
//x, y가 힘을 받는 물체의 좌표
//otherx, othery가 만유인력을 작용시키는 물체의 좌표

//생성자, 위치는 랜덤, id와 질량은 주어지고, data도 주어지고, 속도도 주어지고, 받는 힘은 0
void cRobot::init(int ID, double mas, DATA dat, double s_x, double s_y)
{
	id = ID;
	mass = mas;
	data = dat;
	speed_x = s_x; speed_y = s_y;
	force_x = force_y = coord_x = coord_y = 0;
}

///현재 위치 반환
std::pair<double, double> cRobot::fNowCoord(void){
	return std::make_pair(coord_x, coord_y);
}
	///위치 출력, DirectX 이용 예정
void cRobot::fShow(void){
	return;
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
	coord_x += speed_x * dT;
	coord_y += speed_y * dT;
}
