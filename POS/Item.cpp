//I have done all the coding by myself and only copied the code that my professor provided to complete my project milestones.

#include "Item.h"

namespace sdds
{
	Item::Item()
	{
		for (int i = 0; i < MAX_SKU_LEN; i++)
			this->sku[i] = '\0';
		this->name = nullptr;
		this->price = 0;
		this->taxed = false;
		this->_quantity = 0;
		this->display_Type = 1;
		this->errorState = Error();
	}

	Item::~Item()
	{
		delete[] this->name;
		this->name = nullptr;
	}

	Item::Item(const Item& item)
	{
		*this = item;
	}

	Item& Item::operator = (const Item& item)
	{
		int i = 0;
		if (this != &item)
		{
			while (this->sku[i] != '\0' && i < MAX_SKU_LEN)
			{
				this->sku[i] = '\0';
				i++;
			}
			if (strlen(item.sku) > 0)
				strcpy(this->sku, item.sku);

			if (this->name)
			{
				delete[] this->name;
				this->name = nullptr;
			}
			this->name = new char[strlen(item.name) + 1];
			strcpy(this->name, item.name);

			this->price = item.price;
			this->taxed = item.taxed;
			this->_quantity = item._quantity;
			this->display_Type = item.display_Type;
			this->errorState = item.errorState;
		}

		return *this;
	}

	bool Item::operator == (const char* sku)
	{
		bool isEqual = true;
		unsigned int i = 0;

		if (strlen(this->sku) == strlen(sku))
		{
			while (i < strlen(this->sku) && isEqual)
			{
				if (this->sku[i] == sku[i])
					i++;
				else
					isEqual = false;
			}
		}
		return isEqual;
	}

	bool Item::operator > (const Item& item) const
	{
		int compare = strcmp(item.name, this->name);

		return compare > 0 ? true : false;
	}

	int Item::operator += (int quantity)
	{
		if (this->_quantity + quantity <= MAX_STOCK_NUMBER)
			this->_quantity += quantity;
		else
		{
			this->_quantity = MAX_STOCK_NUMBER;
			this->errorState = Error(ERROR_POS_QTY);
		}

		return this->_quantity;
	}

	int Item::operator -= (int quantity)
	{
		if (quantity <= this->_quantity)
			this->_quantity -= quantity;
		else
		{
			this->_quantity = 0;
			this->errorState = Error(ERROR_POS_STOCK);
		}

		return this->_quantity;
  	}

	Item::operator bool() const
	{
		return !this->errorState;
	}

	Item& Item::displayType(int option)
	{
		if (option == POS_LIST || option == POS_FORM)
			this->display_Type = option;

		return *this;
	}

	double Item::cost() const
	{
		return (this->price * (1 + (this->taxed ? TAX : 0)));
	}

	int Item::quantity() const
	{
		return this->_quantity;
	}

	Item& Item::clear()
	{
		this->errorState.clear();
		return *this;
	}

	std::ostream& Item::write(std::ostream& oStream) const
	{
		if (*this)
		{
			switch (display_Type)
			{
			case 1:
			{
				oStream.width(MAX_SKU_LEN);
				oStream.setf(std::ios::left);
				oStream << this->sku << "|";
				if (strlen(this->name) <= 20)
				{
					oStream.width(20);
					oStream << this->name;
				}
				else
				{
					for(int i = 0; i < 20; i++)
						oStream << this->name[i];
				}
				oStream << "|";
				oStream.unsetf(std::ios::left);
				oStream.width(7);
				oStream.setf(std::ios::fixed);
				oStream.precision(2);
				oStream << this->price << "|";
				oStream.width(3);
				oStream << (this->taxed ? " X " : "   ") << "|";
				oStream.width(4);
				oStream << this->quantity() << "|";
				oStream.width(9);
				oStream << (this->cost() * this->_quantity) << "|";
			}
			break;
			case 2:
			{
				oStream.setf(std::ios::right);
				oStream.fill('=');
				oStream.width(14);
				oStream << "v" << std::endl;
				oStream.fill(' ');
				oStream.unsetf(std::ios::right);
				oStream.setf(std::ios::fixed);
				oStream.precision(2);
				oStream.setf(std::ios::left);
				oStream.width(13);
				oStream << "Name:";
				oStream << this->name << std::endl;
				oStream.width(13);
				oStream << "Sku:";
				oStream << this->sku << std::endl;
				oStream.width(13);
				oStream << "Price:";
				oStream << this->price << std::endl;
				oStream.width(13);
				oStream << "Price + tax:";
				if (this->taxed)
					oStream << this->cost() << std::endl;
				else
					oStream << "N/A" << std::endl;
				oStream.width(13);
				oStream << "Stock Qty:";
				oStream << this->quantity() << std::endl;
				oStream.unsetf(std::ios::left);
			}
			break;
			}
		}
		else
			oStream << this->errorState;

		return oStream;
	}

	std::ofstream& Item::save(std::ofstream& ofStream) const
	{
		if (*this)
		{
			ofStream << itemType() << ',';
			ofStream << this->sku << ',';
			ofStream << this->name << ',';
			ofStream.setf(std::ios::fixed);
			ofStream.precision(2);
			ofStream << this->price << ',';
			ofStream << (this->taxed ? 1 : 0) << ',';
			ofStream << this->_quantity;
		}
		else
			std::cerr << this->errorState << std::endl;

		return ofStream;
	}

