#include"Customer.h"
#include "Store.h"
#include<map>
#include <iostream>
#include <string>


int main()
{
	int op;

	std::map<std::string, Customer> abcCustomers;

	Store s1("Shefa Isaschar", "C:\\Users\\Cyber_User\\Desktop\\EkronotExercises\\STL\\InventorySuperMarket.csv");
	Store s2("MagshIKEA", "C:\\Users\\Cyber_User\\Desktop\\EkronotExercises\\STL\\InventoryIKEA.csv");
	Store s3("MagshiPharm", "C:\\Users\\Cyber_User\\Desktop\\EkronotExercises\\STL\\InventoryPharm.csv");
	

	while (true)
	{
		std::cout << "\nWelcome to MagshiMart!\n"
			<< "1. To sign as customer and buy items\n"
			<< "2. To update existing customer's items\n"
			<< "3. To print the customer who pays the most\n"
			<< "4. To exit\n"
			<< "Your Choice: ";
		std::cin >> op;

		switch (op)
		{
		case 1:
			int cartOp;
			int storeChoice;
			std::string customerName;
			std::cout << "Enter your name: ";
			std::cin >> customerName;

			Customer newCustomer(customerName);
			abcCustomers[customerName] = newCustomer;

			do
			{
				std::cout << "\nWelcome!\n"
					<< "1. To create a new shopping cart\n"
					<< "2. To exit\n"
					<< "Your Choice: ";
				std::cin >> cartOp;
				if (cartOp == 1)
				{
					std::string cartName;
					std::cout << "Enter the new shopping cart name: ";
					std::cin >> cartName;

					abcCustomers[customerName].createNewShoppingCart(cartName);

					do
					{
						std::cout << "\nSelect the store to buy from:\n"
							<< "1. to buy in Shefa Isaschar (Super Market)\n"
							<< "2. to buy in MagshIKEA (Home products)\n"
							<< "3. to buy in MagshiPharm (Pharm and utils)\n"
							<< "4. to exit\n"
							<< "Your Choice: ";
						std::cin >> storeChoice;


					} while (storeChoice != 4);
				}
			} while (cartOp != 2);

			break;
		default:
			break;
		}
	}
}