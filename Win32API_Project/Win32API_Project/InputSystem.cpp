//! InputSystem.cpp

#include <windows.h>
#include <cassert>
#include "InputSystem.h"
#include <conio.h>


namespace global
{
	namespace input
	{
		bool inputKeyTable[MAX_KEY]; // 정의된 키 값을 처리 합니다.

		// Helper Functions ..
		void Set(const int keyIdx, bool bOn)
		{
			assert(keyIdx >= 0 && keyIdx < MAX_KEY); // 방어 코드를 작성하는 것에 익숙해져야 합니다.  배열을 다룰 때는 인덱스를 조심해야 합니다!!

			inputKeyTable[keyIdx] = bOn;			// bool 타입을 활용 합시다.
		}

		void Gotoxy(int x, int y)
		{
			//gotoxy 는 커서 위치 이동 함수입니다.
			HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); //콘솔 핸들 가져오기 
			COORD pos;
			pos.X = x;
			pos.Y = y;
			SetConsoleCursorPosition(consoleHandle, pos);
		}

		bool IsEscapeCmdOn()
		{
			return inputKeyTable[ESCAPE_KEY_INDEX];
		}

		bool IsLeftCmdOn()
		{
			return inputKeyTable[USER_CMD_LEFT];
		}

		bool IsRightCmdOn()
		{
			return inputKeyTable[USER_CMD_RIGHT];
		}

		bool IsUpCmdOn()
		{
			return inputKeyTable[USER_CMD_UP];
		}

		bool IsDownCmdOn()
		{
			return inputKeyTable[USER_CMD_DOWN];
		}

		bool IsSpaceCmdOn()
		{
			return inputKeyTable[USER_CMD_SPACE];
		}


		// 입력 키값에 대해 알아 봅시다. 블러킹과 넌블러킹에 대해서만 이해하고 가기로 합니다!!
		// * 비트 연산에 대해 학습합니다. & 와 && 은 달라요. 
		// &, * 연산자가 맥락에 따라 다르게 해석되는 것에 주의 해야 합니다. 
		void UpdateInput()
		{
			if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			{
				global::input::Set(ESCAPE_KEY_INDEX, true);
			}

			if (GetAsyncKeyState('A') & 0x8000) //왼쪽 'A'
			{
				global::input::Set(USER_CMD_LEFT, true);
			}

			if (GetAsyncKeyState('D') & 0x8000) //오른쪽 'D'
			{
				global::input::Set(USER_CMD_RIGHT, true);
			}

			if (GetAsyncKeyState('W') & 0x8000) //위쪽 'W'
			{
				global::input::Set(USER_CMD_UP, true);
			}

			if (GetAsyncKeyState('S') & 0x8000) //아래쪽 'S'
			{
				global::input::Set(USER_CMD_DOWN, true);
			}

			if (GetAsyncKeyState(VK_SPACE) & 0x8000) //스페이스바
			{
				global::input::Set(USER_CMD_DOWN, true);
			}
		}

	};
};