	std::istream& Item::read(std::istream& iStream)
	{
		bool correctInput = false;
		std::string input;
		std::cout << "Sku" << std::endl << "> ";
		while (!correctInput)
		{
			iStream >> this->sku;
			if (iStream && strlen(this->sku) <= MAX_SKU_LEN)
			{
				correctInput = true;
				this->errorState.clear();
			}
			else
			{
				this->errorState.setErrorMsg(ERROR_POS_SKU);
				std::cout << this->errorState << std::endl << "> ";
			}
		}
		input.clear();
		iStream.clear();
		iStream.ignore(1000, '\n');

		correctInput = false;
		std::cout << "Name" << std::endl << "> ";
		while (!correctInput)
		{
			std::getline(iStream, input, '\n');
			if (iStream && input.length() <= MAX_NAME_LEN)
			{
				correctInput = true;
				if (this->name)
				{
					delete[] this->name;
					this->name = nullptr;
				}
				this->name = new char[input.length() + 1];
				strcpy(this->name, input.c_str());
				this->errorState.clear();
			}
			else
			{
				this->errorState.setErrorMsg(ERROR_POS_NAME);
				std::cout << this->errorState << std::endl << "> ";
			}
		}
		input.clear();
		iStream.clear();

		correctInput = false;
		std::cout << "Price" << std::endl << "> ";
		while (!correctInput)
		{
			iStream >> this->price;
			if (iStream && this->price >= 0)
			{
				correctInput = true;
				this->errorState.clear();
			}
			else
			{
				this->errorState.setErrorMsg(ERROR_POS_PRICE);
				std::cout << this->errorState << std::endl << "> ";
			}
			iStream.clear();
			iStream.ignore(1000, '\n');
		}

		correctInput = false;
		std::cout << "Taxed?" << std::endl;
		std::cout << "(Y)es/(N)o: ";
		while (!correctInput)
		{
			std::getline(iStream, input, '\n');

			if (iStream && input.length() == 1 && (input[0] == 'Y' || input[0] == 'N' || input[0] == 'y' || input[0] == 'n'))
			{
				correctInput = true;
				if (input[0] == 'Y' || input[0] == 'y')
					this->taxed = true;
				else
					this->taxed = false;
				this->errorState.clear();
			}
			else
			{
				this->errorState.setErrorMsg(ERROR_POS_TAX);
				std::cout << "Only 'y' and 'n' are acceptable: ";
			}
		}
		input.clear();
		iStream.clear();

		correctInput = false;
		std::cout << "Quantity" << std::endl << "> ";
		while (!correctInput)
		{
			iStream >> this->_quantity;
			if (iStream && this->_quantity > 0 && this->_quantity <= MAX_STOCK_NUMBER)
			{
				correctInput = true;
				this->errorState.clear();
			}
			else
			{
				this->errorState.setErrorMsg(ERROR_POS_QTY);
				std::cout << this->errorState << std::endl << "> ";
			}
			iStream.clear();
			iStream.ignore(1000, '\n');
		}

		return iStream;
	}

	std::ifstream& Item::load(std::ifstream& ifStream)
	{
		std::string sku = "";
		std::string name = "";
		std::string price = "";
		std::string taxed = "";
		int quantity = 0;
		char delimiter = ',';


		this->errorState.clear();

		std::getline(ifStream, sku, delimiter);
		std::getline(ifStream, name, delimiter);
		std::getline(ifStream, price, delimiter);
		std::getline(ifStream, taxed, delimiter);
		ifStream >> quantity;

		if (ifStream)
		{
			if (sku.length() > 0 && sku.length() <= MAX_SKU_LEN)
			{
				for (unsigned int i = 0; i < sku.length(); i++)
					this->sku[i] = sku[i];
				if (sku.length() < MAX_SKU_LEN)
				{
					for (int i = sku.length(); i < MAX_SKU_LEN; i++)
						this->sku[i] = '\0';
				}
				if (name.length() <= MAX_NAME_LEN)
				{
					if (this->name)
					{
						delete[] this->name;
						this->name = nullptr;
					}
					this->name = new char[name.length() + 1];
					strcpy(this->name, name.c_str());
					if (atof(price.c_str()) >= 0)
					{
						this->price = atof(price.c_str());
						if (taxed == "0" || taxed == "1")
						{
							this->taxed = taxed == "1";
							if (quantity > 0 && quantity <= MAX_STOCK_NUMBER)
								this->_quantity = quantity;
							else
								this->errorState.setErrorMsg(ERROR_POS_QTY);
						}
						else
							this->errorState.setErrorMsg(ERROR_POS_TAX);
					}
					else
						this->errorState.setErrorMsg(ERROR_POS_PRICE);
				}
				else
					this->errorState.setErrorMsg(ERROR_POS_NAME);
			}
			else
				this->errorState.setErrorMsg(ERROR_POS_SKU);
		}
		else
			this->errorState.setErrorMsg(ERROR_POS_EMPTY);

		return ifStream;
	}

	std::ostream& Item::bprint(std::ostream& oStream) const
	{
		oStream << "| ";
		oStream.setf(std::ios::left);
		if (strlen(this->name) <= 20)
		{
			oStream.width(20);
			oStream << this->name;
		}
		else
		{
			for (int i = 0; i < 20; i++)
				oStream << this->name[i];
		}
		oStream << "|";
		oStream.unsetf(std::ios::left);
		oStream.setf(std::ios::fixed);
		oStream.precision(2);
		oStream.width(10);
		oStream << this->cost() << " |";
		oStream.width(5);
		oStream << (this->taxed ? "  T  " : "     ") << "|" << std::endl;

		return oStream;
	}

	double operator += (double& leftOperand, const Item& rightItemOperand)
	{
		return (rightItemOperand.cost() * rightItemOperand.quantity()) + leftOperand;
	}
}