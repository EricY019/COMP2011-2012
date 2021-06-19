#include "game.h"
#include <iostream>
using namespace std;
//do NOT include anything else, write your code below

Game::Game(int width, int height){
    this->width = width;
    this->height = height;
    cells = new Cell*[height];

    for (int i = 0; i < height; i++){
        cells[i] = new Cell[width];
    }
}

Game::Game(const Game& another){
    heroStatus = another.heroStatus;
    height = another.height;
    width = another.width;
    cells = new Cell*[height];

    for (int i = 0; i < height; i++){//'i' - y value
        cells[i] = new Cell[width];

        for (int j = 0; j < width; j++){//'j' - x value
            for (int k = 0; k < another.cells[i][j].getThingCount(); k++){//'k' - thingcount
                addThing(j, i, another.cells[i][j].getThing(k).getType());
            }
        }    
    }
}

Game::~Game(){
    for (int i = 0; i < height; i++){
        delete [] cells[i];
        cells[i] = nullptr;
    }

    delete [] cells;
    cells = nullptr;
}

bool Game::addThing(int x, int y, ThingType type, int quantity){
    if (x < 0 || y < 0 || x > width - 1 || y > height - 1) return false;

    return cells[y][x].addThing(type, quantity);
}

bool Game::removeThing(int x, int y, ThingType type, int quantity){
    if (x < 0 || y < 0 || x > width - 1 || y > height - 1) return false;

    return cells[y][x].removeThing(type, quantity);
}

bool Game::moveHero(char direction){

    if (direction == 'w'){
        if (heroStatus.y == 0) return false;
        heroStatus.y--;
    }

    else if (direction == 'a'){
        if (heroStatus.x == 0) return false;
        heroStatus.x--;
    }

    else if (direction == 's'){
        if (heroStatus.y == height - 1) return false;
        heroStatus.y++;
    }

    else if (direction == 'd'){
        if (heroStatus.x == width - 1) return false;
        heroStatus.x++;
    }

    Cell& herocell = cells[heroStatus.y][heroStatus.x];

    if (herocell.hasWeapons()){
        heroStatus.maceCount += herocell.getThingCount(MACE);
        heroStatus.daggerCount += herocell.getThingCount(DAGGER);
        heroStatus.swordCount += herocell.getThingCount(SWORD);
        herocell.removeEverything();
    }

    else if (herocell.hasMonsters()){
        ThingType type;
        bool alive = true;
        int numthings = herocell.getThingCount();

        for (int i = 0; i < numthings; i++){
            type = herocell.getThing(0).getType();

            if (type == SKELETON){
                (heroStatus.maceCount > 0) ? (heroStatus.maceCount--) : (alive = false);
            }

            else if (type == VAMPIRE){
                (heroStatus.daggerCount > 0) ? (heroStatus.daggerCount--) : (alive = false);
            }

            else if (type == DRAGON){
                (heroStatus.swordCount > 0) ? (heroStatus.swordCount--) : (alive = false);
            }

            if(!alive){
                heroStatus.alive = false;
                break;
            }
            herocell.removeThing(type, 1);          
        }
    }
    return true;
}

bool Game::isHeroAlive() const{
    if (heroStatus.alive) return true;
    return false;
}

bool Game::isAllMonstersGone() const{
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (cells[i][j].hasMonsters()) return false;
        }
    }
    return true;
}

int Game::getMonsterCount() const{
    int monstercount = 0;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (cells[i][j].hasMonsters()) monstercount += cells[i][j].getThingCount();
        }
    }
    return monstercount;    
}

int Game::getHeroX() const{
    return heroStatus.x;
}

int Game::getHeroY() const{
    return heroStatus.y;
}