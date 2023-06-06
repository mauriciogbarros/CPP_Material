//I have done all the coding by myself and only copied the codethat my professor provided to complete my project milestones.
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <ctime>
#include "Error.h"
#include "POS.h"

namespace sdds
{
    class Date
    {
    private:
        int year = 0;
        int month = 0;
        int day = 0;
        int hour = 0;
        int minute = 0;
        int dateValue = 0;
        bool isDateOnly = false;
        Error dateError = Error();
    
    public:
        // Constructors
        Date();
        Date(int year, int month, int day);
        Date(int year, int month, int day, int hour);
        Date(int year, int month, int day, int hour, int minute);

        // Already implemented utility functions
        void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
        int uniqueDateValue(int year, int mon, int day, int hour, int min);
        int daysOfMonth(int year, int month);

        // Overloaded operators
        bool operator ==(const Date& date) const;
        bool operator !=(const Date& date) const;
        bool operator <(const Date& date) const;
        bool operator >(const Date& date) const;
        bool operator <=(const Date& date) const;
        bool operator >=(const Date& date) const;
        operator bool() const;

        // Member functions
        Date& dateOnly(const bool isDateOnly);
        const Error& error() const;
        std::ostream& display(std::ostream& oStream) const;
        void read(std::istream& iStream);
        void validateDate(int& year, int& month, int& day, int& hour, int& minute, bool dateOnly);
    };

    // Helper methods
    std::ostream& operator <<(std::ostream& oStream, const Date& date);
    std::istream& operator >>(std::istream& iStream, Date& date);
}

#endif