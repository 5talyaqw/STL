#include "Customer.h"
#include "Store.h"
#include <iostream>
#include <map>

int main() 
{
    int op;
    std::map<std::string, Customer> abcCustomers; //storing data

    Store s1("Shefa Isaschar", "C:\\Users\\Cyber_User\\Desktop\\EkronotExercises\\STL\\InventorySuperMarket.csv");
    Store s2("MagshIKEA", "C:\\Users\\Cyber_User\\Desktop\\EkronotExercises\\STL\\InventoryIKEA.csv");
    Store s3("MagshiPharm", "C:\\Users\\Cyber_User\\Desktop\\EkronotExercises\\STL\\InventoryPharm.csv");

    while (true) {
        std::cout << "Welcome to MagshiMart!" << std::endl;
        std::cout << "1. To sign as customer and buy items" << std::endl;
        std::cout << "2. To update existing customer's items" << std::endl;
        std::cout << "3. To print the customer who pays the most" << std::endl;
        std::cout << "4. To exit" << std::endl;
        std::cin >> op;

        //signing up and adding shpping cart
        if (op == 1) 
        {
            std::string customerName;
            std::cout << "Enter customer name: ";
            std::cin >> customerName;

            //if customer exist
            if (abcCustomers.find(customerName) != abcCustomers.end()) 
            {
                std::cout << "Customer already exists. Returning to main menu." << std::endl;
                continue;
            }

            //creating new customer
            Customer newCustomer(customerName);
            abcCustomers[customerName] = newCustomer;


            int cartOption;
            std::cout << "1. To create a new shopping cart" << std::endl;
            std::cout << "2. Back to main menu" << std::endl;
            std::cin >> cartOption;

            if (cartOption == 1) 
            {
                std::string cartName;
                std::cout << "Enter the new shopping cart name: ";
                std::cin >> cartName;

                //checking if cart exist
                if (newCustomer.getShoppingCart(cartName) != nullptr) 
                {
                    std::cout << "Shopping cart already exists. Returning to main menu." << std::endl;
                    continue;
                }

                newCustomer.createNewShoppingCart(cartName);

                //choosing store
                int storeChoice;
                std::cout << "Select the store to buy from:" << std::endl;
                std::cout << "1. to buy in Shefa Isaschar (Super Market)" << std::endl;
                std::cout << "2. to buy in MagshIKEA (Home products)" << std::endl;
                std::cout << "3. to buy in MagshiPharm (Pharm and utils)" << std::endl;
                std::cout << "4. Back to main menu" << std::endl;
                std::cin >> storeChoice;

                Store* selectedStore = nullptr;
                switch (storeChoice) 
                {
                case 1: 
                    selectedStore = &s1; 
                    break;
                case 2: 
                    selectedStore = &s2; 
                    break;
                case 3: 
                    selectedStore = &s3; 
                    break;
                default: 
                    continue;
                }

                //displaying items
                std::cout << "The items you can buy are: (-1 to exit)" << std::endl;
                auto products = selectedStore->getProductListFilteredByCategory(NONE); //get the products of the store
                for (int i = 0; i < products.size(); ++i) 
                {
                    std::cout << i + 1 << ". " << products[i] << std::endl;  //display the products
                }

                int productChoice;
                while (true) 
                {
                    std::cout << "What item would you like to buy? Input: ";
                    std::cin >> productChoice;

                    if (productChoice == -1)
                    {
                        break;
                    }

                    if (productChoice < 0 || productChoice > selectedStore->getProductListFilteredByCategory(NONE).size()) 
                    {
                        std::cout << "Bad Input!. Please try again." << std::endl;
                        continue;
                    }
                    break;
                }
            }
        }
        //updating customer cart
        else if (op == 2) 
        {
            std::string customerName;
            std::cout << "Enter customer name: ";
            std::cin >> customerName;

            //finding the customer
            if (abcCustomers.find(customerName) == abcCustomers.end()) 
            {
                std::cout << "Customer does not exist. Returning to main menu." << std::endl;
                continue;
            }
      
            Customer& customer = abcCustomers[customerName];


            int updateOption;
            std::cout << "1. To create a new shopping cart" << std::endl;
            std::cout << "2. Update existing shopping cart" << std::endl;
            std::cout << "3. Back to main menu" << std::endl;
            std::cin >> updateOption;

            if (updateOption == 1) 
            {
                // Similar flow as option 1 for creating a new shopping cart
            }
            else if (updateOption == 2) 
            {
                //update an existing cart
                std::string cartName;
                std::cout << "Enter the shopping cart name to update: ";
                std::cin >> cartName;

                //if not finding the shopping cart
                if (customer.getShoppingCart(cartName) == nullptr) 
                {
                    std::cout << "Shopping cart does not exist." << std::endl;
                    continue;
                }
            }
        }
        //printing the molst paying customer
        else if (op == 3) 
        {
            double maxTotal = 0;
            std::string maxCustomer;

            //using iterator to loop through the map
            for (auto it = abcCustomers.begin(); it != abcCustomers.end(); ++it)
            {
                double total = it->second.totalSum();
                if (total > maxTotal)
                {
                    maxTotal = total;
                    maxCustomer = it->first;
                }
            }


            std::cout << "Customer who pays the most: " << maxCustomer << " with total sum: " << maxTotal << std::endl;
        }
        else if (op == 4) 
        {
            break;  //exiting program
        }
        else 
        {
            std::cout << "Bad Input!. Try again." << std::endl;
        }
    }

    return 0;
}
