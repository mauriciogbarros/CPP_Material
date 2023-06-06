//I have done all the coding by myself and only copied the code that my professor provided to complete my project milestones.

#include "NonPerishable.h"

namespace sdds
{
    char NonPerishable::itemType() const
    {
        return 'N';
    }

    std::ostream& NonPerishable::write(std::ostream& oStream) const
    {
        Item::write(oStream);
        if(*this)
        {
            switch(this->display_Type)
            {
                case POS_LIST:
                    oStream << "     N / A   |";
                break;
                
                case POS_FORM:
                    oStream << "=============^" << std::endl;   
                break;
            }
        }
        return oStream;
    }
}