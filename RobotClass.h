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
#define DATA int///��Ÿ �߰� �ڷ���
#define dT 0.001

//��ġ�� ���� �ۿ��ϴ� �� ��� �Լ�
//x, y�� ���� �޴� ��ü�� ��ǥ
//otherx, othery�� �����η��� �ۿ��Ű�� ��ü�� ��ǥ

class cRobot{

	private:
		double speed_x, speed_y;
		double force_x, force_y;
		int coord_x, coord_y;
		double mass;
		int id;
		DATA data;

	public:
		void init(int ID, double mas, DATA dat, double s_x, double s_y);//������, ��ġ�� ����, id�� ������ �־�����, data�� �־�����, �ӵ��� �־�����, �޴� ���� 0
		std::pair<int, int> fNowCoord(void);///���� ��ġ ��ȯ
		void fRenewForce(double dX, double dY);///�� ���� - �ٸ� ��ü�� ��ȣ�ۿ�
		void fRenewVelocity(void);///�ӵ� ����
		void fRenewCoord(void);///��ġ ����
		void fFindRoute(int from, int to);///üũ����Ʈ�� �־����� �� ��� ã��
};

#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     