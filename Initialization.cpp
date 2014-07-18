#ifndef __INI_CPP
#define __INI_CPP

#include <Windows.h>
#include <cstdio>
#include "RobotClass.cpp"
#include "Road.cpp"

///Load the given condition from "InputCondition.txt"
///display default menu

void Initi(HWND hWnd, HDC hdc, cRoad &mainRoad, std::vector<cRobot>& RobotContainer)
{
	int segnum, cpnum; coord tempcoord; line templine;
	freopen("InputCondition.txt","rt",stdin);
	scanf("%d%d",&segnum, &cpnum);
	for (int i = 0; i < segnum; ++i){
		scanf("%d %d %d %d",&templine.from.x , &templine.from.y, &templine.to.x, &templine.to.y);
		templine.a = templine.to.y - templine.from.y;
		templine.b =  -(templine.to.x - templine.from.x);
		templine.c = templine.to.x * templine.from.y - templine.from.y *  templine.to.x;
		if (templine.a < 0) templine.a *= -1, templine.b *= -1, templine.c *= -1;
		mainRoad.Lines.push_back(templine);
	}
	for (int i = 0; i < cpnum; ++i){
	
	}
	

	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);


	///	MoveToEx(hdc, container[i].x, container[i].y, NULL);
	///	Rectangle(hdc, container[i].x - Rsize, container[i].y - Rsize, container[i].x + Rsize, container[i].y + Rsize);
	EndPaint(hWnd, &ps);
	return;
}

#endif