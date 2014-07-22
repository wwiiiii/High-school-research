#include <vector>
#include <utility>
#include <algorithm>
#include "Road.h"
#include "RobotClass.h"

void RepeatedTask(cRoad& mainRoad, std::vector<cRobot> &RobotContainer)
{
	coord p1, p2; double force, dist, forcex, forcey, deltax;
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		RobotContainer[i].force_x = RobotContainer[i].force_y = 0;
		RobotContainer[i].speed_x *= 0.9;
		RobotContainer[i].speed_y *= 0.9;
		//RobotContainer[i].fConstForce(mainRoad.CheckPoints);
	}
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		p1 = RobotContainer[i].fNowCoord();
		for (int j = i + 1; j < RobotContainer.size(); ++j)
		{
			p2 = RobotContainer[j].fNowCoord();
			dist = sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) );
			if (dist > MAX_DIST) continue;
			deltax = dist - Xzero;
			force = K  * deltax;
			if (dist != 0){
				forcex = force * (p2.x - p1.x) / dist;
				forcey = force * (p2.y - p1.y) / dist;
			}
			else forcex = forcey = 1000;
			RobotContainer[i].fRenewForce(forcex, forcey);
			RobotContainer[j].fRenewForce(-forcex, -forcey);

			///Process Interaction between two robots;
			///RobotContainer[i], RobotContainer[j]
		}
	}

	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		for (int j = 0; j < mainRoad.Lines.size(); ++j)
		{
			double a = mainRoad.Lines[j].a;
			double b = mainRoad.Lines[j].b;
			double c = mainRoad.Lines[j].c;
			coord now = RobotContainer[i].NowCoord;
			if (now.x <= mainRoad.Lines[j].from.x-50 || mainRoad.Lines[j].to.x+50 <= now.x ||
				now.y <= std::min(mainRoad.Lines[j].from.y, mainRoad.Lines[j].to.y)-50 || std::max(mainRoad.Lines[j].from.y, mainRoad.Lines[j].to.y)+50 <= now.y) continue;
			if (abs(now.x - mainRoad.Lines[j].from.x) <= 10 || abs(now.x - mainRoad.Lines[j].to.x) <= 10 ||
				abs(now.y - mainRoad.Lines[j].from.y) <= 10 || abs(now.y - mainRoad.Lines[j].to.y) <= 10) continue;
			double dista = abs(a * now.x + b * now.y + c) / sqrt(a*a+b*b);
			if (dista >= MAX_DIST2) continue;
			if (dista <= 100) dist = 100;
			double force1 = 100000 / dista;
			
			double forx = -force1 * a / sqrt(a*a+b*b);
			double fory = -force1 * b / sqrt(a*a + b*b);

			RobotContainer[i].fRenewForce(forx, fory);
		}
		///Process Interaction between robot and lines
	}

	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		p1 = RobotContainer[i].fNowCoord();
		for (int j = 0; j < mainRoad.Obstacles.size(); ++j)
		{
			p2 = mainRoad.Obstacles[j];
			dist = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
			if (dist > MAX_DIST) continue;
			deltax = dist - Xzero;
			force = K  * deltax;
			if (dist != 0){
				forcex = force * (p2.x - p1.x) / dist;
				forcey = force * (p2.y - p1.y) / dist;
			}
			else forcex = forcey = 1000;
			RobotContainer[i].fRenewForce(forcex, forcey);
			///Process Interaction between robot and obstacles
			///RobotContainer[i], RobotContainer[j]
		}
	}


	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		RobotContainer[i].fRenewVelocity();
		RobotContainer[i].fRenewCoord();
	}
}
