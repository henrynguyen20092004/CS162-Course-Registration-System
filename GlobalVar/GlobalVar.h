#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H

#include <raylib.h>

#include "../GUI/Command/Command.h"
#include "../Struct/Data.h"

struct GlobalVar {
    static std::string renderArgs;
    static Command currentCommand, previousCommand;
    static Font titleFont, textFont;
    static Texture2D defaultAvatar, fullScreenLogo, groupInfo;
    static User currentUser;
    static Semester currentSemester;
    static Data allData;
};

#endif
