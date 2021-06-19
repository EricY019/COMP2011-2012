//ONLY SUBMIT THIS FILE TO ZINC
#include "given.h"
#include "todo.h"
#include <iostream>
using namespace std;
//be reminded that you should NOT include any additional library, please read "Additional Notes" on the PA3 webpage 

Node*** generateMap(int width, int height)
{
    Node*** map = new Node** [height]; // Node*** map, Node** map[height]
    
    for (int y = 0; y < height; y++){
        map[y] = new Node* [width]; // Node* map[height][width]

        for (int x = 0; x < width; x++){
            map[y][x] = nullptr;
        }
    }
    
    return map;
}

void printHeroStatus(const HeroStatus& heroStatus)
{
    cout << "Hero status: x=" << heroStatus.x << " y=" << heroStatus.y << " #mace=" << heroStatus.maceCount << " #dagger=" << heroStatus.daggerCount << " #sword=" << heroStatus.swordCount << endl;
}

void printMonsterCount(Node*** map, int width, int height)
{
    int MonsterCount = 0;

    for (int y = 0; y < height; y++){

        for (int x = 0; x < width; x++){
            Node* nodepoint = map[y][x];
            if (nodepoint == nullptr) continue;
            
            for (; nodepoint != nullptr; nodepoint = nodepoint->next){
                if (nodepoint->thing == SKELETON || nodepoint->thing == VAMPIRE || nodepoint->thing == DRAGON){
                    MonsterCount += nodepoint->quantity;
                }
            }
        }
    }

    if (MonsterCount == 1){
        cout << "There is still one more monster left!" << endl;
    }
    else{
        cout << "There are " << MonsterCount << " monsters left in the world!" << endl;
    }
}

int getLinkedListLength(const Node* head)
{
    int count = 0;

    if (head != nullptr){
        for (; head != nullptr; head = head->next){
            ++count;
        }
    }

    return count;
}

bool addThing(Node*** map, int width, int height, int x, int y, Thing thing, int quantity)
{
    // invalid position
    if (x < 0 || x > width - 1 || y < 0 || y > height - 1){
        return false;
    }
    // empty cell
    else if (map[y][x] == nullptr){
        Node* node = new Node;
        node->thing = thing;
        node->quantity = quantity;
        map[y][x] = node;
    }

    // non-empty cell
    else if (map[y][x] != nullptr){
        Node* Nodepoint = map[y][x];
        for (; Nodepoint != nullptr; Nodepoint = Nodepoint->next){

            if (Nodepoint->thing == thing){ // match
                Nodepoint->quantity += quantity;
                break;
            }
            else if (Nodepoint->next == nullptr){ // no match
                Node* lastnode = new Node;
                lastnode->thing = thing;
                lastnode->quantity = quantity;
                Nodepoint->next = lastnode;
                break;
            }
        }
    }

    return true;
}

bool removeThing(Node*** map, int width, int height, int x, int y, Thing thing, int quantity)
{
    // invalid position
    if (x < 0 || x > width - 1 || y < 0 || y > height - 1){
        return false;
    }

    Node* Nodepoint = map[y][x];
    Node* prevNodepoint = nullptr;

    while (Nodepoint != nullptr && Nodepoint->thing != thing){
        prevNodepoint = Nodepoint;
        Nodepoint = Nodepoint->next;
    }

    if (Nodepoint != nullptr){ // match

        if (Nodepoint->quantity < quantity){ // less
            return false;
        }
        else if (Nodepoint->quantity > quantity){ // more
            Nodepoint->quantity -= quantity;
            return true;
        }
        // same quantity
        if (Nodepoint == map[y][x]){ // delete first item
            map[y][x] = Nodepoint->next;
        }
        else{
            prevNodepoint->next = Nodepoint->next;
        }

        delete Nodepoint;
        Nodepoint = nullptr;
        return true;

    }
    // no match
    return false;
}

void deleteLinkedList(Node*& head)
{
    if (head == nullptr){
        return;
    }

    deleteLinkedList(head->next);
    delete head;
    head = nullptr;
}

