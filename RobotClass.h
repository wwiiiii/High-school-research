/** * * * * * * * * * * * * * * * * * * * *
Project_Clustering
From 2014. 05. 10

자동차 클래스의 정의(변수, 멤버함수)

변수
[각 벡터는 x, y 성분을 각각 변수로 잡는다.]
- 1) 좌표
- 2) 힘
- 3) 속도
- 4) ID
- 5) 도형 객체
- +) 기타 DATA(예비용) // 질량, 반지름

함수
- 1) 위치 출력
- 2) 인/척력, 속도, 좌표 갱신
** * * * * * * * * * * * * * * * * * * * */

#ifndef __Robot_Class
#define __Robot_Class

#define SHAPE int///도형 객체의 자료형
#define DATA int///기타 추가 자료형
#define dT 0.001

//위치에 따라 작용하는 힘 계산 함수
//x, y가 힘을 받는 물체의 좌표
//otherx, othery가 만유인력을 작용시키는 물체의 좌표

class cRobot{
	
	private:
		double speed_x, speed_y;
		double force_x, force_y;
		double coord_x, coord_y;
		double mass;
		int id;
		DATA data;
		SHAPE figure;
	
	public:
		//생성자, 위치는 랜덤, id와 질량은 주어지고, data도 주어지고, 속도도 주어지고, 받는 힘은 0
		cRobot(int ID, double mas, DATA dat, double s_x, double s_y)
		{
			id = ID;
			mass = mas;
			data = dat;
			speed_x = s_x; speed_y = s_y;
			force_x = force_y = coord_x = coord_y = 0;
		}
		//이것은 함수
		pair<double, double> Interaction(double x, double y, double otherx, double othery)
		{

		}
		///현재 위치 반환
		pair<double, double> fNowCoord(void){
			return std::make_pair(coord_x,coord_y);
		}
		
		///위치 출력, DirectX 이용 예정
		void fShow(void){
			return;
		}

		///힘 갱신 - 다른 객체랑 상호작용
		void fRenewForce(double otherCoord_X, double otherCoord_Y){
			pair<double, double> interact = Interaction(coord_x, coord_y, otherCoord_X, otherCoord_Y);
			force_x += interact.first;
			force_y += interact.second;
			///상대 위치를 받아서 힘 갱신하는거 추가해야됨
		}

		///속도 갱신
		void fRenewVelocity(void){
			speed_x += (force_x / mass) * dT;
			speed_y += (force_y / mass) * dT;
		}

		///위치 갱신
		void fRenewCoord(void){
			coord_x += speed_x * dT;
			coord_y += speed_y * dT;					
		}

	
};




#endif
