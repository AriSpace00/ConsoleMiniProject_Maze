#include <cassert>

#include "LevelSystem.h"
#include "Main.h"
#include "ColorSystem.h"
#include "RenderSystem.h"
#include "InputSystem.h"

int tempMap[16][76];

int easyMap[16][76] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,3,0,1},
    {1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,3,0,1},
    {1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,3,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int hardMap[16][76] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1},
    {1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,3,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,3,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,3,0,0,0,0,1,0,0,1},
    {1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,0,0,3,1,0,0,1,3,0,0,0,0,0,0,0,1,0,0,0,0,0,1,3,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1},
    {1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,3,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,2,2,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

struct Position
{
    int y;
    int x;
};

Position Goal = { 13, 71 };
Position Goal1 = { 13, 70 };

bool CheckWall(int y, int x)
{
    if (tempMap[y][x] != 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool CheckGoal(int y, int x)
{
    char buffer[64] = "";
    sprintf_s(buffer, "%d, %d\n", y, x);
    OutputDebugStringA(buffer);

    if ((Goal.y == y && Goal.x == x) || (Goal1.y == y && Goal1.x == x))
    {      
        return true;
    }
    return false;      
}

int key_position[13][2] = {
    {3, 4},
    {13,28},
    {13,29},
    {1,70},
    {5,70},
    {7,16},
    {3,25},
    {13,26},
    {11,40},
    {7,16},
    {11,40},
    {7,31},
    {3,52}
};

bool CheckKey(int y, int x) //플레이어 위치
{
    char buffer[64] = "";
    char str[100];
    sprintf_s(buffer, "%d, %d\n", y, x);
    OutputDebugStringA(buffer);

    for (int k = 0; k < 13; k++) {
        sprintf_s(str, "[i=%d] -> x%d = %d / y%d = %d\r\n", k, key_position[k][0], y, key_position[k][1], x);
        OutputDebugStringA(str);
        if (key_position[k][0] == y && key_position[k][1] == x) {
            key_position[k][0] = 399;
            key_position[k][1] = 399;
            easyMap[y][x] = 0; //화면을 별을 제거
            hardMap[y][x] = 0;
            render::setColor(render::black, render::black);
            render::ScreenDraw(x, y, " ");
            return true;
        }       
    }
    return false;
}

int firewall_position[5][2] = {
    {8, 58},
    {8, 59},
    {2, 31},
    {2, 32},
    {9, 9}
};

bool CheckFireWall(int y, int x)
{
    char buffer[64] = "";
    char str1[100];
    sprintf_s(buffer, "%d, %d\n", y, x);
    OutputDebugStringA(buffer);

    for (int k = 0; k < 5; k++) {
        sprintf_s(str1, "[i=%d] -> x%d = %d / y%d = %d\r\n", k, firewall_position[k][0], y, firewall_position[k][1], x);
        OutputDebugStringA(str1);
        if (firewall_position[k][0] == y && firewall_position[k][1] == x) {
            firewall_position[k][0] = 399;
            firewall_position[k][1] = 399;
            easyMap[y][x] = 0; //화면을 벽을 제거
            render::setColor(render::black, render::black);
            render::ScreenDraw(x, y, " ");
            return true;
        }
    }
    return false;
}

int keyControl()
{
    char temp = _getch();

    if (temp == 'w' || temp == 'W')
    {
        return global::input::USER_CMD_UP;
    }
    
    else if (temp == 's' || temp == 'S')
    {
        return global::input::USER_CMD_DOWN;
    }

    else if (temp == ' ')
    {
        return global::input::USER_CMD_SPACE;
    }

    return 0;
}
   
int infoDraw()
{
    global::input::Gotoxy(1, 1);
    printf("[조작법]\n\n");
    printf("\n\n\n");

    
    printf("                          [이동]\n                          W, A, S, D\n\n");
    printf("                          [선택]\n                          스페이스바로 메뉴를 선택할 수 있습니다.\n                          스페이스바를 누르면 이전 화면으로 이동합니다.\n\n");
    
    printf("                          [게임 방법]\n                          플레이어(파란색)가 키(노란색)을 전부 획득한 후, \n                          미로의 도착지(초록색)에 도달하면 게임 클리어입니다.\n\n");
    printf("                          [주의 사항]\n                          창 크기를 조절하지 말아주세요. \n                          그래픽이 깨질 수 있습니다.\n\n");
    printf("                          [개발자]\n                          플밍2반 김민정\n\n");

    while (1)
    {
        int n = keyControl();

        if (n == global::input::USER_CMD_SPACE)
        {
            system("cls");
            return -1;  
        }
    }
}

int menuDraw()
{    
    int x = 37;
    int y = 15;

    global::input::Gotoxy(x - 2, y); // -2한 이유는 > 를 출력해야하기 때문이다.
    printf("▶게임 시작");

    global::input::Gotoxy(x, y + 1);
    printf("게임 정보");
    
    global::input::Gotoxy(x, y + 2);
    printf("게임 종료");

    while (1)
    {
        int n = keyControl();

        switch (n)
        {
            case global::input::USER_CMD_UP:
            {
                if (y > 15)
                {
                    global::input::Gotoxy(x - 2, y);
                    printf("  ");
                     
                    global::input::Gotoxy(x - 2, --y);
                    printf("▶");

                    Sleep(150);
                }
            }
            break;

            case global::input::USER_CMD_DOWN:
            {
                if (y < 17)
                {
                    global::input::Gotoxy(x - 2, y);
                    printf("  ");

                    global::input::Gotoxy(x - 2, ++y);
                    printf("▶");

                    Sleep(150);
                }
            }
            break;

            case global::input::USER_CMD_SPACE:
            {
                system("cls");
                return y - 15;
            }
            break;
        
        }
    }
}
   
void titleDraw()
{
    int h = 0, w = 0;
    global::input::Gotoxy(h, w);

    int title[5][92] =
    {
        {1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1, 1, 1, 1, 0, 0, 0, 1, 1, 1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1},
        {1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1, 1, 0, 1, 1, 0, 1, 1, 0, 1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0},
        {1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1, 1, 0, 0, 0, 1, 0, 0, 0, 1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1, 1, 0, 0, 0, 0, 0, 0, 0, 1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},
        {1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1, 1, 0, 0, 0, 0, 0, 0, 0, 1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1}
    };

    //시작화면 출력
    printf("\n\n\n\n");

    for (int h = 0; h < 5; h++)
    {
        for (int w = 0; w < 92; w++)
        {
            if (title[h][w] == 1)
            {
                global::setColor(global::color::white, global::color::white);
                printf("%d", title[h][w]);
            }
            else if (title[h][w] == 0)
            {
                global::setColor(global::color::lightgreen, global::color::lightgreen);
                printf("%d", title[h][w]);
            }
        }
        printf("\n");
    }
    global::setColor(global::color::white, global::color::black);
}

int maplistDraw()
{
    int x = 37;
    int y = 8;
    
    //printf("\n\n");

     global::input::Gotoxy(1, 1);
    printf("[맵 선택]");

    global::input::Gotoxy(x - 2, y);
    printf("▶쉬움");
    global::input::Gotoxy(x, y + 1);
    printf("어려움");
    global::input::Gotoxy(x, y + 2);
    printf("뒤로");

    while(1)
    {
        int n = keyControl();

        switch (n)
        {
            case global::input::USER_CMD_UP:
            {
                if (y > 8)
                {
                    global::input::Gotoxy(x - 2, y);
                    printf("  ");

                    global::input::Gotoxy(x - 2, --y);
                    printf("▶");

                    Sleep(150);
                }
            }
            break;

            case global::input::USER_CMD_DOWN:
            {
                if (y < 10)
                {
                    global::input::Gotoxy(x - 2, y);
                    printf("  ");
                     
                    global::input::Gotoxy(x - 2, ++y);
                    printf("▶");

                    Sleep(150);
                }
            }
            break;
            
            case global::input::USER_CMD_SPACE:
            {
                system("cls");

                if (y-8 != 2)
                {
                    render::SetBackScreen();
                }
                else
                {
                    render::SetStdScreen();
                }
                return y - 8;
            }
            break;
        }
    }
}

void gameClearDraw()
{
    /*int y = 10, x= 0;
    global::input::Gotoxy(x, y);*/

    int gameClear[5][92] =
    {
        {0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,0},
        {1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0},
        {1,1,0,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0},
        {1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0},
        {0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0}
    };

    for (int h = 0; h < 5; h++)
    {
        for (int w = 0; w < 92; w++)
        {
            if (gameClear[h][w] == 1)
            {
                global::input::Gotoxy(w, h+3);
                global::setColor(global::color::white, global::color::white);
                printf("%d", gameClear[h][w]);
                //render::ScreenDraw(w, h, "0");
            }
            else if (gameClear[h][w] == 0)
            {
                global::input::Gotoxy(w, h+3);
                global::setColor(global::color::lightgreen, global::color::lightgreen);
                printf("%d", gameClear[h][w]);
                //render::ScreenDraw(w, h, "0");
            }
        }
        //global::input::Gotoxy(h, w);
        printf("\n");
    }
    global::setColor(global::color::white, global::color::black);

}

void drawMap()
{
    //int x = 10;
    //int y = 10;


    for (int h = 0; h < 15; h++) //세로 길이까지
    {
        for (int w = 0; w < 75; w++) //가로 길이까지
        {
            int temp = tempMap[h][w]; //임시 저장한 맵 데이터[높이][폭]
            if (temp == 0) // 빈 공간
            {
                //render::GotoXY(x, y);
                render::setColor(render::black, render::black);
                render::ScreenDraw(w, h, " ");
            }
            else if (temp == 1) // 벽
            {
                //render::GotoXY(x, y);
                render::setColor(render::white, render::white);
                render::ScreenDraw(w, h, "#");
            }
            else if (temp == 2) // 최종 목적지: 게임 종료
            {
                //render::GotoXY(x, y);
                render::setColor(render::lightgreen, render::lightgreen);
                render::ScreenDraw(w, h, "0");
            }
            else if (temp == 3) // key item
            {
                //render::GotoXY(x, y);
                render::setColor(render::yellow, render::black);
                render::ScreenDraw(w, h, "*");
            }
            else if (temp == 4) // 잠긴 부분
            {
                //render::GotoXY(x, y);
                render::setColor(render::red, render::black);
                render::ScreenDraw(w, h, "+");
            }
            
        }
        //y++;
        printf("\n");
    }
    render::setColor(render::white, render::black);
}

void gLoop(int mapCode)
{
    
    int key = 0; //열쇠 갯수 저장변수

    int playing = 1; //1이면 게임중, 0이면 게임 종료

    //mapNumber가 0이면 쉬운 맵, 1이면 어려운 맵
    //아래와 같은 방식으로 맵을 추가하면 됨
    if (mapCode == 0)
    {
       memcpy(tempMap, easyMap, sizeof(tempMap));
    }
    else if (mapCode == 1)
    {  
        memcpy(tempMap, hardMap, sizeof(tempMap));
    }

    drawMap();
}

void playerMove(int* x, int* y, int _x, int _y, int* key, int* playing)
{
    //플레이어 좌표를 조작할 함수
    //원래 좌표 (x,y)에서 증감할 좌표(_x, _y)

    char mapObject = tempMap[*y + _y][*x + _x];

    global::setColor(global::color::white, global::color::black); // 색 기본값

    if (mapObject == '0')
    {
        global::input::Gotoxy(*x, *y);
        printf(" "); // 지우기

        global::setColor(global::color::cyan, global::color::black); // 새로운 색 설정
        global::input::Gotoxy(*x + _x, *y + _y); // 증감한 위치로 이동 후, 플레이어 출력
        // printf("@");

        *x += _x; // 실제 좌표값으로 반영
        *y += _y; // 실제 좌표값으로 반영
    }

    else if (mapObject == '1')
    {
        //1은 벽이기 때문에 아무런 동작을 하지 않으면 됨  
    }

    else if (mapObject == 'k') //이동할 위치에 열쇠가 있으면 획득
    {
        *key += 1; // 열쇠갯수 1 증가
        tempMap[*y + _y][*x + _x] = '0'; // 획득하였으면 기존에 있던 k를 0으로 설정
        global::input::Gotoxy(*x + _x, *y + _y); //열쇠가 있는 위치를 지움
        printf(" ");
    }

    else if (mapObject == 'l')
    {
        if (*key > 0)
        {
            *key -= 1;
            tempMap[*y + _y][*x + _x] = '0'; // 획득하였으면 기존에 있던 l을 0으로 설정
            global::setColor(global::color::white, global::color::black);
            global::input::Gotoxy(*x + _x, *y + _y);
            printf(" ");
        }
    }
    else if (mapObject == 'q')
    {
        *playing = 0;
    }
}

void drawUI(int* x, int* y, int* key)
{
    global::setColor(global::color::white, global::color::black);
    global::input::Gotoxy(3, 16);
    printf("위치 : %02d, %02d", *x, *y);

    global::setColor(global::color::yellow, global::color::black);
    global::input::Gotoxy(34, 16);
    printf("열쇠 : %d개", *key);
}