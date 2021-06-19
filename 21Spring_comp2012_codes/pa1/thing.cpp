#include "thing.h"
//do NOT include anything else, write your code below

Thing::Thing(ThingType type){
    this->type = type;
}

bool Thing::isWeapon() const{
    if (type == MACE || type == DAGGER || type == SWORD) return true;
    else return false;
}

bool Thing::isMonster() const{
    if (type == SKELETON || type == VAMPIRE || type == DRAGON) return true;
    else return false;
}

ThingType Thing::getType() const{
    return type;
}

void Thing::setType(ThingType type){
    this->type = type;
}

char Thing::getSymbol() const{
    switch(type){
        case MACE: return 'm'; break;
        case DAGGER: return 'd'; break;
        case SWORD: return 's'; break;
        case SKELETON: return 'K'; break;
        case VAMPIRE: return 'V'; break;
        case DRAGON: return 'D'; break;
        default: return 'x'; break;
    }
}