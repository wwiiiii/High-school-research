#include <vector>
#include <utility>
#include "Road.h"
#include "RobotClass.h"

void RepeatedTask(cRoad& mainRoad, std::vector<cRobot> &RobotContainer)
{
	coord p1, p2; double force, dist, forcex, forcey;
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		RobotContainer[i].force_x = RobotContainer[i].force_y = 0;
		//RobotContainer[i].fConstForce();
	}
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		p1 = RobotContainer[i].fNowCoord();
		for (int j = i + 1; j < RobotContainer.size(); ++j)
		{
			p2 = RobotContainer[j].fNowCoord();
			dist = sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) );
			force = 0;// dist;
			forcex = force * (p1.x - p2.x) / dist / 10000000;
			forcey = force * (p1.y - p2.y) / dist / 10000000;
			if (dist > 100){
				RobotContainer[i].fRenewForce(forcex, forcey);
				RobotContainer[j].fRenewForce(-forcex, -forcey);
			}
			else{
				RobotContainer[i].fRenewForce(-forcex,- forcey);
				RobotContainer[j].fRenewForce(forcex, forcey);
			}

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
		RobotContainer[i].speed_x /= 1000000000;
		RobotContainer[i].speed_y /= 1000000000;
		RobotContainer[i].fRenewCoord();
	}
}