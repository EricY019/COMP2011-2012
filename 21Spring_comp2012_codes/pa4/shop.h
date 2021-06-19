#ifndef STORE_H
#define STORE_H

#include "customer.h"
#include "dumb_storage.h"
#include "smart_storage.h"

class Shop
{
  public:
    Shop(int size, bool smart, bool verbose);
    ~Shop();                             // This deletes the storage object.
    int serve(Customer &Customer) const; // Serve the customer by calling serve_buyer or serve_seller.

  private:
    void serve_buyer(Customer &customer) const;  // Handle the buyer.
    void serve_seller(Customer &customer) const; // Handle the seller.

  private:
    Storage *storage; // Either a dumb storage or a smart storage. Owned by shop, destructed by shop.
    bool verbose;     // Control the verbosity of printing.
};

#endif
