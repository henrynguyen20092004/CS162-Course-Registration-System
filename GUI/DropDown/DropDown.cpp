#include "DropDown.h"

#include <cstring>

#include "../TextFunction/TextFunction.h"

DropDown::DropDown() : dropDownBox({0.0f, 0.0f, 0.0f, 0.0f}), label(nullptr) {}

DropDown::DropDown(
    const char* label, Node<std::string>* itemList, Vector2 pos, float width
)
    : dropDownBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}), label(label) {
    for (; itemList; itemList = itemList->next) {
        items += itemList->data;

        if (itemList->next) {
            items += ';';
        }
    }
}

DropDown::DropDown(const char* label, Node<Semester>* itemList, Vector2 pos, float width)
    : dropDownBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}), label(label) {
    for (; itemList; itemList = itemList->next) {
        items += "Semester " + std::to_string(itemList->data.number) + ", " +
                 itemList->data.schoolYearName;

        if (itemList->next) {
            items += ';';
        }
    }
}

DropDown::DropDown(const char* label, Node<Course>* itemList, Vector2 pos, float width)
    : dropDownBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}), label(label) {
    for (; itemList; itemList = itemList->next) {
        items += itemList->data.id + '-' + itemList->data.className;

        if (itemList->next) {
            items += ';';
        }
    }
}

DropDown::DropDown(const char* label, const char* itemList, Vector2 pos, float width)
    : items(itemList),
      dropDownBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}),
      label(label) {}

void DropDown::drawDropDown(char*& selectedItem, float scrollY, Color labelColor) {
    drawDefaultText(
        textFont, label,
        {dropDownBox.x,
         dropDownBox.y - DEFAULT_TEXT_SIZE - DEFAULT_TEXT_MARGIN.y + scrollY},
        labelColor
    );
    Rectangle dropDownBoxWithScroll = dropDownBox;
    dropDownBoxWithScroll.y += scrollY;

    if (GuiDropdownBox(
            dropDownBoxWithScroll, items.c_str(), &activeItemIndex, editMode
        )) {
        editMode = !editMode;
        int itemsLength = items.size(), indexToGetSelectedItem = 0,
            currentStringIndex = 0;

        for (; indexToGetSelectedItem < itemsLength; ++indexToGetSelectedItem) {
            if (currentStringIndex == activeItemIndex) {
                std::string subFromStart = items.substr(indexToGetSelectedItem);
                int nextDelimiter = subFromStart.find(';');

                if (nextDelimiter == std::string::npos) {
                    nextDelimiter = subFromStart.size();
                }

                strcpy(selectedItem, subFromStart.substr(0, nextDelimiter).c_str());
                return;
            }

            if (items[indexToGetSelectedItem] == ';') {
                ++currentStringIndex;
            }
        }
    }
}
