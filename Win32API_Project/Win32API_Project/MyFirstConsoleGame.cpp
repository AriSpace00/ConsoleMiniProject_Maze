#include <stdio.h>
#include <windows.h>
#include <random>

#include "InputSystem.h" // 기능 별로 모듈화를 한다는 개념에 대해 생각해 봅시다!
#include "RenderSystem.h"
#include "LevelSystem.h"


namespace global
{
    namespace time
    {
        ULONGLONG previousTime;
        ULONGLONG currentTime;
        ULONGLONG deltaTime;

        int updateCount;
        int fixedUpdateCount;

        void InitTime()
        {
            currentTime = previousTime = GetTickCount64();
        }

        void UpdateTime()
        {
            previousTime = currentTime;
            currentTime = GetTickCount64();

            deltaTime = currentTime - previousTime;
        }

        ULONGLONG GetDeltaTime()
        {
            return deltaTime;
        }
    };

    COORD prePlayerPos; // 이전 플레이어 위치
    COORD curPlayerPos; // 현재 플레이어 위치

    SMALL_RECT playerMovableRect = { 5, 5, 10, 10 }; // @SEE StartGame()

    const int playerMoveSpeed = 200;

    int KeyCount = 0;
    //int FireWallCount = 0;
};

int GameNumber = -1;
int LevelIndex = -1;

void Clamp(short& n, short min, short max) // 레퍼런스 타입에 대해 배워 봅시다.
{
    if (n < min) n = min;
    if (n > max) n = max;
}

void DrawPlayer()
{
    render::setColor(render::cyan, render::cyan);
    render::ScreenDraw(global::curPlayerPos.X, global::curPlayerPos.Y, '@');
}

bool bPlayerSuccess;
void CheckPlayerSuccess()
{
    bPlayerSuccess = CheckGoal(global::curPlayerPos.Y, global::curPlayerPos.X);
}

bool bPlayerGetKey;
void CheckPlayerGetKey()
{
    bPlayerGetKey = CheckKey(global::curPlayerPos.Y, global::curPlayerPos.X);
}

bool bPlayerFireWall;
void CheckPlayerFireWall()
{
    bPlayerFireWall = CheckFireWall(global::curPlayerPos.Y, global::curPlayerPos.X);  
}

void UpdatePlayerPosition()
{
    if (CheckGoal(global::curPlayerPos.Y, global::curPlayerPos.X) == false || global::KeyCount < 5)
    {
        if (global::input::IsEscapeCmdOn())
        {
            global::input::Set(global::input::ESCAPE_KEY_INDEX, false);

            //TODO: 게임 화면 전환이나 종료 처리

            return; // 다른 키 입력을 신경 쓸 필요가 없어요.
        }

        if (global::input::IsSpaceCmdOn())
        {
            global::input::Set(global::input::ESCAPE_KEY_INDEX, false);

            global::curPlayerPos.Y = 1;
            global::curPlayerPos.X = 1;

            return; // 다른 키 입력을 신경 쓸 필요가 없어요.
        }

        if (global::input::IsLeftCmdOn())
        {
            global::input::Set(global::input::USER_CMD_LEFT, false);

            if (CheckWall(global::curPlayerPos.Y, global::curPlayerPos.X - 1) == false)
            {
                global::curPlayerPos.X--;
            }

            Clamp(global::curPlayerPos.X, global::playerMovableRect.Left, global::playerMovableRect.Right);
        }

        if (global::input::IsRightCmdOn())
        {
            global::input::Set(global::input::USER_CMD_RIGHT, false);

            if (CheckWall(global::curPlayerPos.Y, global::curPlayerPos.X + 1) == false)
            {
                global::curPlayerPos.X++;
            }

            Clamp(global::curPlayerPos.X, global::playerMovableRect.Left, global::playerMovableRect.Right);
        }

        if (global::input::IsUpCmdOn())
        {
            global::input::Set(global::input::USER_CMD_UP, false);

            if (CheckWall(global::curPlayerPos.Y - 1, global::curPlayerPos.X) == false)
            {
                global::curPlayerPos.Y--;
            }

            Clamp(global::curPlayerPos.Y, global::playerMovableRect.Top, global::playerMovableRect.Bottom);
        }

        if (global::input::IsDownCmdOn())
        {
            global::input::Set(global::input::USER_CMD_DOWN, false);


            if (CheckWall(global::curPlayerPos.Y + 1, global::curPlayerPos.X) == false)
            {
                global::curPlayerPos.Y++;
            }
            Clamp(global::curPlayerPos.Y, global::playerMovableRect.Top, global::playerMovableRect.Bottom);
        }
    }

    if ((global::curPlayerPos.X == global::prePlayerPos.X) && (global::curPlayerPos.Y == global::prePlayerPos.Y))
    {
        // 안 움직임
    }
    else
    {
        global::prePlayerPos = global::curPlayerPos;
        
        CheckPlayerSuccess();
        
        CheckPlayerGetKey();
        /*if (global::KeyCount > 0)
        {
            CheckPlayerFireWall();
        } */       
        // 움직임
    }
}
void UpdatePlayer()
{
    // 키 입력과 화면 출력과 게임 로직 갱신을 분리해서 생각해 봅시다.
    static ULONGLONG elapsedTime;

    elapsedTime += global::time::GetDeltaTime();

    while (elapsedTime >= global::playerMoveSpeed)
    {
        UpdatePlayerPosition();

        elapsedTime -= global::playerMoveSpeed;
    }
}

