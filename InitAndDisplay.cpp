#ifndef __INI_CPP
#define __INI_CPP

#include <Windows.h>
#include <cstdio>
#include <algorithm>
#include <vector>
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
		if(templine.from.x > templine.to.x){
			std::swap(templine.from, templine.to);
		}
		if(templine.from.x == templine.to.x && templine.from.y > templine.to.y){
			std::swap(templine.from, templine.to);
		}
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

std::pair<bool, std::pair<coord, coord> > CoordCalculate(coord p1, coord p2, double a, double b, double c){
	coord q1, q2;
	if (a == 0){
		int y = -(int)(c / b);
		q1.x = p1.x, q2.x = p2.x, q1.y = q2.y = y;
	}
	else if (b == 0){
		int x = -(int)(c / a);
		q1.x = q2.x = x, q1.y = p1.y, q2.y = p2.y;
	}
	else{
		int x1 = -(int)(b*p1.y + c) / a, x2 = -(int)(b*p2.y + c) / a, y1 = -(int)(a*p1.x + c) / b, y2 = -(int)(a*p2.x + c) / b;
		int a[2][4] = { { p1.x, p2.x, x1, x2 }, { y1, y2, p1.y, p2.y } };
		for (int i = 3; i >= 0; i--){
			for (int j = 0; j < i; j++){
				if (a[0][j] > a[0][j + 1]){
					int t = a[0][j];
					a[0][j] = a[0][j + 1];
					a[0][j + 1] = t;
					t = a[1][j];
					a[1][j] = a[1][j + 1];
					a[1][j + 1] = t;
				}
			}
		}
		q1.x = a[0][1], q2.x = a[0][2], q1.y = a[1][1], q2.y = a[1][2];
	}
	if (p1.x <= q1.x && p2.x >= q1.x && p1.y <= q1.y && p2.y >= q2.y)
		return std::make_pair(1, std::make_pair(q1, q2));
	else return std::make_pair(0, std::make_pair(q1, q2));
}

