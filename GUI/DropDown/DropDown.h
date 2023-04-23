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
    const char* label;

   public:
    int activeItemIndex = -1;
    bool editMode = false;
    DropDown();
    DropDown(const char* label, Node<std::string>* itemList, Vector2 pos, float width);
    DropDown(const char* label, Node<Semester>* itemList, Vector2 pos, float width);
    DropDown(const char* label, Node<Course>* itemList, Vector2 pos, float width);
    DropDown(const char* label, const char* itemList, Vector2 pos, float width);
    void drawDropDown(char*& selectedItem, Color labelColor = NORMAL_TEXT_COLOR);
};

#endif
