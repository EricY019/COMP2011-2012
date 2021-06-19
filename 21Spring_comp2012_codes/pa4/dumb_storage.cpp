#include "dumb_storage.h"

void DumbStorage::select_container_for_buyer()
{
    // This is the dumb storage implementation, which requires O(N) number of weighing operations.
    deselect_container();
    for (Container *container : containers)
    {
        if (!container->empty() && (selected == nullptr || *container < *selected) && (*reference < *container))
        {
            selected = container;
        }
    }
}

void DumbStorage::deselect_container()
{
    selected = nullptr;
}
