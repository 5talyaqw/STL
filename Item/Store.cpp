#include "Store.h"
#include <iterator>
#include <fstream>
#include <sstream>
#include <algorithm>

Store::Store(std::string storeName, std::string inventoryFileName) : _storeName(storeName)
{
	getInventoryFromFile(inventoryFileName);
}
std::string Store::getName() const
{
	return _storeName;
}

std::string Store::getSortedProductList(SortingCriteria sortingCritieria) const
{
	std::deque<Item> sortedProducts = _products;
	switch (sortingCritieria)
	{
	case CATEGORY:
		std::sort(sortedProducts.begin(), sortedProducts.end(), CategoryComparator);
		break;
	case NAME:
		std::sort(sortedProducts.begin(), sortedProducts.end(), NameComparator);
		break;
	case PRICE:
		std::sort(sortedProducts.begin(), sortedProducts.end(), PriceComparator);
		break;
	case SERIAL:
		std::sort(sortedProducts.begin(), sortedProducts.end(), SerialComparator);
		break;
	default:
		throw std::invalid_argument("Invalid sorting criteria");
	}
	std::ostringstream oss;
	for (auto it = sortedProducts.begin();it != sortedProducts.end(); it++)
	{
		oss << *it << "\n";
	}
	return oss.str();
}

std::string Store::getProductListFilteredByCategory(ItemCategory category) const
{
	std::ostringstream oss;
	for (auto it = _products.begin();it != _products.end(); ++it)
	{
		if (it->getCategory() == category)
		{
			oss << *it << "\n";
		}
	}
	return oss.str();
}

Item Store::operator[](const int itemNumber) const
{
	if (itemNumber < 0 || itemNumber >= _products.size())
	{
		throw std::invalid_argument("index out of bonds");

	}
	return _products[itemNumber];
}

void Store::getInventoryFromFile(const std::string inventoryFileName)
{
	// This function reads a CSV file into the object inventory (std::deque<Item>)

	std::deque<std::deque<std::string>> content;	// the entire file as strings
	std::deque<std::string> row;					// a row in the file as string
	std::string line, word;

	std::fstream file(inventoryFileName, std::ios::in);		// openning the csv file for read
	if (file.is_open())
	{
		while (std::getline(file, line))		// reading line by line
		{
			row.clear();

			std::stringstream str(line);		// adding the line to a std::stringstream

			while (std::getline(str, word, ','))	// reading each word seperated by ','
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
	{
		std::cerr << "Could not open the file " << inventoryFileName << "\n" << std::endl;
		throw std::invalid_argument("Could not open the file " + inventoryFileName);
	}

	/* Indexes
		0 --- Item's Name
		1 --- Item's Serial
		2 --- Item's Unit Price
		3 --- Item's Category (int)
	*/

	for (int i = 1; i < content.size(); i++)
	{
		std::string itemName = content[i][0];
		std::string itemSerial = content[i][1];
		double itemPrice = strtod(content[i][2].c_str(), nullptr);
		ItemCategory itemCategory = ItemCategory(stoi(content[i][3]));
		this->_products.push_back(Item(itemName, itemSerial, itemPrice, itemCategory));
	}

	// To print the content remove the comments:
	// for (int i = 0; i < content.size(); i++)
	//{
	//	for (int j = 0; j < content[i].size(); j++)
	//	{
	//		std::cout << content[i][j] << " ";
	//	}
	//	std::cout << "\n";
	//}

}

std::ostream& operator<<(std::ostream& os, const Store& store)
{
	os << "store name: " << store.getName() << "\n";
	os<< "Products:\n";
	
	std::copy(store._products.begin(), store._products.end(), std::ostream_iterator<Item>(os, "\n"));

	return os;
}
