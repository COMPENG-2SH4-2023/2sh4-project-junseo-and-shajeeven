#include "objPosArrayList.h"
#include "MacUILib.h"


//Array List Constructor
objPosArrayList::objPosArrayList()
{
    aList = new objPos [ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = 200;
}

//Array List Destructor
objPosArrayList::~objPosArrayList()
{
    delete [] aList;
}

//Getting Size of List
int objPosArrayList::getSize()
{
    return sizeList;
}

//Inserting an Element to the Head
void objPosArrayList::insertHead(objPos thisPos)
{
    if(sizeList == sizeArray)
    {
        return;
    }
    for (int i = sizeList; i > 0; i--)
    {
        aList[i] = aList[i-1];
    }
    aList[0] = thisPos;
    sizeList++;
}

//Inserting an Element to the Tail
void objPosArrayList::insertTail(objPos thisPos)
{
    if(sizeList == sizeArray)
    {
        return;
    }
    aList[sizeList] = thisPos;
    sizeList++;
}

//Removing the Element at the Head
void objPosArrayList::removeHead()
{
    if (sizeList == 0)
    {
        return;
    }

    for (int i = 0; i < sizeList; i++)
    {
        aList[i] = aList[i+1];
    }

    sizeList--;
}

//Removing the Element at the Tail
void objPosArrayList::removeTail()
{
    if (sizeList == 0)
    {
        return;
    }
    sizeList--;
}

//Obtaining x-y Coordinates and Symbol at the Head
void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0].x, aList[0].y, aList[0].symbol);
}

//Obtaining x-y Coordinates and Symbol at the Tail
void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList-1].x, aList[sizeList-1].y, aList[sizeList-1].symbol);
}

//Obtaining x-y Coordinates and Symbol at a Specific Index in the list
void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index].x, aList[index].y, aList[index].symbol);
}