void deleteMap(Node*** map, int width, int height)
{
    for (int y = 0; y < height; y++){

        for (int x = 0; x < width; x++){
            deleteLinkedList(map[y][x]);
        }

        delete[] map[y];
        map[y] = nullptr;
    }

    delete[] map;
    map = nullptr;
}

bool moveHero(char move, Node*** map, int width, int height, HeroStatus &heroStatus)
{
    if (move == 'w'){
        if (heroStatus.y == 0) return false;
        removeThing(map, width, height, heroStatus.x, heroStatus.y, HERO, 1);
        heroStatus.y--;
    }
    else if (move == 'a'){
        if (heroStatus.x == 0) return false;
        removeThing(map, width, height, heroStatus.x, heroStatus.y, HERO, 1);
        heroStatus.x--;
    }
    else if (move == 's'){
        if (heroStatus.y == height - 1) return false;
        removeThing(map, width, height, heroStatus.x, heroStatus.y, HERO, 1);
        heroStatus.y++;
    }
    else if (move == 'd'){
        if (heroStatus.x == width - 1) return false;
        removeThing(map, width, height, heroStatus.x, heroStatus.y, HERO, 1);
        heroStatus.x++;
    }

    Node* Nodepoint = map[heroStatus.y][heroStatus.x];

    // empty cell
    if (Nodepoint == nullptr){
        addThing(map, width, height, heroStatus.x, heroStatus.y, HERO, 1);
    }
    // weapon cell
    else if (Nodepoint->thing == MACE || Nodepoint->thing == DAGGER || Nodepoint->thing == SWORD){
        for (; Nodepoint != nullptr; Nodepoint = Nodepoint->next){
            if (Nodepoint->thing == MACE){
                heroStatus.maceCount += Nodepoint->quantity;
            }
            else if (Nodepoint->thing == DAGGER){
                heroStatus.daggerCount += Nodepoint->quantity;
            }
            else if (Nodepoint->thing == SWORD){
                heroStatus.swordCount += Nodepoint->quantity;
            }
        }
        deleteLinkedList(map[heroStatus.y][heroStatus.x]);
        addThing(map, width, height, heroStatus.x, heroStatus.y, HERO, 1);
    }
    // monster cell
    else if (Nodepoint->thing == SKELETON || Nodepoint->thing == VAMPIRE || Nodepoint->thing == DRAGON){
        int requireMace = 0, requireDagger = 0, requireSword = 0;
        for (; Nodepoint != nullptr; Nodepoint = Nodepoint->next){
            if (Nodepoint->thing == SKELETON){
                requireMace += Nodepoint->quantity;
            }
            else if (Nodepoint->thing == VAMPIRE){
                requireDagger += Nodepoint->quantity;
            }
            else if (Nodepoint->thing == DRAGON){
                requireSword += Nodepoint->quantity;
            }
        }

        if (requireMace > heroStatus.maceCount || requireDagger > heroStatus.daggerCount || requireSword > heroStatus.swordCount){
            heroStatus.alive = false;
        }
        else {
            heroStatus.maceCount -= requireMace;
            heroStatus.daggerCount -= requireDagger;
            heroStatus.swordCount -= requireSword;
            deleteLinkedList(map[heroStatus.y][heroStatus.x]);
            addThing(map, width, height, heroStatus.x, heroStatus.y, HERO, 1);
        }
    }

    return true;
}

int getMonsterCount(Node*** map, int width, int height)
{
    int MonsterCount = 0;

    for (int y = 0; y < height; y++){

        for (int x = 0; x < width; x++){
            Node* nodepoint = map[y][x];
            if (nodepoint == nullptr) continue;
            
            for (; nodepoint != nullptr; nodepoint = nodepoint->next){
                if (nodepoint->thing == SKELETON || nodepoint->thing == VAMPIRE || nodepoint->thing == DRAGON){
                    MonsterCount += nodepoint->quantity;
                }
            }
        }
    }

    return MonsterCount;
}