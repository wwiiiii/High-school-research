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

	for (int i = 1; i <= cpnum; ++i){
		int n; scanf("%d", &n);
		while (n--){
			scanf("%d", &temp);
			mainRoad.Directions[i].push_back(temp);
		}
	}
	scanf("%d", &carnum);

	for (int i = 0; i < carnum; ++i){
		scanf("%d %d",&u,&v);
		tempRobot.init(i, MASS, NULL, u, v);
		RobotContainer.push_back(tempRobot);
	}
	return;
}

void Display(HWND hWnd, HDC hdc, PAINTSTRUCT ps, std::vector<cRobot>& RobotContainer, cRoad &mainRoad)
{
	///기본 틀 생성, Draw basic frame
	Rectangle(hdc, 70, 70, 1400, 700);
	Rectangle(hdc, 70, 700 + 30, 1920 - 70, 1000 - 70);
	Rectangle(hdc, 1400 + 30, 70, 1920 - 70, 70 + 300);
	Rectangle(hdc, 1400 + 30, 70 + 300 + 30, 1920 - 70, 700);
	static int cnt=0; cnt++;
	FILE *fp2 = fopen("cnt.txt", "wt");
	fprintf(fp2," asdfasdf %d",cnt);
	///자동차들 그리기
	mainRoad.PassiveID = 1; mainRoad.scalex = mainRoad.scaley = 1;
	coord center; center.x = (70 + 1400) / 2;  center.y = (70 + 700) / 2;
	coord passiveCoord = RobotContainer[mainRoad.PassiveID].fNowCoord();
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		coord p = RobotContainer[i].fNowCoord();
		p.x = center.x + (passiveCoord.x - p.x) / mainRoad.scalex;
		p.y = center.y + (passiveCoord.y - p.y) / mainRoad.scaley;
		if (70 <= p.x - 10 && p.x + 10 <= 1400 && 70 <= p.y && p.y <= 700){
			if (i != mainRoad.PassiveID)	Rectangle(hdc, p.x - 10, p.y - 10, p.x + 10, p.y + 10);
			else Ellipse(hdc, p.x - 10, p.y - 10, p.x + 10, p.y + 10);
		}
	}
	
	///도로그리기


	return;
}

#endif