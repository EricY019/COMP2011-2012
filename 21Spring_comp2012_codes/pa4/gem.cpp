#include "gem.h"

using namespace std;

ostream &operator<<(ostream &os, const Gem &gem)
{
    os << "Gem (" << gem.weight << " ct";
#if defined(DEBUG)
    os << ", @" << &gem;
#endif
    os << ")";
    return os;
}
