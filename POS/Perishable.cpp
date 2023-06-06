//I have done all the coding by myself and only copied the code that my professor provided to complete my project milestones.

#include "Perishable.h"

namespace sdds
{
    char Perishable::itemType() const
    {
        return 'P';
    }

    std::istream& Perishable::read(std::istream& iStream)
    {
        Date expiryDate = Date();
        Item::read(iStream);
        if(*this && iStream)
        {
            expiryDate = expiryDate.dateOnly(true);
            std::cout << "Expiry date (YYYY/MM/DD)" << std::endl << "> ";
            iStream >> expiryDate;
            if(expiryDate)
                this->expiryDate = expiryDate;
            else
                this->errorState = expiryDate.error();
        }

        return iStream;
    }

    std::ostream& Perishable::write(std::ostream& oStream) const
    {
        Item::write(oStream);
        if(*this)
        {
            switch(this->display_Type)
            {
                case POS_LIST:
                    oStream << "  " << this->expiryDate << " |";
                break;

                case POS_FORM:
                {
                    oStream << "Expiry date: " << this->expiryDate << std::endl;
                    oStream << "=============^" << std::endl;
                }
                break;
            }
        }

        return oStream;
    }

    std::ifstream& Perishable::load(std::ifstream& ifStream)
    {
        Date expiryDate = Date();
        Item::load(ifStream);
        if(*this && ifStream)
        {
            expiryDate.dateOnly(true);
            ifStream.ignore();
            ifStream >> expiryDate;
            if(expiryDate)
                this->expiryDate = expiryDate;
            else
                this->errorState = expiryDate.error();
        }

        return ifStream;
    }

    std::ofstream& Perishable::save(std::ofstream& ofStream) const
    {
        Item::save(ofStream);
        if(*this)
            ofStream << "," << this->expiryDate;

        return ofStream;
    }
}