#ifndef __INI_CPP
#define __INI_CPP

#include <Windows.h>
#include <cstdio>
#include "InitAndDisplay.h"
#define MASS (100.0)
///Load the given condition from "InputCondition.txt"
///display default menu

void Initi(HWND hWnd, cRoad &mainRoad, std::vector<cRobot>& RobotContainer)
{
	HDC hdc;
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
	return;
}

void Display(HWND hWnd, HDC hdc, PAINTSTRUCT ps)
{
	MoveToEx(hdc, 50, 50, NULL);
	LineTo(hdc,50, 700);
	LineTo(hdc, 1400, 700);
	LineTo(hdc, 1400, 50);
	LineTo(hdc, 50, 50);
	return;
}

#endif