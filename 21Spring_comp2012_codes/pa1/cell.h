#ifndef __CELL_H__
#define __CELL_H__

#include "thing.h"

#include <iostream>
//we don't include "using namespace std;" in this header file
//we just want to avoid having that in all files that include this header
//as a result, we will need to write "std::cout" instead of "cout" in the code below
//for details, you may read our self-study notes on namespace: https://course.cse.ust.hk/comp2012/notes/h.namespace.pdf

class Cell 
{
public:
    Cell();
    ~Cell();
    bool addThing(ThingType type, int quantity);
    bool removeThing(ThingType type, int quantity);
    bool removeAnythingFromTheFront(int quantity);
    void removeEverything();
    const Thing& getThing(int index) const;
    int getThingCount() const;
    int getThingCount(ThingType type) const;
    int getThingTypeCount() const;
    bool hasWeapons() const;
    bool hasMonsters() const;
    bool hasType(ThingType type) const;

    void printSymbol() const
    {
        int count = getThingTypeCount(); //note that we count the types of things, not the number of things
        if (count == 0) //output '.' for nothing being in the cell 
            std::cout << '.'; //we didn't use "using namespace std;" so we have to be specific
        else
        {
            if (count == 1) //if there is only one type of things
            {
                std::cout << things[0].getSymbol(); //thing[0].getSymbol() will give us the character which represents that one thing
            }
            else //otherwise, output either '1', '2', or '3'
                std::cout << static_cast<char>(('0' + count)); 
        }
    }
    void printThings() const
    {
        std::cout << "["; 
        for(int i=0; i<thingCount; i++)
        {
            std::cout << things[i].getSymbol();
            if (i != thingCount-1) 
                std::cout << ",";
        }
        std::cout << "]" << std::endl;
    }
    
private:
    Thing* things;
    int thingCount;
};

#endif // __CELL_H__