#ifndef SMART_CONTAINER_H
#define SMART_CONTAINER_H

#include "container.h"

class SmartContainer : public Container
{
  public:
    SmartContainer *parent = nullptr; // Whether to use it or not?
    SmartContainer *left = nullptr;   // Everything on the left is not heavier than the key.
    SmartContainer *right = nullptr;  // Everything on the right is heavier than the key.
};

#endif
