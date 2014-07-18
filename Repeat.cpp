#include <vector>
#include <utility>
#include "Road.h"
#include "RobotClass.h"

void RepeatedTask(cRoad& mainRoad, std::vector<cRobot> &RobotContainer)
{
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		for (int j = i + 1; j < RobotContainer.size(); ++j)
		{
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
		std::pair<int, int> NowCoord = RobotContainer[i].fNowCoord();
		///Display robot on shot
	}
}