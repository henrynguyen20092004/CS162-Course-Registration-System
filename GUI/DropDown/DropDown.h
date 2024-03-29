#ifndef DROP_DOWN_H
#define DROP_DOWN_H

#include "../../Struct/Course.h"
#include "../../Struct/LinkedList.h"
#include "../../Struct/Semester.h"
#include "../../Struct/Student.h"
#include "../GlobalStyle.h"

class DropDown {
   private:
    const char* label = nullptr;

   public:
    Rectangle dropDownBox{0.0f, 0.0f, 0.0f, 0.0f};
    std::string items;
    int activeItemIndex = -1;
    bool editMode = false;
    DropDown();
    DropDown(const char* label, Node<std::string>* itemList, Vector2 pos, float width);
    DropDown(const char* label, Node<Semester>* itemList, Vector2 pos, float width);
    DropDown(const char* label, Node<Course>* itemList, Vector2 pos, float width);
    DropDown(const char* label, Node<Student>* itemList, Vector2 pos, float width);
    DropDown(const char* label, const char* itemList, Vector2 pos, float width);
    bool drawDropDown(
        char*& selectedItem, float scrollY = 0.0f, Color labelColor = NORMAL_TEXT_COLOR
    );
};

#endif
