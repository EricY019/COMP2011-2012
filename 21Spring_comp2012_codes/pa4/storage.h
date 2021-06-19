#ifndef STORAGE_H
#define STORAGE_H

#include <vector>

#include "container.h"
#include "gem.h"

class Storage
{
    friend std::ostream &operator<<(std::ostream &os, const Storage &storage); // Print the current storage status.

  public:
    Storage(int size);
    Storage(std::vector<Container *> containers, Container *reference);

    virtual ~Storage();                                       // This destructes the "containers" and "reference" container.
    virtual std::size_t hash() const final;                   // Convert the current storage status to a hash code for fast comparison during grading :), just read it for fun.
    virtual Container *get_selected_container() const final;  // An interface to get the current selected container for the shop.
    virtual Container *get_reference_container() const final; // An interface to get the reference container for the shop.
    virtual void select_container_for_seller() final;         // Ask the storage manager to select an empty container for seller. The first empty container will be selected.

    // Select a container containing the gem that will satisfy the buyer, according to the reference container.
    virtual void select_container_for_buyer() = 0;

    // Deselect the container, and also adjust the structure of containers after the change of container state.
    virtual void deselect_container() = 0;

  protected:
    const std::vector<Container *> containers; // All containers owned by the storage.

    Container *reference; // The reference container is independent from the container list and only contains the customer's gem.
    Container *selected;  // A pointer to the current selected (i.e., searched) container.
};

template <typename T>
std::vector<Container *> allocate_containers(int size)
{
    // A helper function to allocate contents for the const vector.
    std::vector<Container *> containers;
    for (int i = 0; i < size; ++i)
    {
        containers.push_back(new T());
    }
    return containers;
}

#endif
