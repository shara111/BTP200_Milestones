// Final Project 
// PublicationSelector
// File PublicationSelector.h
// Version 1.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
//                    
/////////////////////////////////////////////////////////////////
/* Citation and Sources...
Final Project Milestone 5
Module: Streamable
Filename: Streamable.cpp
Version 1.0
Author	Fardad Soleimanloo
Revision History
-----------------------------------------------------------
Date      August 6, 2023
2023/13/7  Preliminary release
2023/3/7  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/

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