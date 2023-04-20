#ifndef DROP_DOWN_H
#define DROP_DOWN_H

#include <string>

#include "../../Struct/Course.h"
#include "../../Struct/LinkedList.h"
#include "../../Struct/Semester.h"
#include "../GlobalStyle.h"

class DropDown {
   private:
    Rectangle dropDownBox;
    std::string items;

   public:
    DropDown(Node<std::string>* itemList, Vector2 pos, float width);
    DropDown(Node<Semester>* itemList, Vector2 pos, float width);
    DropDown(Node<Course>* itemList, Vector2 pos, float width);
    DropDown(const std::string& itemList, Vector2 pos, float width);
    void drawDropDown(
        const char* label, char*& selectedItem, int& activeItemIndex, bool& editMode,
        Color labelColor = NORMAL_TEXT_COLOR
    );
};

#endif
