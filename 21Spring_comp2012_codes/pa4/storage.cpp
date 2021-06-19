#include "storage.h"
#include <iomanip>

using namespace std;

Storage::Storage(int size) : Storage(allocate_containers<Container>(size), new Container)
{
}

Storage::Storage(vector<Container *> containers, Container *reference)
    : containers(containers), reference(reference), selected(nullptr)
{
}

Storage::~Storage()
{
    for (Container *container : containers)
    {
        if (container)
        {
            delete container;
        }
    }
    if (reference)
    {
        delete reference;
    }
}

size_t Storage::hash() const
{
    // This hash function gives the same hash code for the same empty/non-empty status of the storages.
    size_t seed = containers.size();
    for (size_t i = 0; i < containers.size(); ++i)
    {
        if (containers[i]->empty())
        {
            // Read more about the magic number: https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
    }
    return seed;
}

Container *Storage::get_selected_container() const
{
    return selected;
}

Container *Storage::get_reference_container() const
{
    return reference;
}

void Storage::select_container_for_seller()
{
    deselect_container();
    for (Container *container : containers)
    {
        if (container->empty())
        {
            selected = container;
            break;
        }
    }
}

ostream &operator<<(ostream &os, const Storage &storage)
{
    // This is a helper function that prints the status of the storage.
    int num_occupied = 0;

    os << "Storage: ";

    for (Container *container : storage.containers)
    {
        if (container->empty())
        {
            os << "E";
        }
        else
        {
            num_occupied += 1;
            os << "V";
        }
    }

    os << " " << setprecision(4) << num_occupied * 100.0 / storage.containers.size() << "%";

    return os;
};
