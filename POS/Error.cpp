//I have done all the coding by myself and only copied the codethat my professor provided to complete my project milestones.
#include "Error.h"

namespace sdds
{
    Error::Error()
    {
        this->msg = nullptr;
    }

    Error::Error(const char* msg)
    {
        if (msg != nullptr && strlen(msg) > 0)
        {
            this->msg = new char[strlen(msg) + 1];
            strcpy(this->msg, msg);
        }
    }

    Error::Error(const Error& error)
    {
        if (error)
            *this = error;
    }

    Error& Error::operator=(const Error& error)
    {
        if (this != &error)
        {
            if (error)
            {
                if (this)
                    delete[] this->msg;
                this->msg = nullptr;
                this->msg = new char[strlen(error.msg) + 1];
                strcpy(this->msg, error.msg);
            }
        }

        return *this;
    }

    std::ostream& Error::getErrorMsg(std::ostream& oStream) const
    {
        if (*this)
            oStream << this->msg;
        return oStream;
    }

    void Error::setErrorMsg(const char* msg)
    {
        if (msg != nullptr)
        {
            if (*this)
            {
                delete[] this->msg;
                this->msg = nullptr;
            }
            this->msg = new char[strlen(msg) + 1];
            strcpy(this->msg, msg);
        }
    }

    Error& Error::clear()
    {
        if (*this)
        {
            delete[] this->msg;
            this->msg = nullptr;
        }
        return *this;
    }

    Error::operator bool() const
    {
        return this->msg != nullptr;
    }

    Error::~Error()
    {
        if (*this)
        {
            delete[] this->msg;
            this->msg = nullptr;
        }
    }

    std::ostream& operator <<(std::ostream& oStream, const Error& error)
    {
        return error.getErrorMsg(oStream);
    }
}