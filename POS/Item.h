//I have done all the coding by myself and only copied the code that my professor provided to complete my project milestones.
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include "POS.h"
#include "PosIO.h"
#include "Error.h"

namespace sdds
{
	class Item : public PosIO
	{
	private:
		char* name = nullptr;				// up to MAX_NAME_LEN
		char sku[MAX_SKU_LEN] = { '\0' };
		double price = 0;
		bool taxed = false;
		int _quantity = 0;

	protected:
		int display_Type = 1;				// either POS_LIST(1) or POS_FORM(2)
		Error errorState = Error();

	public:
		Item();
		~Item();
		Item(const Item& item);
		Item& operator = (const Item& item);
		bool operator == (const char* sku);
		bool operator > (const Item& item) const;
		int operator += (int quantity);
		int operator -= (int quantity);
		operator bool() const;
		virtual char itemType() const = 0;
		Item& displayType(int option);
		double cost() const;
		int quantity() const;
		Item& clear();
		std::ostream& write(std::ostream& oStream) const;
		std::ofstream& save(std::ofstream& ofStream) const;
		std::istream& read(std::istream& iStream);
		std::ifstream& load(std::ifstream& ifStream);
		std::ostream& bprint(std::ostream& oStream) const;
	};

	// Helper methods
	double operator += (double& leftOperand, const Item& rightItemOperand);
}
#endif // !SDDS_ITEM_H
