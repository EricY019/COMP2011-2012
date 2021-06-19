#ifndef GEM_H
#define GEM_H

#include <iostream>

struct Gem
{
    const int weight;
};

std::ostream &operator<<(std::ostream &os, const Gem &gem);

#endif
