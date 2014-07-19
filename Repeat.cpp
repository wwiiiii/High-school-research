#include <vector>
#include <utility>
#include "Road.h"
#include "RobotClass.h"

void RepeatedTask(cRoad& mainRoad, std::vector<cRobot> &RobotContainer)
{
	coord p1, p2; double force, dist, forcex, forcey;
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		p1 = RobotContainer[i].fNowCoord();
		for (int j = i + 1; j < RobotContainer.size(); ++j)
		{
			p2 = RobotContainer[j].fNowCoord();
			dist = sqrt( (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) );
			force = dist * 1234;
			forcex = force / 2;
			forcey = force / 2;
			RobotContainer[i].fRenewForce(forcex, forcey);
			RobotContainer[j].fRenewForce(forcex, forcey);
			///Process Interaction between two robots;
			///RobotContainer[i], RobotContainer[j]
		}
	}

	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		///Process Interaction between robot and lines
	}
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		RobotContainer[i].fRenewVelocity();
		RobotContainer[i].fRenewCoord();
		coord NowCoord = RobotContainer[i].fNowCoord();
		///Display robot on shot
	}
}