void Display(HWND hWnd, HDC hdc, PAINTSTRUCT ps, std::vector<cRobot>& RobotContainer, cRoad &mainRoad)
{

	///�⺻ Ʋ ����, Draw basic frame
	Rectangle(hdc, 70 / RatioX, 70 / RatioY, 1400 / RatioX, 700 / RatioY);
	Rectangle(hdc, 70 / RatioX, (700 + 30) / RatioY, (1920 - 70) / RatioX, (1000 - 70) / RatioY);
	Rectangle(hdc, (1400 + 30) / RatioX, 70 / RatioY, (1920 - 70) / RatioX, (70 + 300) / RatioY);
	Rectangle(hdc, (1400 + 30) / RatioX, (70 + 300 + 30) / RatioY, (1920 - 70) / RatioX, 700 / RatioY);
	
	
	///�ڵ����� �׸���
	HPEN my, old;
	my = CreatePen(PS_SOLID, 2 , RGB(243,97,220));
	old = (HPEN)SelectObject(hdc, my);
	coord center; center.x = (70 + 1400) / 2;  center.y = (70 + 700) / 2;
	coord passiveCoord = RobotContainer[mainRoad.PassiveID].fNowCoord();
	passiveCoord.x = 55000; passiveCoord.y = 75000;
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		coord p = RobotContainer[i].fNowCoord();
		p.x = -(passiveCoord.x - p.x) / mainRoad.scalex; p.x += center.x; p.x /= RatioX;
		p.y = -(passiveCoord.y - p.y) / mainRoad.scaley; p.y += center.y; p.y /= RatioY;
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
	


	///���ֹ� ������
	for (int i = 0; i < mainRoad.Obstacles.size(); ++i)
	{
		coord p = mainRoad.Obstacles[i];
		p.x = -(passiveCoord.x - p.x) / mainRoad.scalex; p.x += center.x; p.x /= RatioX;
		p.y = -(passiveCoord.y - p.y) / mainRoad.scaley; p.y += center.y; p.y /= RatioY;
		if (70 / RatioX <= p.x - 10 && p.x + 10 <= 1400 / RatioX && 70 / RatioY <= p.y && p.y <= 700 / RatioY){
				Rectangle(hdc, p.x - 10, p.y - 10, p.x + 10, p.y + 10);
		}
	}
	

	///���α׸���
	std::vector<coord> IntersectContainer;
	coord q1, q2; bool isIntersect;
	std::pair<bool , std::pair<coord, coord> >ret;
	q1.x = passiveCoord.x + mainRoad.scalex * (70 - center.x);
	q1.y = passiveCoord.y + mainRoad.scaley * (70 - center.y);
	q2.x = passiveCoord.x + mainRoad.scalex * (1400 - center.x);
	q2.y = passiveCoord.y + mainRoad.scaley * (700 - center.y);
	{TCHAR pnt[50]; wsprintf(pnt, TEXT("LU[%d,%d]"), q1.x, q1.y);;
	TextOut(hdc, 70 / RatioX, 70 / RatioY, pnt, lstrlen(pnt)); }
	for (int i = 0; i < mainRoad.Lines.size(); ++i)
	{
		ret = CoordCalculate(q1,q2,mainRoad.Lines[i].a , mainRoad.Lines[i].b, mainRoad.Lines[i].c);
		if (ret.first == false) continue;
		coord from = ret.second.first; coord to = ret.second.second;
		if(mainRoad.Lines[i].from.x <= from.x && from.x <= mainRoad.Lines[i].to.x &&
		   mainRoad.Lines[i].from.y <= from.x && from.x <= mainRoad.Lines[i].to.y) IntersectContainer.push_back(from);
		if(mainRoad.Lines[i].from.x <= to.x && to.x <= mainRoad.Lines[i].to.x &&
		   mainRoad.Lines[i].from.y <= to.x && to.x <= mainRoad.Lines[i].to.y) IntersectContainer.push_back(to);
		if(q1.x <= mainRoad.Lines[i].from.x && mainRoad.Lines[i].from.x <= q2.x &&
		   q2.y <= mainRoad.Lines[i].from.y && mainRoad.Lines[i].from.y <= q1.y) IntersectContainer.push_back(mainRoad.Lines[i].from);
		if(q1.x <= mainRoad.Lines[i].to.x && mainRoad.Lines[i].to.x <= q2.x &&
		   q2.y <= mainRoad.Lines[i].to.y && mainRoad.Lines[i].to.y <= q1.y) IntersectContainer.push_back(mainRoad.Lines[i].to);
		
		for(int q = 0; q<IntersectContainer.size(); ++q)
		{
			IntersectContainer[q].x = (IntersectContainer[q].x - passiveCoord.x) / mainRoad.scalex; IntersectContainer[q].x += center.x; IntersectContainer[q].x/=RatioX;
			IntersectContainer[q].y = (IntersectContainer[q].y - passiveCoord.y) / mainRoad.scaley; IntersectContainer[q].y += center.y; IntersectContainer[q].y/=RatioY;
			MoveToEx(hdc, IntersectContainer[q].x, IntersectContainer[q].y, NULL);
		}

		for (int q = 0; q+1<IntersectContainer.size(); ++q)
		{
			MoveToEx(hdc, IntersectContainer[q].x, IntersectContainer[q].y, NULL);
			LineTo(hdc, IntersectContainer[q + 1].x, IntersectContainer[q + 1].y);
		}
		
		//from.x = (from.x - passiveCoord.x) / mainRoad.scalex; from.x += center.x; from.x /= RatioX;
		//from.y = (from.y - passiveCoord.y) / mainRoad.scaley; from.y += center.y; from.y /= RatioY;
		//to.x = (to.x - passiveCoord.x) / mainRoad.scalex; to.x += center.x; to.x /= RatioX;
		//to.y = (to.y - passiveCoord.y) / mainRoad.scaley; to.y += center.y; to.y /= RatioY;
		//MoveToEx(hdc, from.x, from.y, NULL); LineTo(hdc, to.x, to.y);
	}

	///��ġ�� ��������
	for (int i = 0; i < RobotContainer.size(); ++i)
	{
		TCHAR pnt[100];
		wsprintf(pnt, TEXT("%d => (%d,%d)"), i, RobotContainer[i].NowCoord.x , RobotContainer[i].NowCoord.y);;
		TextOut(hdc, 1500 / RatioX, 30 * i, pnt, lstrlen(pnt));
	}
	TCHAR pnt[10000]; wsprintf(pnt, TEXT("Zoom Status : (%d / %d)"), (int)(mainRoad.scalex*1000), (int)(mainRoad.scaley*1000));;
	TextOut(hdc, 70 / RatioX, 800, pnt, lstrlen(pnt));
	return;
}

#endif
