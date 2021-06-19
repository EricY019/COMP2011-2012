#ifndef SMART_STORAGE
#define SMART_STORAGE

#include "smart_container.h"
#include "storage.h"

class SmartStorage : public Storage
{
  public:
    SmartStorage(int size) : Storage(allocate_containers<SmartContainer>(size), new SmartContainer()) {}

    // TODO: Select a container containing the gem that will satisfy the buyer, according to the reference container.
    virtual void select_container_for_buyer() override;

    // TODO: Deselect the container, and also adjust the structure of containers after the change of container state.
    virtual void deselect_container() override;
};

#endif
