#include <vector>
#include <utility>
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
		RobotContainer[i].fConstForce(mainRoad.CheckPoints);
	}
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		p1 = RobotContainer[i].fNowCoord();
		for (int j = i + 1; j < RobotContainer.size(); ++j)
		{
			p2 = RobotContainer[j].fNowCoord();
			dist = sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) );
			deltax = dist - Xzero;
			force = K  * deltax;// dist;
			/*if (dist > 700){
				forcex = force * (p2.x - p1.x) / dist;
				forcey = force * (p2.y - p1.y) / dist;
			}
			else {
				if (dist != 0){
					forcex = 1000000 / dist;
					forcey = 1000000 / dist;
					forcex *= (p2.x - p1.x) / dist;
					forcey *= (p2.y - p1.y) / dist;
				}
				else forcex = forcey = -9321;
			}*/
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
	
	/*for (int i = 0; i < RobotContainer.size(); ++i)
	{
		for (int j = 0; j < mainRoad.Lines.size(); ++j)
		{
			std::pair<double, double> F = mainRoad.fRoadForce(RobotContainer[i]);
			RobotContainer[i].fRenewForce(F.first,F.second);
		}
		///Process Interaction between robot and lines
	}*/
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		RobotContainer[i].fRenewVelocity();
		RobotContainer[i].fRenewCoord();
	}
}
