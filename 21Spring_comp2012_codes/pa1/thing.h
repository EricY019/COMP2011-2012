#ifndef __THING_H__
#define __THING_H__

enum ThingType
{
    MACE,
    DAGGER,
    SWORD,
    SKELETON,
    VAMPIRE,
    DRAGON
};

class Thing 
{
public:
    Thing(ThingType type=MACE);
    bool isWeapon() const; 
    bool isMonster() const;
    ThingType getType() const;
    void setType(ThingType type);
    char getSymbol() const;

private:
    ThingType type;
};

#endif // __THING_H__