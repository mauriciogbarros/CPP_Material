//I have done all the coding by myself and only copied the codethat my professor provided to complete my project milestones.

#include "Date.h"

namespace sdds
{
    Date::Date()
    {
        this->isDateOnly = false;
        getSystemDate(this->year, this->month, this->day, this->hour, this->minute, this->isDateOnly);
        this->dateValue = uniqueDateValue(year, month, day, hour, minute);
        this->dateError = Error();
    }

    Date::Date(int year, int month, int day)
    {
        this->isDateOnly = true;
        this->dateError = Error();
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = 0;
        this->minute = 0;
        validateDate(this->year, this->month, this->day, this->hour, this->minute, this->isDateOnly);
        this->dateValue = uniqueDateValue(this->year, this->month, this->day, this->hour, this->minute);
    }

    Date::Date(int year, int month, int day, int hour)
    {
        this->isDateOnly = false;
        this->dateError = Error();
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = 0;
        validateDate(this->year, this->month, this->day, this->hour, this->minute, this->isDateOnly);
        this->dateValue = uniqueDateValue(this->year, this->month, this->day, this->hour, this->minute);
    }
    Date::Date(int year, int month, int day, int hour, int minute)
    {
        this->isDateOnly = false;
        this->dateError = Error();
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        validateDate(this->year, this->month, this->day, this->hour, this->minute, this->isDateOnly);
        this->dateValue = uniqueDateValue(this->year, this->month, this->day, this->hour, this->minute);
    }

    void Date::getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly) 
    {
        time_t t = time(NULL);
        tm lt = *localtime(&t);
        day = lt.tm_mday;
        mon = lt.tm_mon + 1;
        year = lt.tm_year + 1900;
        if(dateOnly)
            hour = min = 0;
        else
        {
            hour = lt.tm_hour;
            min = lt.tm_min;
        }
    }

    int Date::uniqueDateValue(int year, int mon, int day, int hour, int min)
    {
        return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
    }

    int Date::daysOfMonth(int year, int month)
    {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = month >= 1 && month <= 12 ? month : 13;
        mon--;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

        bool Date::operator ==(const Date& date) const
        {
            return this->dateValue == date.dateValue;
        }

        bool Date::operator !=(const Date& date) const
        {
            return this->dateValue != date.dateValue;
        }

        bool Date::operator <(const Date& date) const
        {
            return this->dateValue < date.dateValue;
        }

        bool Date::operator >(const Date& date) const
        {
            return this->dateValue > date.dateValue;
        }

        bool Date::operator <=(const Date& date) const
        {
            return this->dateValue <= date.dateValue;
        }

        bool Date::operator >=(const Date& date) const
        {
            return this->dateValue >= date.dateValue;
        }

        Date::operator bool() const
        {
            return !this->dateError;
        }

        Date& Date::dateOnly(const bool isDateOnly)
        {
            this->isDateOnly = isDateOnly;
            if(this->isDateOnly)
            {
                this->hour = 0;
                this->minute = 0;
            }
            return *this;
        }

        const Error& Date::error() const
        {
            return this->dateError;
        }

        std::ostream& Date::display(std::ostream& oStream) const
        {
            if(!*this)
                oStream << dateError << "(";

            oStream << year << "/";
            oStream << std::setw(2) << std::setfill('0') << month;
            oStream << "/" << std::setw(2) << std::setfill('0') << day;
            if (!isDateOnly)
            {
                oStream << ", ";
                oStream << std::setw(2) << std::setfill('0') << hour;
                oStream << ":" << std::setw(2) << std::setfill('0') << minute;
            }

            if(!*this)
                oStream << ")";
            oStream << std::setfill(' ');
            return oStream;
        }

        void Date::read(std::istream& iStream)
        {
            this->year = 0;
            this->month = 0;
            this->day = 0;
            this->hour = 0;
            this->minute = 0;
            this->isDateOnly = false;
            this->dateValue = uniqueDateValue(this->year, this->month, this->day, this->hour, this->minute);
            this->dateError.clear();

            iStream >> this->year;
            if (iStream.fail())
                this->dateError.setErrorMsg("Cannot read year entry");
            else
            {
                iStream.ignore();
                iStream >> this->month;
                if (iStream.fail())
                    this->dateError.setErrorMsg("Cannot read month entry");
                else
                {
                    iStream.ignore();
                    iStream >> this->day;
                    if (iStream.fail())
                        this->dateError.setErrorMsg("Cannot read day entry");
                    else
                    {
                        if (iStream.peek() != '\n' && !iStream.eof())
                        {
                            iStream.ignore();
                            iStream >> this->hour;
                            if (iStream.fail())
                                this->dateError.setErrorMsg("Cannot read hour entry");
                            else
                            {
                                iStream.ignore();
                                iStream >> this->minute;
                                if (iStream.fail())
                                    this->dateError.setErrorMsg("Cannot read minute entry");
                            }
                        }
                        else
                            this->isDateOnly = true;
                    }
                }
            }

            if (*this)
            {
                this->dateValue = uniqueDateValue(this->year, this->month, this->day, this->hour, this->minute);
                validateDate(this->year, this->month, this->day, this->hour, this->minute, this->isDateOnly);
            }
        }

        void Date::validateDate(int& year, int& month, int& day, int& hour, int& minute, bool dateOnly)
        {
            this->dateError.clear();
            if (year < MIN_YEAR || year > MAX_YEAR)
                this->dateError.setErrorMsg("Invalid Year");
            else
            {
                if (month < 1 || month > 12)
                    this->dateError.setErrorMsg("Invalid Month");
                else
                {
                    if (day < 1 || day > daysOfMonth(year, month))
                        this->dateError.setErrorMsg("Invalid Day");
                    else
                    {
                        if (!dateOnly)
                        {
                            if (hour < 0 || hour > 23)
                                this->dateError.setErrorMsg("Invalid Hour");
                            else
                            {
                                if (minute < 0 || minute > 59)
                                    this->dateError.setErrorMsg("Invlid Minute");
                            }
                        }

                    }
                }
            }
        }

        std::ostream& operator << (std::ostream& oStream, const Date& date)
        {
            return date.display(oStream);
        }

        std::istream& operator >> (std::istream& iStream, Date& date)
        {
            date.read(iStream);
            return iStream;
        }
}