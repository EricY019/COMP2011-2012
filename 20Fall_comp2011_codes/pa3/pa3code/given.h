//a thing type in the world
enum Thing
{
    MACE,
    DAGGER,
    SWORD,
    SKELETON,
    VAMPIRE,
    DRAGON,
    HERO
};

//a node in the linked list 
struct Node
{
    Thing thing; //the thing type that this node represents
    int quantity = 1; //the number of the thing
    Node *next = nullptr;  //the next pointer, remember the last node's "next" must point to nullptr
};

//hero status
struct HeroStatus
{
    bool alive = true; //is the hero alive? always true initially
    int x = 0; //x-position, always 0 initially
    int y = 0; //y-position, always 0 initially
    int maceCount = 0; //number of maces the hero has, always 0 initially
    int daggerCount = 0; //number of daggers the hero has, always 0 initially
    int swordCount = 0; //number of swords the hero has, always 0 initially
};

void printMap(Node*** map, int width, int height);
void printCell(const Node* head);
void printLinkedList(const Node* head);