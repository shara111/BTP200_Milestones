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
Filename: Streamable.h
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

#ifndef  SDDS_STREAMABLE_H_
#define SDDS_STREAMABLE_H_

#include <iostream>
using namespace std;
namespace sdds
{
	class Streamable
	{
	public:
		/*This method is not capable of modifying the Streamable object.write receivesand returns a reference of an ostream object.
		Functions overriding this function will write into an ostream object.*/
		virtual ostream& write(std::ostream& os) const = 0;
		/*read receivesand returns a reference of an istream object.
		Functions overriding this function will read from an istream object.*/
		virtual istream& read(std::istream& is) = 0;
		/*This method is not capable of modifying the Streamable object.conIo receives a reference of an ios objectand returns a Boolean.
		Functions overriding this function will determine if the incoming ios object is a console IO object or not.*/
		virtual bool conIO(std::ios& io) const = 0;
		/*Boolean conversion operator overload (pure virtual)
		Boolean conversion overloads of this method will return if the Streamable object is in a valid state or not.*/
		virtual operator bool() const = 0;
		virtual ~Streamable() {}
	};
	ostream& operator<<(std::ostream& os, const Streamable& obj);
	istream& operator>>(std::istream& is, Streamable& obj);

}

#endif // ! SDDS_STREAMABLE_H_
