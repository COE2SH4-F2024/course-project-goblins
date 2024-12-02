#include "objPosArrayList.h"

#include <iostream>

#include "objPos.h"
// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

objPosArrayList::objPosArrayList() {
    // std::cout << "objPosArrayList const: ";
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos[arrayCapacity];
    // std::cout << "Success" << std::endl;
}

objPosArrayList::~objPosArrayList() {
    delete[] aList;
}

int objPosArrayList::getSize() const {
    return listSize;
}

void objPosArrayList::insertHead(objPos obj) {
    if (listSize >= arrayCapacity) return;
    for (int i = listSize; i > 0; --i) {
        aList[i] = aList[i - 1];
    }
    aList[0] = obj;
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
    if (index >= 0 && index < listSize) {
        return aList[index];
    }
}

void objPosArrayList::removeAtIndex(int index) {
    if (index >= 0 && index < listSize) {
        for (int i = index; i < listSize - 1; ++i) {
            aList[i] = aList[i + 1];
        }
        --listSize;
    }
}