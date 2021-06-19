#include <fstream>

#include "shop.h"

using namespace std;

int main(int argc, char *argv[])
{
    string path;
    bool smart = false;
    bool verbose = false;

    if (argc > 1)
    {
        path = argv[1];
    }
    else
    {
        cout << "Please specify a input file path." << endl;
        return 0;
    }

    if (argc > 2)
    {
        if (string(argv[2]) == "true")
        {
            smart = true;
        }
    }

    if (argc > 3)
    {
        if (string(argv[3]) == "true")
        {
            verbose = true;
        }
    }

    ifstream in(path);

    int shop_size, num_customers;
    int total_weighing_operations = 0;

    in >> shop_size >> num_customers;

    cout << "Shop size: " << shop_size << ", #Customers: " << num_customers << "." << endl
         << endl;

    Shop shop(shop_size, smart, verbose);

    for (int i = 0; i < num_customers; ++i)
    {
        Customer customer;
        in >> customer;
        cout << customer << endl;
        total_weighing_operations += shop.serve(customer);
        cout << endl;
    }

    cout << "Total number of weighing operations: " << total_weighing_operations << "." << endl;

    return 0;
}
