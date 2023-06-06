//I have done all the coding by myself and only copied the code that my professor provided to complete my project milestones.
#ifndef SDDS_NON_PERISHABLE_H
#define SDDS_NON_PERISHABLE_H

#include "Item.h"

namespace sdds
{
    class NonPerishable: public Item
    {
    public:
        char itemType() const;
        std::ostream& write(std::ostream& oStream) const;
    };
}

#endif