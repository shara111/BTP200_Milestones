#define _CRT_SECURE_NO_WARNINGS
#include "Streamable.h"

using namespace std;

namespace sdds
{
	ostream& operator<<(std::ostream& os, const Streamable& obj)
	{
		if (obj)
		{
			obj.write(os);
		}
		return os;
	}
	istream& operator>>(std::istream& is, Streamable& obj)
	{
		obj.read(is);
		return is;
	}
}