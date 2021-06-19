#ifndef CONTAINER_H
#define CONTAINER_H

#include "gem.h"

class Container
{
    friend class Shop; // Only Shop can operate on container's private members
    friend bool operator<(const Container &a, const Container &b);
    friend std::ostream &operator<<(std::ostream &os, const Container &container);

  public:
    Container();
    Container(const Container &) = delete;
    Container &operator=(const Container &) = delete;
    virtual ~Container();
    bool empty() const;

  private:
    const Gem *gem; // Gem is only accesible to Shop. The storage manager won't have the chance to touch the gem.

    // For computation of the total number of weighing operations.
    // (This is an example implementation, ZINC may use a different implementation to count #weighing operations.)
    static int weighing_operations;

  private:
    int weight() const;        // Help friends to obtain a container's weight
    void put(const Gem *&gem); // Help friends to put gem into container
    const Gem *take();         // Help friends to take gem from container
};

// Container is also known as the dumb container.
typedef Container DumbContainer;

#endif
