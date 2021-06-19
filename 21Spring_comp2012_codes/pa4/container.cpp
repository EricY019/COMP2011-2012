#include "container.h"

using namespace std;

Container::Container() : gem(nullptr)
{
}

Container::~Container()
{
    if (gem)
    {
        delete gem;
    }
}

bool Container::empty() const
{
    return gem == nullptr;
}

ostream &operator<<(ostream &os, const Container &container)
{

    os << "Container [";
    if (container.gem)
    {
        os << *container.gem;
    }
#if defined(DEBUG)
    // During debugging, also print out the address.
    os << ", @" << &container;
#endif
    os << "]";
    return os;
}

int Container::weight() const
{
    if (gem)
    {
        return gem->weight;
    }
    return 0;
}

void Container::put(const Gem *&gem)
{
    if (this->gem == nullptr)
    {
        this->gem = gem;
        gem = nullptr; // Consume the input gem here.
    }
}

const Gem *Container::take()
{
    const Gem *taken = this->gem;
    this->gem = nullptr;
    return taken;
}

bool operator<(const Container &a, const Container &b)
{
    Container::weighing_operations++;
    return a.weight() < b.weight();
}

int Container::weighing_operations = 0;
