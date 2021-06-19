#include "shop.h"
using namespace std;

Shop::Shop(int size, bool smart, bool verbose) : verbose(verbose)
{
    if (smart)
    {
        storage = new SmartStorage(size);
    }
    else
    {
        storage = new DumbStorage(size);
    }
};

Shop::~Shop()
{
    delete storage;
};

int Shop::serve(Customer &customer) const
{
    Container::weighing_operations = 0;

    switch (customer.get_purpose())
    {
    case Customer::Purpose::BUY:
        serve_buyer(customer);
        break;

    case Customer::Purpose::SELL:
        serve_seller(customer);
        break;

    case Customer::Purpose::UNK:
        break;
    }

    if (verbose)
    {
        cout << *storage << endl;
    }

    return Container::weighing_operations;
}

void Shop::serve_seller(Customer &customer) const
{
    cout << "Shop: A seller comes." << endl;

    // This function asks the storage manager to select an empty container for seller.
    storage->select_container_for_seller();

    // Now, get a pointer to the selected container.
    Container *selected = storage->get_selected_container();

    if (selected)
    {
        // Good, there is an empty container. Let's take the customer's gem and put it onto the container.
        const Gem *gem = customer.give_gem();
        cout << "Shop: " << *gem << " is bought from the seller." << endl;
        selected->put(gem);
    }
    else
    {
        // Sadly, there is no empty container.
        cout << "Shop: It seems the storage is full, reject the seller." << endl;
    }

    // Don't forget to deselect the selected container.
    storage->deselect_container();
}

void Shop::serve_buyer(Customer &customer) const
{
    cout << "Shop: A buyer comes." << endl;

    // Fetch the customer's gem (it may be a nullptr, though).
    const Gem *customer_gem = customer.give_gem();

    // Put the gem (or nullptr) into reference container.
    storage->get_reference_container()->put(customer_gem);

    // Select a container containing the gem that will satisfy the buyer, according to the reference container.
    storage->select_container_for_buyer();

    // After selection, get a pointer to the selected container.
    Container *selected = storage->get_selected_container();

    // Don't forget to return the gem to the customer!
    customer_gem = storage->get_reference_container()->take();
    customer.receive_gem(customer_gem);

    if (selected)
    {
        // Good. A valid container is found. Take the gem from the selected container.
        const Gem *gem = selected->take();
        cout << "Shop: We offer " << *gem << " at $" << gem->weight << "." << endl;

        // Let the customer decide.
        customer.decide(gem);

        if (gem == nullptr)
        {
            // The customer takes it!
            cout << "Shop: The customer accepts the offer." << endl;
        }
        else
        {
            // The customer rejects it.
            cout << "Shop: The customer runs away." << endl;
            selected->put(gem);
        }
    }
    else
    {
        // Nothing selected, fail to serve.
        cout << "Shop: We fail to offer a gem." << endl;
    }

    // Don't forget to deselect the container.
    storage->deselect_container();
}
