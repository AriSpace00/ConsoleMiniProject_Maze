#pragma once
#include "Main.h"
#include "InputSystem.h"

void gLoop(int);
void titleDraw();
int menuDraw();
int maplistDraw();
int infoDraw();
void gameClearDraw();

void drawMap();
void drawUI(int*, int*, int*);
int keyControl();

bool CheckWall(int x, int y);
bool CheckGoal(int x, int y);
bool CheckKey(int y, int x);
bool CheckFireWall(int y, int x);
