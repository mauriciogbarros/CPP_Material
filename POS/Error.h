//I have done all the coding by myself and only copied the codethat my professor provided to complete my project milestones.
#ifndef SDDS_ERROR_H
#define SDDS_ERROR_H
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>

namespace sdds
{
    class Error
    {
    private:
        char* msg = nullptr;

    public:
        // Constructors
        Error();
        Error(const char* msg);
        Error(const Error& error);

        // Member functions
        std::ostream& getErrorMsg(std::ostream& oStream) const;
        void setErrorMsg(const char* msg);
        Error& clear();

        // Operators
        Error& operator =(const Error& error);
        operator bool() const;

        // Destructor
        ~Error();
    };

    // Helper functions
    std::ostream& operator <<(std::ostream& oStream, const Error& error);
}

#endif