#include "DropDown.h"

#include <cstring>

#include "../TextFunction/TextFunction.h"

DropDown::DropDown(Node<std::string>* itemList, Vector2 pos, float width)
    : dropDownBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}) {
    for (; itemList; itemList = itemList->next) {
        items += itemList->data;

        if (itemList->next) {
            items += ';';
        }
    }
}

DropDown::DropDown(Node<Semester>* itemList, Vector2 pos, float width)
    : dropDownBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}) {
    for (; itemList; itemList = itemList->next) {
        items += itemList->data.number;

        if (itemList->next) {
            items += ';';
        }
    }
}

DropDown::DropDown(Node<Course>* itemList, Vector2 pos, float width)
    : dropDownBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}) {
    for (; itemList; itemList = itemList->next) {
        items += itemList->data.id + '-' + itemList->data.className;

        if (itemList->next) {
            items += ';';
        }
    }
}

DropDown::DropDown(const std::string& itemList, Vector2 pos, float width)
    : items(itemList), dropDownBox({pos.x, pos.y, width, DEFAULT_ITEM_HEIGHT}) {}

void DropDown::drawDropDown(
    const char* label, char*& selectedItem, int& activeItemIndex, bool& editMode,
    Color labelColor
) {
    drawDefaultText(
        textFont, label,
        {dropDownBox.x, dropDownBox.y - DEFAULT_TEXT_SIZE - DEFAULT_TEXT_MARGIN.y},
        labelColor
    );

    if (GuiDropdownBox(dropDownBox, items.c_str(), &activeItemIndex, editMode)) {
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
