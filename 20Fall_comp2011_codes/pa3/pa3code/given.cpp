#include "given.h"
#include "todo.h"
#include <iostream>
using namespace std;

void printMap(Node*** map, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printCell(map[i][j]);
            cout << " ";
        }
        cout << endl;
    }
}

void printCell(const Node* head)
{
    int thingCount = getLinkedListLength(head); //you need to implement getLinkedListLength correctly for printCell to work correctly
    if (thingCount == 0)
        cout << '.';
    else if (thingCount == 1)
    {
        const char REPRESENTING_CHAR[] = {'m', 'd', 's', 'K', 'V', 'D', 'H'};
        cout << REPRESENTING_CHAR[head->thing];
    }
    else
        cout << static_cast<char>(('0' + thingCount));
}

void printLinkedList(const Node* head)
{
    if(head)    
        while(head)
        {
            cout << "(Thing=" << head->thing << ",quantity=" << head->quantity << ",next=" << (head->next==nullptr?"nullptr":"not nullptr") << ") ";
            head = head->next;
        }
    else
        cout << "Empty.";
    cout << endl;
}