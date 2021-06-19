#ifndef DUMB_STORAGE_H
#define DUMB_STORAGE_H

#include "container.h"
#include "storage.h"

class DumbStorage : public Storage
{
  public:
    DumbStorage(int size) : Storage(allocate_containers<Container>(size), new Container()) {}
    virtual void select_container_for_buyer() override;
    virtual void deselect_container() override;
};

#endif
