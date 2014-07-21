#ifndef __INI__H
#define __INI__H
#include <Windows.h>
#include <vector>
#include "CONST.h"
#include "Road.h"
#include "RobotClass.h"
extern void Initi(HWND hWnd, cRoad &mainRoad, std::vector<cRobot>& RobotContainer);
extern void Display(HWND hWnd, HDC hdc, PAINTSTRUCT ps, std::vector<cRobot>& RobotContainer, cRoad &mainRoad);
extern std::pair<bool, std::pair<coord, coord> > CoordCalculate(coord p1, coord p2, double a, double b, double c);
#endif