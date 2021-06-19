//Only submit this file to Zinc
#include "given.h"
#include "todo.h"
#include <iostream>
using namespace std;

Node*** generateMap(int width, int height)
{
    Node*** node = new Node **[height];
    for (int i = 0; i < height; i++)
    {
        node[i] = new Node *[width];
        for (int j = 0; j < width; j++)
            node[i][j] = nullptr;
    }
    return node;
}

void printHeroStatus(const HeroStatus& heroStatus)
{
    cout << "Hero status: x=" << heroStatus.x << " y=" << heroStatus.y << " #mace=" << heroStatus.maceCount << " #dagger=" << heroStatus.daggerCount << " #sword=" << heroStatus.swordCount << endl;
}

void printMonsterCount(Node*** map, int width, int height)
{
    int count = getMonsterCount(map, width, height);
    if (count == 1)
        cout << "There is still one more monster left!" << endl;
    else
        cout << "There are " << count << " monsters left in the world!" << endl;
}

int getLinkedListLength(const Node* head)
{
    int n = 0;
    while (head)
    {
        n++;
        head = head->next;
    }
    return n;
}

//helper function: not given to students
void addThingToLinkedList(Node*& head, Thing thing, int quantity)
{
    if (!head) //empty list
    {
        head = new Node;
        head->thing = thing;
        head->quantity = quantity;
    }
    else
    {
        //look for it
        Node *cur = head;
        Node *prev = nullptr;
        do
        {
            if (cur->thing == thing)
            {
                cur->quantity += quantity;
                return;
            }
            prev = cur;
            cur = cur->next;
        } while (cur);

        //prev is last node at this point
        prev->next = new Node;
        prev->next->thing = thing;
        prev->next->quantity = quantity;
    }
}

//helper function: not given to students
bool removeThingFromLinkedList(Node*& head, Thing thing, int quantity)
{
    if (head)
    {
        //look for it
        Node *cur = head;
        Node *prev = nullptr;
        do
        {
            if (cur->thing == thing)
            {
                if (cur->quantity < quantity)
                    return false;
                else if (cur->quantity > quantity)
                {
                    cur->quantity -= quantity;
                    return true;
                }
                else //remove the node altogether
                {
                    if (prev) //deleting a node that is not head
                    {
                        prev->next = cur->next;
                        delete cur;
                    }
                    else //deleting the head node
                    {
                        head = cur->next;
                        delete cur;
                    }
                    return true;
                }
            }
            prev = cur;
            cur = cur->next;
        } while (cur);
    }
    return false;
}

bool addThing(Node*** map, int width, int height, int x, int y, Thing thing, int quantity)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return false;
    addThingToLinkedList(map[y][x], thing, quantity);
    return true;
}

bool removeThing(Node*** map, int width, int height, int x, int y, Thing thing, int quantity)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return false;
    return removeThingFromLinkedList(map[y][x], thing, quantity);
}

void deleteLinkedList(Node*& head)
{
    while (head)
    {
        Node *next = head->next;
        delete head;
        head = next;
    }
}

void deleteMap(Node*** map, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            deleteLinkedList(map[i][j]);
        }
        delete [] map[i];
    }
    delete [] map;
}

//helper function: not given to students
bool isWeapon(Thing thing)
{
    return (thing==MACE||thing==DAGGER||thing==SWORD);
}

//helper function: not given to students
bool isMonster(Thing thing)
{
    return (thing==SKELETON||thing==VAMPIRE||thing==DRAGON);
}

bool moveHero(char move, Node*** map, int width, int height, HeroStatus &heroStatus)
{
    int ox = 0; //offset x
    int oy = 0; //offset y
    if (move == 'w')
        oy = -1;
    if (move == 'a')
        ox = -1;
    if (move == 's')
        oy = 1;
    if (move == 'd')
        ox = 1;
    int tx = heroStatus.x + ox; //target x
    int ty = heroStatus.y + oy; //target y
    if (tx < 0 || tx >= width || ty < 0 || ty >= height)
        return false;

    removeThing(map, width, height, heroStatus.x, heroStatus.y, HERO, 1);
    heroStatus.x = tx;
    heroStatus.y = ty;

    Node*& cur = map[ty][tx];
    if(cur)
    {
        if(isWeapon(cur->thing))
        {
            while (cur)
            {
                //give the weapons to the hero
                if (cur->thing == MACE)
                    heroStatus.maceCount += cur->quantity;
                else if (cur->thing == DAGGER)
                    heroStatus.daggerCount += cur->quantity;
                else if (cur->thing == SWORD)
                    heroStatus.swordCount += cur->quantity;  

                //remove the weapon          
                Node *next = cur->next;
                delete cur;
                cur = next;
            }
        }
        else if(isMonster(cur->thing))
        {
            //check if there are enough weapons first
            bool enough = true;
            Node* cur2 = cur;
            while (cur2)
            {
                if( (cur2->thing == SKELETON && heroStatus.maceCount < cur2->quantity) 
                    || (cur2->thing == VAMPIRE && heroStatus.daggerCount < cur2->quantity)
                    || (cur2->thing == DRAGON && heroStatus.swordCount < cur2->quantity) )
                {
                    enough = false;
                    break;
                }
                cur2 = cur2->next;
            }

            if(enough) //enough weapons to kill all monsters
            {
                while (cur)
                {
                    //take the weapons from the hero
                    if (cur->thing == SKELETON)
                        heroStatus.maceCount -= cur->quantity;
                    else if (cur->thing == VAMPIRE)
                        heroStatus.daggerCount -= cur->quantity;
                    else if (cur->thing == DRAGON)
                        heroStatus.swordCount -= cur->quantity;

                        
                    //remove the monster   
                    Node *next = cur->next;
                    delete cur;
                    cur = next;
                }
            }
            else //not enough weapons
            {
                heroStatus.alive = false;
            }
        }
    }
    
    if(heroStatus.alive)
        addThing(map, width, height, tx, ty, HERO, 1);

    return true;
}

//note to self: in given code, write "return 99;"
int getMonsterCount(Node*** map, int width, int height)
{
    int count = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Node *cur = map[i][j];
            while (cur)
            {
                if (cur->thing == SKELETON || cur->thing == VAMPIRE || cur->thing == DRAGON)
                    count += cur->quantity;
                cur = cur->next;
            }
        }
    }
    return count;
}