#ifndef __INI_CPP
#define __INI_CPP

#include <Windows.h>
#include <cstdio>
#include "InitAndDisplay.h"

///Load the given condition from "InputCondition.txt"
///display default menu

void Initi(HWND hWnd, cRoad &mainRoad, std::vector<cRobot>& RobotContainer)
{
	HDC hdc; cRobot tempRobot;
	int segnum, cpnum, temp, carnum, u,v; coord tempcoord; line templine;
	freopen("TEXT.txt","rt",stdin);
	scanf("%d%d",&segnum, &cpnum);

	for (int i = 0; i < cpnum + 5; ++i){
		std::vector<int> TEMP;
		mainRoad.Directions.push_back(TEMP);
	}

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

	for (int i = 0; i < cpnum; ++i){
		int n; scanf("%d", &n);
		while (n--){
			scanf("%d", &temp);
			mainRoad.Directions[i].push_back(temp);
		}
	}
	scanf("%d", &carnum);

	for (int i = 0; i < carnum; ++i){
		scanf("%d %d",&u,&v);
		tempcoord = mainRoad.CheckPoints[0];
		//tempcoord.y += 30 * i;
		//tempcoord.x += 30 * i;
		tempRobot.init(i, MASS, NULL, u, v, tempcoord);
		RobotContainer.push_back(tempRobot);
	}
	return;
}

void Display(HWND hWnd, HDC hdc, PAINTSTRUCT ps, std::vector<cRobot>& RobotContainer, cRoad &mainRoad)
{

	///기본 틀 생성, Draw basic frame
	Rectangle(hdc, 70 / RatioX, 70 / RatioY, 1400 / RatioX, 700 / RatioY);
	Rectangle(hdc, 70 / RatioX, (700 + 30) / RatioY, (1920 - 70) / RatioX, (1000 - 70) / RatioY);
	Rectangle(hdc, (1400 + 30) / RatioX, 70 / RatioY, (1920 - 70) / RatioX, (70 + 300) / RatioY);
	Rectangle(hdc, (1400 + 30) / RatioX, (70 + 300 + 30) / RatioY, (1920 - 70) / RatioX, 700 / RatioY);
	
	
	///자동차들 그리기
	HPEN my, old;
	my = CreatePen(PS_SOLID, 2 , RGB(243,97,220));
	old = (HPEN)SelectObject(hdc, my);
	coord center; center.x = (70 + 1400) / 2;  center.y = (70 + 700) / 2;
	coord passiveCoord = RobotContainer[mainRoad.PassiveID].fNowCoord();
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		coord p = RobotContainer[i].fNowCoord();
		p.x = (passiveCoord.x - p.x) / mainRoad.scalex; p.x += center.x; p.x /= RatioX;
		p.y = (passiveCoord.y - p.y) / mainRoad.scaley; p.y += center.y; p.y /= RatioY;
		if (70 / RatioX <= p.x - 10 && p.x + 10 <= 1400 / RatioX && 70 / RatioY <= p.y && p.y <= 700 / RatioY){
			if (i != mainRoad.PassiveID)	{
				Rectangle(hdc, p.x - 10, p.y - 10, p.x + 10, p.y + 10);
			}
			else Ellipse(hdc, p.x - 10, p.y - 10, p.x + 10, p.y + 10);
			TCHAR pnt[10];	wsprintf(pnt, TEXT("%d"), i);;
			TextOut(hdc, p.x - 5, p.y - 5, pnt, lstrlen(pnt));
		}
	}
	SelectObject(hdc, old);
	DeleteObject(my);
	
	///장애물 띄우기
	for (int i = 0; i < mainRoad.Obstacles.size(); ++i)
	{
		coord p = mainRoad.Obstacles[i];
		p.x = (passiveCoord.x - p.x) / mainRoad.scalex; p.x += center.x; p.x /= RatioX;
		p.y = (passiveCoord.y - p.y) / mainRoad.scaley; p.y += center.y; p.y /= RatioY;
		if (70 / RatioX <= p.x - 10 && p.x + 10 <= 1400 / RatioX && 70 / RatioY <= p.y && p.y <= 700 / RatioY){
				Rectangle(hdc, p.x - 10, p.y - 10, p.x + 10, p.y + 10);
		}
	}
	

	///도로그리기
	coord q1, q2; bool isIntersect;
	for (int i = 0; i < mainRoad.Lines.size(); ++i)
	{
		isIntersect = false;
	}


	///위치들 출력하자
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		TCHAR pnt[100];
		wsprintf(pnt, TEXT("(%d,%d)"), RobotContainer[i].NowCoord.x , RobotContainer[i].NowCoord.y);;
		TextOut(hdc, 1500 / RatioX, 30 * i, pnt, lstrlen(pnt));
	}
	TCHAR pnt[10000]; wsprintf(pnt, TEXT("Zoom Status : (%d / %d)"), (int)(mainRoad.scalex*1000), (int)(mainRoad.scaley*1000));;
	TextOut(hdc, 70 / RatioX, 800, pnt, lstrlen(pnt));
	return;
}

#endif