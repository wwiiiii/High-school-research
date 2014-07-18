#ifndef __INI_CPP
#define __INI_CPP

#include <Windows.h>
#include <cstdio>
#include "RobotClass.cpp"
#include "Road.cpp"
#define MASS (100.0)
///Load the given condition from "InputCondition.txt"
///display default menu

void Initi(HWND hWnd, HDC hdc, cRoad &mainRoad, std::vector<cRobot>& RobotContainer)
{
	int segnum, cpnum, temp, carnum, u,v; coord tempcoord; line templine;
	freopen("InputCondition.txt","rt",stdin);
	scanf("%d%d",&segnum, &cpnum);
	mainRoad.Directions.reserve(cpnum + 5);
	for (int i = 0; i < segnum; ++i){
		scanf("%d %d %d %d",&templine.from.x , &templine.from.y, &templine.to.x, &templine.to.y);
		templine.a = templine.to.y - templine.from.y;
		templine.b =  -(templine.to.x - templine.from.x);
		templine.c = templine.to.x * templine.from.y - templine.from.y *  templine.to.x;
		if (templine.a < 0) templine.a *= -1, templine.b *= -1, templine.c *= -1;
		mainRoad.Lines.push_back(templine);
	}
	for (int i = 0; i < cpnum; ++i){
		scanf("%d %d",&tempcoord.x, &tempcoord.y);
		mainRoad.CheckPoints.push_back(tempcoord);
	}

	for (int i = 1; i <= cpnum; ++i){
		int n; scanf("%d", &n);
		while (n--){
			scanf("%d", &temp);
			mainRoad.Directions[i].push_back(temp);
		}
	}
	scanf("%d", &carnum);
	for (int i = 1; i <= carnum; ++i){
		cRobot tempRobot; scanf("%d %d",&u,&v);
		tempRobot.init(i, MASS, NULL, u, v);
		RobotContainer.push_back(tempRobot);
	}

	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);


	///	MoveToEx(hdc, container[i].x, container[i].y, NULL);
	///	Rectangle(hdc, container[i].x - Rsize, container[i].y - Rsize, container[i].x + Rsize, container[i].y + Rsize);
	EndPaint(hWnd, &ps);
	return;
}

#endif