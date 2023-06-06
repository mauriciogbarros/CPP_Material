//I have done all the coding by myself and only copied the code that my professor provided to complete my project milestones.
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"

namespace sdds
{
    class Perishable: public Item
    {
    private:
        Date expiryDate = Date();

    public:
        char itemType() const;
        std::istream& read(std::istream& iStream);
        std::ostream& write(std::ostream& oStream) const;
        std::ifstream& load(std::ifstream& ifStream);
        std::ofstream& save(std::ofstream& ofStream) const;
    };
}

#endif