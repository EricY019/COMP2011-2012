#include "given.h"
#include "todo.h"
#include <iostream>
using namespace std;

int main()
{
    cout << "Hello! What are you?" << endl;
    cout << "1. I am a programmer!" << endl;
    cout << "2. I am the HERO!" << endl;
    cout << "Your answer: ";
    int choice;
    cin >> choice;
    cout << endl;
    if(choice == 2) //play the game
    {
        HeroStatus heroStatus;
        int width = 4;  //map width
        int height = 5; //map height
        Node ***map = generateMap(width, height);

        addThing(map, width, height, 0, 0, HERO, 1);
        addThing(map, width, height, 0, 2, SWORD, 3);
        addThing(map, width, height, 3, 3, DRAGON, 1);
        addThing(map, width, height, 3, 3, DRAGON, 1);
        addThing(map, width, height, 3, 1, VAMPIRE, 1);
        addThing(map, width, height, 2, 0, MACE, 1);
        addThing(map, width, height, 2, 0, DAGGER, 3);
        addThing(map, width, height, 1, 3, DAGGER, 1);

        bool gameOver = false;
        while (!gameOver)
        {
            printMap(map, width, height);
            cout << endl;
            cout << "Hi Hero! What is your move? (w/a/s/d)" << endl;
            printHeroStatus(heroStatus);
            printMonsterCount(map, width, height);
            cout << "Your move: ";
            char move;
            cin >> move;
            cout << endl;
            switch (move)
            {
            case 'w':
            case 'a':
            case 's':
            case 'd':
                if (!moveHero(move, map, width, height, heroStatus))
                {
                    cout << "We cannot move to there!" << endl;
                }
                break;
            default:
                cout << "The hero has went crazy, aborting!" << endl;
                gameOver = true;
            }
            if (!heroStatus.alive)
            {
                printMap(map, width, height);
                printHeroStatus(heroStatus);
                cout << "RIP. You tried! :(" << endl;
                gameOver = true;
            }
            else if (getMonsterCount(map, width, height) == 0)
            {
                printMap(map, width, height);
                printHeroStatus(heroStatus);
                cout << "GOOD JOB HERO! YOU HAVE SAVED THE WORLD!" << endl;
                gameOver = true;
            }
        }

        deleteMap(map, width, height);
    }
    else if(choice == 1) //test the test cases
    {
        cout << "OK! Let's test our program." << endl;
        //cout << boolalpha; //removed this line (see FAQ); on Zinc and sample output, we show 1/0 instead of true/false, so let's just remove this line for consistency

        int testCaseNumber = 1;
        cout << "Which test case? ";
        cin >> testCaseNumber;
        cout << endl;
        cout << "Running test case " << testCaseNumber << "..." << endl;

        if(testCaseNumber == 1)
        {
            //description: simple test of generateMap
            int width = 5;  //map width
            int height = 4; //map height
            cout << "An empty map:" << endl;
            Node ***map = generateMap(width, height);
            printMap(map, width, height);
            deleteMap(map, width, height);
            cout << map << map[0][0] << endl;
            cout << "Another empty map:" << endl;
            width = 5;
            height = 6;
            map = generateMap(width, height);
            printMap(map, width, height);
            //for this test case, we deliberately chose not to release the dynamic memory allocated; memory leak won't be checked for this case
            deleteMap(map, width, height);
            cout << map << map[0][0] << endl;
        }
        else if(testCaseNumber == 2)
        {
            //description: simple test of addThing, and printMonsterCount
            int width = 5;  //map width
            int height = 4; //map height
            Node ***map = generateMap(width, height);
            cout << "adding hero: " << addThing(map, width, height, -1, 0, HERO, 1) << endl;
            cout << "adding hero: " << addThing(map, width, height, 4, 5, HERO, 1) << endl;
            cout << "adding hero: " << addThing(map, width, height, 0, 0, HERO, 1) << endl;
            cout << "adding monster: " << addThing(map, width, height, 3, 2, VAMPIRE, 1) << endl;
            printMap(map, width, height);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            printMonsterCount(map, width, height);
            //for this test case, we deliberately chose not to release the dynamic memory allocated; memory leak won't be checked for this case
            deleteMap(map, width, height);
        }
        else if(testCaseNumber == 3)
        {
            //description: advanced test of addThing, and printMonsterCount
            int width = 5;  //map width
            int height = 4; //map height
            Node ***map = generateMap(width, height);
            cout << "adding HERO: " << addThing(map, width, height, 0, 0, HERO, 1) << endl;
            cout << "adding DAGGER: " << addThing(map, width, height, 2, 1, DAGGER, 1) << endl;
            cout << "adding DAGGER: " << addThing(map, width, height, 2, 1, DAGGER, 1) << endl;
            cout << "adding SKELETON: " << addThing(map, width, height, 3, 2, SKELETON, 1) << endl;
            cout << "adding VAMPIRE: " << addThing(map, width, height, 3, 2, VAMPIRE, 3) << endl;
            cout << "adding MACE: " << addThing(map, width, height, 3, 3, MACE, 1) << endl;
            cout << "adding SWORD: " << addThing(map, width, height, 3, 3, SWORD, 3) << endl;
            cout << "adding DAGGER: " << addThing(map, width, height, 3, 3, DAGGER, 2) << endl;
            printMap(map, width, height);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Linked list nodes at (2,1): "; printLinkedList(map[1][2]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            cout << "Linked list nodes at (3,3): "; printLinkedList(map[3][3]);
            printMonsterCount(map, width, height);
            //for this test case, we deliberately chose not to release the dynamic memory allocated; memory leak won't be checked for this case
            deleteMap(map, width, height);
        }
        else if(testCaseNumber == 4)
        {
            //description: simple test of removeThing (on a cell with 1 type of thing)
            int width = 5;  //map width
            int height = 4; //map height
            Node ***map = generateMap(width, height);
            addThing(map, width, height, 0, 0, HERO, 1);
            addThing(map, width, height, 2, 1, DAGGER, 1);
            addThing(map, width, height, 2, 1, DAGGER, 1);
            addThing(map, width, height, 3, 2, SKELETON, 1);
            addThing(map, width, height, 3, 2, VAMPIRE, 3);
            addThing(map, width, height, 3, 3, MACE, 1);
            addThing(map, width, height, 3, 3, SWORD, 3);
            addThing(map, width, height, 3, 3, DAGGER, 2);
            cout << "removeing DAGGER: " << removeThing(map, width, height, 2, 1, DAGGER, 1) << endl;
            printMap(map, width, height);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Linked list nodes at (2,1): "; printLinkedList(map[1][2]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            cout << "Linked list nodes at (3,3): "; printLinkedList(map[3][3]);
            cout << "removeing DAGGER again: " << removeThing(map, width, height, 2, 1, DAGGER, 1) << endl;
            printMap(map, width, height);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Linked list nodes at (2,1): "; printLinkedList(map[1][2]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            cout << "Linked list nodes at (3,3): "; printLinkedList(map[3][3]);
            cout << "removeing DAGGER one more time: " << removeThing(map, width, height, 2, 1, DAGGER, 1) << endl;
            printMap(map, width, height);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Linked list nodes at (2,1): "; printLinkedList(map[1][2]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            cout << "Linked list nodes at (3,3): "; printLinkedList(map[3][3]);
            //for this test case, we deliberately chose not to release the dynamic memory allocated; memory leak won't be checked for this case
            deleteMap(map, width, height);
        }
        else if(testCaseNumber == 5)
        {
            //description: simple test of moveHero and printHeroStatus
            int width = 5;  //map width
            int height = 4; //map height
            HeroStatus heroStatus;
            Node ***map = generateMap(width, height);
            addThing(map, width, height, 0, 0, HERO, 1);
            addThing(map, width, height, 2, 1, DAGGER, 1);
            addThing(map, width, height, 2, 1, DAGGER, 1);
            addThing(map, width, height, 3, 2, SKELETON, 1);
            addThing(map, width, height, 3, 2, VAMPIRE, 3);
            addThing(map, width, height, 3, 3, MACE, 1);
            addThing(map, width, height, 3, 3, SWORD, 3);
            addThing(map, width, height, 3, 3, DAGGER, 2);
            printMap(map, width, height);
            printHeroStatus(heroStatus);
            cout << "moveHero: " << moveHero('a', map, width, height, heroStatus) << endl;
            cout << "moveHero: " << moveHero('w', map, width, height, heroStatus) << endl;
            cout << "moveHero: " << moveHero('d', map, width, height, heroStatus) << endl;
            printMap(map, width, height);
            printHeroStatus(heroStatus);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (1,0): "; printLinkedList(map[0][1]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Linked list nodes at (2,1): "; printLinkedList(map[1][2]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            cout << "Linked list nodes at (3,3): "; printLinkedList(map[3][3]);
            //for this test case, we deliberately chose not to release the dynamic memory allocated; memory leak won't be checked for this case
            deleteMap(map, width, height);
        }
        else if(testCaseNumber == 6)
        {
            //description: test of moving hero to get weapons
            int width = 5;  //map width
            int height = 4; //map height
            HeroStatus heroStatus;
            Node ***map = generateMap(width, height);
            addThing(map, width, height, 0, 0, HERO, 1);
            addThing(map, width, height, 2, 1, DAGGER, 1);
            addThing(map, width, height, 2, 1, DAGGER, 1);
            addThing(map, width, height, 3, 2, SKELETON, 1);
            addThing(map, width, height, 3, 2, VAMPIRE, 3);
            addThing(map, width, height, 3, 3, MACE, 1);
            addThing(map, width, height, 3, 3, SWORD, 3);
            addThing(map, width, height, 3, 3, DAGGER, 2);
            printMap(map, width, height);
            printHeroStatus(heroStatus);
            cout << "moveHero: " << moveHero('d', map, width, height, heroStatus) << endl;
            cout << "moveHero: " << moveHero('d', map, width, height, heroStatus) << endl;
            cout << "moveHero: " << moveHero('s', map, width, height, heroStatus) << endl; //takes 2 daggers
            printMap(map, width, height);
            printHeroStatus(heroStatus);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (1,0): "; printLinkedList(map[0][1]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Linked list nodes at (2,1): "; printLinkedList(map[1][2]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            cout << "Linked list nodes at (3,3): "; printLinkedList(map[3][3]);
            cout << "moveHero: " << moveHero('s', map, width, height, heroStatus) << endl;
            cout << "moveHero: " << moveHero('s', map, width, height, heroStatus) << endl;
            cout << "moveHero: " << moveHero('d', map, width, height, heroStatus) << endl; //gets 1 mace, 3 sowrds, and 2 daggers
            printMap(map, width, height);
            printHeroStatus(heroStatus);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (1,0): "; printLinkedList(map[0][1]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Linked list nodes at (2,1): "; printLinkedList(map[1][2]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            cout << "Linked list nodes at (3,3): "; printLinkedList(map[3][3]);
            //for this test case, we deliberately chose not to release the dynamic memory allocated; memory leak won't be checked for this case
            deleteMap(map, width, height);
        }
        else if(testCaseNumber == 7)
        {
            //description: test of moving hero to get weapons, encounter monsters, and live
            int width = 5;  //map width
            int height = 4; //map height
            HeroStatus heroStatus;
            Node ***map = generateMap(width, height);
            addThing(map, width, height, 0, 0, HERO, 1);
            addThing(map, width, height, 2, 1, DAGGER, 1);
            addThing(map, width, height, 2, 1, DAGGER, 1);
            addThing(map, width, height, 3, 2, SKELETON, 1);
            addThing(map, width, height, 3, 2, VAMPIRE, 3);
            addThing(map, width, height, 3, 3, MACE, 1);
            addThing(map, width, height, 3, 3, SWORD, 3);
            addThing(map, width, height, 3, 3, DAGGER, 2);
            printMap(map, width, height);
            printHeroStatus(heroStatus);
            cout << "moveHero: " << moveHero('d', map, width, height, heroStatus) << endl;
            cout << "moveHero: " << moveHero('d', map, width, height, heroStatus) << endl;
            cout << "moveHero: " << moveHero('s', map, width, height, heroStatus) << endl; //get weapons
            printMap(map, width, height);
            printHeroStatus(heroStatus);
            cout << "moveHero: " << moveHero('s', map, width, height, heroStatus) << endl;
            cout << "moveHero: " << moveHero('s', map, width, height, heroStatus) << endl;
            cout << "moveHero: " << moveHero('d', map, width, height, heroStatus) << endl; //get weapons
            printMap(map, width, height);
            printHeroStatus(heroStatus);
            cout << "moveHero: " << moveHero('w', map, width, height, heroStatus) << endl; //encounter monsters
            printMap(map, width, height);
            printHeroStatus(heroStatus);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (1,0): "; printLinkedList(map[0][1]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Linked list nodes at (2,1): "; printLinkedList(map[1][2]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            cout << "Linked list nodes at (3,3): "; printLinkedList(map[3][3]);
            cout << "Hero is " << (heroStatus.alive?"alive":"dead") << endl;
            //for this test case, we deliberately chose not to release the dynamic memory allocated; memory leak won't be checked for this case
            deleteMap(map, width, height);
        }
        else if(testCaseNumber == 8)
        {
            //description: test of moving hero to get weapons, encounter monsters, and die; check getMonsterCount as well
            int width = 5;  //map width
            int height = 4; //map height
            HeroStatus heroStatus;
            Node ***map = generateMap(width, height);
            addThing(map, width, height, 0, 0, HERO, 1);
            addThing(map, width, height, 1, 0, SWORD, 1);
            addThing(map, width, height, 1, 0, MACE, 1);
            addThing(map, width, height, 1, 1, SKELETON, 1);
            addThing(map, width, height, 1, 1, VAMPIRE, 1);
            printMap(map, width, height);
            printHeroStatus(heroStatus);
            cout << "getMonsterCount returns " << getMonsterCount(map, width, height) << endl;
            cout << "Hero is " << (heroStatus.alive?"alive":"dead") << endl;
            cout << "moveHero: " << moveHero('d', map, width, height, heroStatus) << endl; //get weapons
            cout << "moveHero: " << moveHero('s', map, width, height, heroStatus) << endl; //encounter monsters (not enough appropriate weapons to kill them all)
            printMap(map, width, height);
            printHeroStatus(heroStatus);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (0,1): "; printLinkedList(map[1][0]);
            cout << "Linked list nodes at (1,0): "; printLinkedList(map[0][1]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Hero is " << (heroStatus.alive?"alive":"dead") << endl;
            cout << "getMonsterCount returns " << getMonsterCount(map, width, height) << endl;
            //for this test case, we deliberately chose not to release the dynamic memory allocated; memory leak won't be checked for this case
            deleteMap(map, width, height);
        }
        else if(testCaseNumber == 9)
        {
            //description: simple memory leak checking: just to delete empty maps and a linked list
            int width = 5;  //map width
            int height = 4; //map height
            cout << "An empty map:" << endl;
            Node ***map = generateMap(width, height);
            printMap(map, width, height);
            cout << "Deleting map..." << endl;
            deleteMap(map, width, height);
            cout << "Done!" << endl;
            cout << "Another empty map:" << endl;
            width = 5;
            height = 6;
            map = generateMap(width, height);
            printMap(map, width, height);
            cout << "Deleting map..." << endl;
            deleteMap(map, width, height);
            cout << "Done!" << endl;
            Node* node1 = new Node;
            Node* node2 = new Node;
            node1->next = node2;
            cout << "Deleting a linked list of 2 nodes..." << endl;
            deleteLinkedList(node1);
            cout << "Done!" << endl;
            //for this test case, we WILL check for memory leak on Zinc. See the new Zinc submission guide for details.
        }
        else if(testCaseNumber == 10)
        {
            //description: memory leak checking for a simple test of removeThing (on a cell with 1 type of thing)
            int width = 5;  //map width
            int height = 4; //map height
            Node ***map = generateMap(width, height);
            addThing(map, width, height, 0, 0, HERO, 1);
            addThing(map, width, height, 2, 1, DAGGER, 1);
            addThing(map, width, height, 2, 1, DAGGER, 1);
            addThing(map, width, height, 3, 2, SKELETON, 1);
            addThing(map, width, height, 3, 2, VAMPIRE, 3);
            addThing(map, width, height, 3, 3, MACE, 1);
            addThing(map, width, height, 3, 3, SWORD, 3);
            addThing(map, width, height, 3, 3, DAGGER, 2);
            cout << "removeing DAGGER: " << removeThing(map, width, height, 2, 1, DAGGER, 1) << endl;
            printMap(map, width, height);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Linked list nodes at (2,1): "; printLinkedList(map[1][2]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            cout << "Linked list nodes at (3,3): "; printLinkedList(map[3][3]);
            cout << "removeing DAGGER again: " << removeThing(map, width, height, 2, 1, DAGGER, 1) << endl;
            printMap(map, width, height);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Linked list nodes at (2,1): "; printLinkedList(map[1][2]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            cout << "Linked list nodes at (3,3): "; printLinkedList(map[3][3]);
            cout << "removeing DAGGER one more time: " << removeThing(map, width, height, 2, 1, DAGGER, 1) << endl;
            printMap(map, width, height);
            cout << "Linked list nodes at (0,0): "; printLinkedList(map[0][0]);
            cout << "Linked list nodes at (1,1): "; printLinkedList(map[1][1]);
            cout << "Linked list nodes at (2,1): "; printLinkedList(map[1][2]);
            cout << "Linked list nodes at (3,2): "; printLinkedList(map[2][3]);
            cout << "Linked list nodes at (3,3): "; printLinkedList(map[3][3]);
            cout << "Deleting map..." << endl;
            deleteMap(map, width, height);
            cout << "Done!" << endl;
            //for this test case, we WILL check for memory leak on Zinc. See the new Zinc submission guide for details.
        }
        else if (testCaseNumber == 11)
        {
            int width = 6;
            int height = 4;
            Node ***map = generateMap(width, height);
            HeroStatus heroStatus;
            addThing(map, width, height, 0, 0, HERO, 1);

            for (int y = 0; y < 2; y++){
                for (int x = 0; x < width; x++){
                    if (x == 0 && y == 0)   continue;
                    addThing(map, width, height, x, y, MACE, 2);
                    addThing(map, width, height, x, y, DAGGER, 2);
                    addThing(map, width, height, x, y, SWORD, 2);
                }
            }
            for (int y = 2; y < height; y++){
                for (int x = 0; x < width; x++){
                    addThing(map, width, height, x, y, SKELETON, 2);
                    addThing(map, width, height, x, y, VAMPIRE, 2);
                    addThing(map, width, height, x, y, DRAGON, 2);
                }
            }
            printMap(map, width, height);
            printMonsterCount(map, width, height);
            for (int y = 0; y < height; y++){
                for (int x = 0; x < width; x++){
                    moveHero('d', map, width, height, heroStatus);
                }
                for (int x = 0; x < width; x++){
                    moveHero('a', map, width, height, heroStatus);
                }
                printMap(map, width, height);
                printHeroStatus(heroStatus);
                printMonsterCount(map, width, height);
                moveHero('s', map, width, height, heroStatus);
            }
            deleteMap(map, width, height);
            cout << "Done deleting map!" << endl;
        }
        //you can design and add more test cases yourself
    }
    else //choice is neither 1 nor 2...
    {
        cout << "So you are crazy... bye!" << endl;
    }

    return 0;
}
