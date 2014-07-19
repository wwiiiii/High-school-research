/** * * * * * * * * * * * * * * * * * * * *
Project_Clustering
From 2014. 05. 10

�ڵ��� Ŭ������ ����(����, ����Լ�)

����
[�� ���ʹ� x, y ������ ���� ������ ��´�.]
- 1) ��ǥ
- 2) ��
- 3) �ӵ�
- 4) ID
- 5) ���� ��ü
- +) ��Ÿ DATA(�����) // ����, ������

�Լ�
- 1) ��ġ ���
- 2) ��/ô��, �ӵ�, ��ǥ ����

2014. 07. 17
Direct X���� WIN API ������� �뼱 ����, ���� ���� ��ü�� �ʿ� �����Ƿ� ����
** * * * * * * * * * * * * * * * * * * * */

#ifndef __Robot_Class
#define __Robot_Class
#include <utility>
#include <vector>
#define DATA int///��Ÿ �߰� �ڷ���
#define dT 0.001

//��ġ�� ���� �ۿ��ϴ� �� ��� �Լ�
//x, y�� ���� �޴� ��ü�� ��ǥ
//otherx, othery�� �����η��� �ۿ��Ű�� ��ü�� ��ǥ
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
		void init(int ID, double mas, DATA dat, int from, int to);//ID, ����, ������, ������� ������
		coord fNowCoord(void);///���� ��ġ ��ȯ
		void fRenewForce(double dX, double dY);///�� ���� - �ٸ� ��ü�� ��ȣ�ۿ�
		void fConstForce(std::vector<coord> & CheckPoints);///�⺻��� ���󰡰� �ϴ� ��
		void fRenewVelocity(void);///�ӵ� ����
		void fRenewCoord(void);///��ġ ����
		void fFindRoute(int from, int to);///üũ����Ʈ�� �־����� �� ��� ã��
};

#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     