#ifndef __GAME_H__
#define __GAME_H__

#include "thing.h"
#include "cell.h"

#include <iostream>
//we don't include "using namespace std;" in this header file
//we just want to avoid having that in all files that include this header
//as a result, we will need to write "std::cout" instead of "cout" in the code below
//for details, you may read our self-study notes on namespace: https://course.cse.ust.hk/comp2012/notes/h.namespace.pdf

class Game
{
public:
    Game(int width, int height);
    Game(const Game& another);
    ~Game();
    bool addThing(int x, int y, ThingType type, int quantity=1);
    bool removeThing(int x, int y, ThingType type, int quantity=1);
    bool moveHero(char direction);
    bool isHeroAlive() const;
    bool isAllMonstersGone() const;
    int getMonsterCount() const;
    int getHeroX() const;
    int getHeroY() const;
    
    void print() const
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if(heroStatus.alive && i == heroStatus.y && j == heroStatus.x)
                    std::cout << "H"; //we didn't use "using namespace std;" so we have to be specific
                else
                    cells[i][j].printSymbol();
                std::cout << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Hero status: x=" << heroStatus.x 
                    << " y=" << heroStatus.y 
                    << " #mace=" << heroStatus.maceCount 
                    << " #dagger=" << heroStatus.daggerCount 
                    << " #sword=" << heroStatus.swordCount 
                    << std::endl; //note: heroStatus is a Game::HeroStatus struct object
                    //you can find the definition of HeroStatus under the "private" section of the Game class below
        int monsterCount = getMonsterCount();
        if (monsterCount == 0)
            std::cout << "There is no monster left! Hurray!" << std::endl;
        else if (monsterCount == 1)
            std::cout << "There is still one more monster left!" << std::endl;
        else
            std::cout << "There are " << monsterCount << " monsters left in the world!" << std::endl;
        std::cout << std::endl;
    }

    void printThings(int x, int y) const
    {
        cells[y][x].printThings();
    }

private:
    struct HeroStatus
    {
        int x = 0;
        int y = 0;
        bool alive = true;
        int maceCount = 0;
        int daggerCount = 0;
        int swordCount = 0;
    } heroStatus;

    int width;
    int height;
    Cell** cells;
};

#endif // __GAME_H__