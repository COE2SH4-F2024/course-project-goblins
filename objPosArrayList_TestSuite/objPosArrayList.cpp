#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction,
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList() {
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos[arrayCapacity];
}

objPosArrayList::~objPosArrayList() {
    delete[] aList;
}

int objPosArrayList::getSize() const {
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos) {
    if (listSize >= arrayCapacity) return;
    for (int i = listSize; i > 0; --i) {
        aList[i] = aList[i - 1];
    }
    aList[0] = thisPos;
    ++listSize;
}

void objPosArrayList::insertTail(objPos thisPos) {
    if (listSize < arrayCapacity) {
        aList[listSize++] = thisPos;
    }
}

void objPosArrayList::removeHead() {
    if (listSize > 0) {
        for (int i = 0; i < listSize - 1; ++i) {
            aList[i] = aList[i + 1];
        }
        --listSize;
    }
}

void objPosArrayList::removeTail() {
    if (listSize > 0) {
        --listSize;
    }
}

objPos objPosArrayList::getHeadElement() const {
    return aList[0];
}

objPos objPosArrayList::getTailElement() const {
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const {
    return (index >= 0 && index < listSize) ? aList[index] : objPos();
}