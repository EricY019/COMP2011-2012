#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "gem.h"

class Customer
{
    friend std::istream &operator>>(std::istream &is, Customer &customer);       // This reads customer information from istream (for file reading).
    friend std::ostream &operator<<(std::ostream &os, const Customer &customer); // This prints the customer information in the customer view.

  public:
    enum class Purpose
    {
        UNK, // Unknown purpose
        BUY, // A buyer
        SELL // A seller
    };

    Customer();
    Customer(const Customer &other);
    Customer &operator=(const Customer &other);
    ~Customer();

    Purpose get_purpose();
    const Gem *give_gem();             // Give the gem to shop clerk as the reference, or sell it to the shop. The ownership of gem is temporally transferred to shop.
    void receive_gem(const Gem *&gem); // Receive the reference gem from shop. The ownership of gem is transferred back to customer.

    void decide(const Gem *&gem); // Decide whether to accept the offer. If so, the ownership of the new gem will be transferred from shop to this customer.

  private:
    Purpose purpose;
    const Gem *gem;
    int highest_acceptable_price;
};

#endif
