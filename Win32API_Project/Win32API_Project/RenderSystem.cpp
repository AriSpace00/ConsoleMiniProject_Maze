#include <stdio.h>
#include "renderSystem.h"


namespace render
{
    bool bScreenIndex;
    HANDLE hScreen[2];

    SMALL_RECT consoleScreenSize;
    INT consoleScreenX;
    INT consoleScreenY;

    SMALL_RECT updateScreenSize;
    INT updateScreenX;
    INT updateScreenY;

    SMALL_RECT GetPlayerMovableRect()
    {
        return updateScreenSize;
    }

    HANDLE GetScreenHandle()
    {
        int index = (bScreenIndex ? 1 : 0);

        return hScreen[index];
    }

    void GotoXY(int x, int y)
    {
        COORD Cur = { x, y };

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
    }

    void setColor(int forground, int background)
    {
        int code = forground + background * 16;
        SetConsoleTextAttribute(hScreen[bScreenIndex], code);
    }

    void InitScreen()
    {
        
        
        // ȭ�� ���� 2���� �����.
        hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

        // �����̴� Ŀ���� �� ���� ��Ű��.
        CONSOLE_CURSOR_INFO cursorInfo = { 0, };
        cursorInfo.bVisible = 0; // Ŀ���� ������ ���� ����(0�̸� �Ⱥ���, 0���� ���� ���̸� ����)
        cursorInfo.dwSize = 1; // Ŀ���� ũ�⸦ ���� (1~100 ���̸� ����)
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        SetConsoleCursorInfo(hScreen[0], &cursorInfo);
        SetConsoleCursorInfo(hScreen[1], &cursorInfo);


        // �ܼ�â ũ�⸦ ���� ����.
        // ������ ���� �ִµ� �н� ������ �׳�, �������� ������ �ۼ�.
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        consoleScreenSize.Left = csbi.srWindow.Left;
        consoleScreenSize.Right = csbi.srWindow.Right;
        consoleScreenSize.Bottom = csbi.srWindow.Bottom;
        consoleScreenSize.Top = csbi.srWindow.Top;

        consoleScreenX = csbi.dwSize.X;
        consoleScreenY = csbi.dwSize.Y;

        // ���� ������ ȭ�� ������ ��������. �ܼ� ũ�� ���� �簢���̶�� �����ϸ� �˴ϴ�.
        updateScreenSize.Left = consoleScreenSize.Left;
        updateScreenSize.Right = consoleScreenSize.Right;
        updateScreenSize.Bottom = consoleScreenSize.Bottom;
        updateScreenSize.Top = consoleScreenSize.Top;

        updateScreenX = consoleScreenX;
        updateScreenY = consoleScreenY;
    }

    void ScreenFlipping()
    {
        SetConsoleActiveScreenBuffer(GetScreenHandle());
        bScreenIndex = !bScreenIndex;
    }

    void ScreenClear()
    {
        COORD Coor = { updateScreenSize.Left, updateScreenSize.Top };
        DWORD dw;

        for (int y = 0; y < updateScreenY; y++)
        {
            render::setColor(render::white, render::black);
            Coor.Y = updateScreenSize.Top + y;

            FillConsoleOutputCharacter(GetScreenHandle(), ' ', updateScreenX, Coor, &dw);
        }
    }

    void ScreenClear2()
    {
        COORD Coor = { updateScreenSize.Left, updateScreenSize.Top };
        DWORD dw;

        for (int y = 0; y < updateScreenY; y++)
        {
            Coor.Y = updateScreenSize.Top + y;

            FillConsoleOutputCharacter(hScreen[0], ' ', updateScreenX, Coor, &dw);
            FillConsoleOutputCharacter(hScreen[1], ' ', updateScreenX, Coor, &dw);
            FillConsoleOutputCharacter(GetScreenHandle(), ' ', updateScreenX, Coor, &dw);
        }                              
    }

    void SetStdScreen()
    {
        SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
    }
        
    void SetBackScreen()
    {
        SetConsoleActiveScreenBuffer(GetScreenHandle());
    }


    void ScreenRelease()
    {
        CloseHandle(hScreen[0]);
        CloseHandle(hScreen[1]);
    }

    // �ܼ��̴� ���� �ȼ� �������ƴ϶� ���� ����...�� ���ھ� �׷�(?) �ַƴϴ�.
    void ScreenDraw(int x, int y, const char c)
    {
        DWORD dw;
        COORD Cur = { x, y };
        char buffer[10];
        sprintf_s(buffer, "%c", c);

        SetConsoleCursorPosition(GetScreenHandle(), Cur);

        WriteFile(GetScreenHandle(), buffer, 1, &dw, NULL);
    }

    void ScreenDraw(int x, int y, const char* pStr)
    {
        DWORD dw;
        COORD Cur = { x, y };

        SetConsoleCursorPosition(GetScreenHandle(), Cur);

        WriteFile(GetScreenHandle(), pStr, strlen(pStr), &dw, NULL);
    }

    void ScreenDraw2(int x, int y, const char* pStr)
    {
        DWORD dw;
        COORD Cur = { x, y };

        SetConsoleCursorPosition(hScreen[0], Cur);
        SetConsoleCursorPosition(hScreen[1], Cur);
        SetConsoleCursorPosition(GetScreenHandle(), Cur);

        WriteFile(hScreen[0], pStr, strlen(pStr), &dw, NULL);
        WriteFile(hScreen[1], pStr, strlen(pStr), &dw, NULL);
    }

    void ScreenDraw3(int x, int y, const char* pStr)
    {
        DWORD dw;
        COORD Cur = { 45, 16 };

        SetConsoleCursorPosition(GetScreenHandle(), Cur);

        WriteFile(GetScreenHandle(), pStr, strlen(pStr), &dw, NULL);
    }

    void ScreenDraw4(int x, int y, const char* pStr)
    {
        DWORD dw;
        COORD Cur = { 5, 16 };

        SetConsoleCursorPosition(GetScreenHandle(), Cur);

        WriteFile(GetScreenHandle(), pStr, strlen(pStr), &dw, NULL);
    }

    void DrawBorder()
    {
        // ���� ����. Y ���� ���� �ȴ�.
        for (int x = updateScreenSize.Left - 1; x < updateScreenSize.Right + 1; x++)
        {
            ScreenDraw(x, updateScreenSize.Top - 1, '#');
        }

        // �Ʒ��� ����. Y ���� ���� �ȴ�.
        for (int x = updateScreenSize.Left - 1; x < updateScreenSize.Right + 1; x++)
        {
            ScreenDraw(x, updateScreenSize.Bottom + 1, '#');
        }

        // ���� ����, X ���� ���� �ȴ�.
        for (int y = updateScreenSize.Top - 1; y < updateScreenSize.Bottom + 1; y++)
        {
            ScreenDraw(updateScreenSize.Left - 1, y, '#');
        }

        // ������ ����, X ���� ���� �ȴ�.
        for (int y = updateScreenSize.Top - 1; y < updateScreenSize.Bottom + 1; y++)
        {
            ScreenDraw(updateScreenSize.Right + 1, y, '#');
        }
    }
};