void PrintPlayerKey()
{
    char buffer[64] = "";
    sprintf_s(buffer, "Key: %d", global::KeyCount);
    render::setColor(render::white, render::black);
    render::ScreenDraw4(0, 0, buffer);
}

void StartGame()
{
    render::InitScreen();

    global::playerMovableRect = render::GetPlayerMovableRect();

    global::curPlayerPos.X = 1;
    global::curPlayerPos.Y = 1;

    global::prePlayerPos = global::curPlayerPos;

    DrawPlayer();
}

void EndGame()
{
    render::ScreenRelease();
}

void ProcessInput()
{
    global::input::UpdateInput();
}

void PrintCountsPerSecond();
void PrintPlayerPostion();

bool GameClearTest = true;

void Render(int a)
{
    render::ScreenClear();

    PrintCountsPerSecond();

    PrintPlayerPostion();
    PrintPlayerKey();

    gLoop(a);

    DrawPlayer();

    render::ScreenFlipping();
}

bool IsGameRun()
{
    return true; 

}

void FixeUpdate()
{
    static ULONGLONG elapsedTime;

    elapsedTime += global::time::GetDeltaTime();

    while (elapsedTime >= 1000) //1초
    {
        global::time::fixedUpdateCount += 1;

        elapsedTime -= 1000;
    }
}

void Update()
{
    global::time::updateCount += 1;

    if (bPlayerGetKey)
    {
        bPlayerGetKey = false;
        ++global::KeyCount;
    }

    if ((global::KeyCount >= 5) && bPlayerSuccess)
    {
        bPlayerSuccess = false;

        GameNumber = -1;

        render::ScreenClear();
        render::ScreenFlipping();
        render::SetStdScreen();

        gameClearDraw();

        Sleep(2000);

        GameNumber = 2;
    }
    else
    {
        UpdatePlayer();
    }

    /*if (bPlayerFireWall)
    {
        bPlayerFireWall = false;
        --global::KeyCount;
        ++global::FireWallCount;
    }*/

    
}

void PrintPlayerPostion()
{
    char buffer[64] = "";
    sprintf_s(buffer, "Player Position (%d, %d)", global::curPlayerPos.X, global::curPlayerPos.Y);
    render::setColor(render::white, render::black);
    render::ScreenDraw3(0, 0, buffer);
}

void PrintCountsPerSecond()
{
    static ULONGLONG elapsedTime;

    elapsedTime += global::time::GetDeltaTime();
    if (elapsedTime >= 1000)
    {
        char buffer[64] = "";

        sprintf_s(buffer, "updateCount : %d fixedUpdateCount : %d  delta %2d\n",
            global::time::updateCount, global::time::fixedUpdateCount, global::time::GetDeltaTime());

        render::ScreenDraw(0, 0, buffer);

        elapsedTime = 0;
        global::time::updateCount = 0;
        global::time::fixedUpdateCount = 0;
    }
}

int main()
{
    render::InitScreen();
    global::time::InitTime();
    Update();
    StartGame();

    bool menu = false;
    bool isDrawMenu = false;
    bool as = false;

    while (IsGameRun())
    {
        global::time::UpdateTime();
        ProcessInput();
        FixeUpdate();
        Update();

        if (isDrawMenu == false)
        {
            if (GameNumber == -1)
            {
                titleDraw();
                GameNumber = menuDraw();
                menu = true;
            }
            else if (GameNumber == 0 && LevelIndex == -1)
            { 
                int Select = maplistDraw();
                if (Select == 0)
                    LevelIndex = 0;
                if (Select == 1)
                    LevelIndex = 1;
                if (Select == 2)
                    GameNumber = -1;
            }
            else if (GameNumber == 0 && LevelIndex == 0)
            {
                Render(LevelIndex);
            }
            else if (GameNumber == 0 && LevelIndex == 1)
            {
                Render(LevelIndex);
            }
            else if (GameNumber == 1)
            {
                GameNumber = infoDraw();
                
            }
            else if (GameNumber == 2)
            {
                break;
            }
            //Sleep(1);
            //isDrawMenu = true;  // 게임을 시작하면 이걸 실행. 
        }
    }

    EndGame();

    return 0;
}