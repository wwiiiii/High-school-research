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

2014. 07. 17
Direct X에서 WIN API 사용으로 노선 변경, 따로 도형 객체가 필요 없으므로 제거
** * * * * * * * * * * * * * * * * * * * */

#ifndef __Robot_Class
#define __Robot_Class
#include <utility>
#include <vector>
#define DATA int///기타 추가 자료형
#define dT 0.001

//위치에 따라 작용하는 힘 계산 함수
//x, y가 힘을 받는 물체의 좌표
//otherx, othery가 만유인력을 작용시키는 물체의 좌표
typedef struct{ int x, y; }coord;
class cRobot{

	private:
		std::vector<int> BasicRoute;
		int RouteNowAt;
		double speed_x, speed_y;
		double force_x, force_y;
		double BasicForceX, BasicForceY;///force to follow basic route(from -> to)
		coord NowCoord;
		bool isAutoDriving;
		double mass;
		int id;
		DATA data;

	public:
		void init(int ID, double mas, DATA dat, int from, int to);//ID, 질량, 데이터, 출발점과 도착점
		coord fNowCoord(void);///현재 위치 반환
		void fRenewForce(double dX, double dY);///힘 갱신 - 다른 객체랑 상호작용
		void fConstForce(std::vector<coord> & CheckPoints);///기본경로 따라가게 하는 힘
		void fRenewVelocity(void);///속도 갱신
		void fRenewCoord(void);///위치 갱신
		void fFindRoute(int from, int to);///체크포인트가 주어졌을 때 경로 찾기
};

#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     