#pragma once
#include <Windows.h>

namespace render
{

    void InitScreen();
    void ScreenRelease();

    void ScreenFlipping();
    void ScreenClear();
    void ScreenClear2();

	void SetStdScreen();
	void SetBackScreen();

	//  함수 오버로딩에 대해 알아 봅시다.
	void ScreenDraw(int x, int y, const char c);
	void ScreenDraw(int x, int y, const char* pStr);
	void ScreenDraw2(int x, int y, const char* pStr);
    void ScreenDraw3(int x, int y, const char* pStr);
    void ScreenDraw4(int x, int y, const char* pStr);

    SMALL_RECT GetPlayerMovableRect();

    void GotoXY(int x, int y);

    void DrawBorder();
    enum
    {
        black,
        blue,
        green,
        cyan,
        red,
        purple,
        brown,
        lightgray,
        darkgray,
        lightblue,
        lightgreen,
        lightcyan,
        lightred,
        lightpurple,
        yellow,
        white
    };


    void setColor(int, int);



};
