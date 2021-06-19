#include "cell.h"
#include <iostream>
using namespace std;
//do NOT include anything else, write your code below

Cell::Cell(){
    things = nullptr;
    thingCount = 0;
}

Cell::~Cell(){
    delete [] things;
    things = nullptr;
}

bool Cell::addThing(ThingType type, int quantity){
    if (quantity <= 0) return false;

    Thing* newthings = new Thing[thingCount + quantity];
    
    for (int i = 0; i < thingCount; i++){
        newthings[i].setType(things[i].getType());
    }
    for (int i = 0; i < quantity; i++){
        newthings[thingCount + i].setType(type);
    }

    delete [] things;
    things = newthings;
    newthings = nullptr;
    thingCount += quantity;
    return true;
}

bool Cell::removeThing(ThingType type, int quantity){
    if (quantity > getThingCount(type) || quantity <= 0) return false;
    if (thingCount == getThingCount(type) && quantity == getThingCount(type)){
        delete [] things;
        things = nullptr;
        thingCount = 0;
        return true;
    }

    Thing* newthings = new Thing[thingCount - quantity];
    int historyquantity = quantity;
    int index = 0;

    for (int i = 0; i < thingCount; i++){
        if (things[i].getType() != type || quantity == 0){
            newthings[index].setType(things[i].getType());
            index++;
        }
        else quantity--;
    }
    delete [] things;
    things = newthings;
    newthings = nullptr;
    thingCount -= historyquantity;
    return true;
}

bool Cell::removeAnythingFromTheFront(int quantity){
    if (quantity <= 0 || quantity > thingCount) return false; 
    if (quantity == thingCount){
        delete [] things;
        things = nullptr;
        thingCount = 0;
        return true;
    }

    Thing* newthings = new Thing[thingCount - quantity];

    for (int i = 0; i < thingCount - quantity; i++){
        newthings[i].setType(things[quantity + i].getType());
    }

    delete [] things;
    things = newthings;
    newthings = nullptr;
    thingCount -= quantity;
    return true;
}

void Cell::removeEverything(){
    delete [] things;
    things = nullptr;
    thingCount = 0;
}

const Thing& Cell::getThing(int index) const{
    return things[index];
}

int Cell::getThingCount() const{
    return thingCount;
}

int Cell::getThingCount(ThingType type) const{
    int typecount = 0;
    ThingType thingtype;

    for (int i = 0; i < thingCount; i++){
        thingtype = things[i].getType();
        if (thingtype == type) typecount++;  
    }
    return typecount;
}

int Cell::getThingTypeCount() const{
    if (thingCount == 0) return 0;

    int thingtypecount = 1;
    ThingType thisthingtype, historythingtype;

    for (int i = 0; i < thingCount; i++){
        thisthingtype = things[i].getType();
        for (int j = 0; j < i; j++){
            historythingtype = things[j].getType();
            if (thisthingtype == historythingtype) break;
            if (j == i - 1 && thisthingtype != historythingtype) thingtypecount++;
        }
    }
    return thingtypecount;
}

bool Cell::hasWeapons() const{
    for (int i = 0; i < thingCount; i++){
        if (things[i].isWeapon()) return true;
    }
    return false;
}

bool Cell::hasMonsters() const{
    for (int i = 0; i < thingCount; i++){
        if (things[i].isMonster()) return true;
    }
    return false;
}

bool Cell::hasType(ThingType type) const{
    if (getThingCount(type) > 0) return true;
    else return false;
}