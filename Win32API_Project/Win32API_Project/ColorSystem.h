#pragma once
#include "Main.h"
#define __COLOR_LIST_

namespace global
{
    namespace color
    {
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
    }

    void setColor(int, int);
}
