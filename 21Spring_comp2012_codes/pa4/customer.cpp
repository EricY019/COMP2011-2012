#include "customer.h"

using namespace std;

Customer::Customer() : purpose(Purpose::UNK), gem(nullptr), highest_acceptable_price(0)
{
}

Customer::Customer(const Customer &other)
{
    *this = other;
}

Customer &Customer::operator=(const Customer &other)
{
    if (this != &other)
    {
        purpose = other.purpose;
        if (other.gem)
        {
            gem = new Gem{other.gem->weight};
        }
        else
        {
            gem = nullptr;
        }
        highest_acceptable_price = other.highest_acceptable_price;
    }

    return *this;
}

Customer::~Customer()
{
    if (gem)
    {
        delete gem;
    }
}

void Customer::decide(const Gem *&gem)
{
    if (gem->weight <= highest_acceptable_price)
    {
        // the customer takes this gem.
        delete gem;
        gem = nullptr;
    }
}

const Gem *Customer::give_gem()
{
    const Gem *gem = this->gem;
    this->gem = nullptr;
    return gem;
}

void Customer::receive_gem(const Gem *&gem)
{
    this->gem = gem;
    gem = nullptr;
}

Customer::Purpose Customer::get_purpose()
{
    return purpose;
}

istream &operator>>(istream &is, Customer &customer)
{
    string purpose;
    int weight;

    is >> purpose >> weight;

    if (purpose == "b")
    {
        int highest_acceptable_price;
        is >> highest_acceptable_price;
        customer.purpose = Customer::Purpose::BUY;
        if (weight > 0)
        {
            customer.gem = new Gem{weight};
        }
        if (highest_acceptable_price > 0)
        {
            customer.highest_acceptable_price = highest_acceptable_price;
        }
    }
    else if (purpose == "s")
    {
        customer.purpose = Customer::Purpose::SELL;
        if (weight < 1)
        {
            throw runtime_error("All weight of gem to sell should be larger than 0.");
        }
        customer.gem = new Gem{weight};
    }
    else
    {
        throw runtime_error("Unknown purpose: \"" + purpose + "\".");
    }

    return is;
}

ostream &operator<<(ostream &os, const Customer &customer)
{
    os << "Customer: ";
    if (customer.purpose == Customer::Purpose::BUY)
    {
        os << "I want to buy a gem ";
        if (customer.gem != nullptr)
        {
            os << "that is heavier than " << *customer.gem << " ";
        }
        os << "and the highest acceptable price is $" << customer.highest_acceptable_price;
    }
    else
    {
        os << "I want to sell " << *customer.gem;
    }
    os << ".";
    return os;
}
