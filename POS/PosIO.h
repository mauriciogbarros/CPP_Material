//I have done all the coding by myself and only copied the code that my professor provided to complete my project milestones.
#ifndef SDDS_POSIO_H
#define SDDS_POSIO_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

namespace sdds
{
	class PosIO
	{
	public:
		virtual std::ostream& write(std::ostream& oStream) const = 0;
		virtual std::ofstream& save(std::ofstream& ofStream) const = 0;
		virtual std::istream& read(std::istream& iStream) = 0;
		virtual std::ifstream& load(std::ifstream& ifStream) = 0;
		virtual ~PosIO();
	};

	std::ostream& operator << (std::ostream& oStream, PosIO& posIO);
	std::ofstream& operator << (std::ofstream& ofStream, PosIO& posIO);
	std::istream& operator >> (std::istream& iStream, PosIO& posIO);
	std::ifstream& operator >> (std::ifstream& ifStream, PosIO& posIO);
}
#endif // SDDS_POSIO_H
