//I have done all the coding by myself and only copied the code that my professor provided to complete my project milestones.

#include "PosIO.h"

namespace sdds
{
	PosIO::~PosIO() {};

	std::ostream& operator << (std::ostream& oStream, PosIO& posIO)
	{
		return posIO.write(oStream);
	}

	std::ofstream& operator << (std::ofstream& ofStream, PosIO& posIO)
	{
		return posIO.save(ofStream);
	}

	std::istream& operator >> (std::istream& iStream, PosIO& posIO)
	{
		return posIO.read(iStream);
	}

	std::ifstream& operator >> (std::ifstream& ifStream, PosIO& posIO)
	{
		return posIO.load(ifStream);
	}
}