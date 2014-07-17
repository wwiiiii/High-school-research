#include <ctime>
#include <cstdio>
#include <cstdlib>
#include "RobotClass.h"
#include <vector>
#include <utility>

using namespace std;

vector<cRobot> Container;

void input()
{
	int n;
	puts("자동차의 개수를 입력하시오");
	scanf("%d",&n);
	puts("행운을 빕니다!");
	ini(n);
}

void ini(int n)
{
	
	process(n);
}

void process(int n)
{
	pair<double, double> coo;
	while(true)
	{
		//힘 갱신작용
		for(int i=0;i<n;i++)	
		{
			for(int j=0;j<n;++j)
			{
				if(i==j) continue;
				coo = Container[j].fNowCoord();
				Container[i].fRenewForce(coo.first, coo.second);
			}
		}
		//속도 갱신 위치 갱신 위치 출력
		for(int i=0;i<n;i++)
		{
			Container[i].fRenewVelocity();
			Container[i].fRenewCoord();
			Container[i].fShow();
		}
	}
	return;
}

int main()
{
	input();
}
