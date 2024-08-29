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
Module: Publication
Filename: Publication.cpp
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
#include <iostream>
#include <cstring>
#include <string> 
#include <iomanip>
#include "Publication.h"
#include "Lib.h"

using namespace std;

namespace sdds
{
	Publication::Publication()
	{
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		m_date.setToToday();
	}
	//copy constructor
	Publication::Publication(const Publication& other)
	{
		m_title = nullptr;
		*this = other;
	}
	Publication& Publication::operator=(const Publication& other)
	{
		if (this != &other)
		{
			set(other.m_membership);
			setRef(other.m_libRef);
			strcpy(m_shelfId, other.m_shelfId);
			m_date = other.m_date;


			//allocate memory for the title and copy the content
			if (other.m_title != nullptr)
			{
				delete[] m_title;
				strcpy(m_shelfId, other.m_shelfId);
				m_title = new char[strlen(other.m_title) + 1];
				strcpy(m_title, other.m_title);
			}
		}
		else
			m_title = nullptr;
		return *this;
	}
	Publication::~Publication()
	{
		delete[] m_title;
		m_title = nullptr;
	}
	//Modifiers
	void Publication::set(int member_id)
	{
		m_membership = member_id > 9999 && member_id <= 99999 ? member_id : 0;
	}
	void Publication::setRef(int value)
	{
		m_libRef = value;
	}
	void Publication::resetDate()
	{
		m_date.setToToday();
	}
	//Queries
	char Publication::type()const
	{
		return 'P';
	}
	bool Publication::onLoan()const
	{
		if (m_membership != 0)
		{
			return true;
		}
		return false;
	}
	Date Publication::checkoutDate()const
	{
		return m_date;
	}
	bool Publication::operator==(const char* title)const
	{
		bool p = strstr(m_title, title);

		if (p)
		{
			return true;
		}
		return false;
	}
	Publication::operator const char* ()const
	{
		return m_title;
	}
	int Publication::getRef()const
	{
		return m_libRef;
	}

	//Pure Virtual Functions Implementation
	bool Publication::conIO(ios& io)const
	{
		if (&io == &cin || &io == &cout)
		{
			return true;
		}
		return false;
	}
	ostream& Publication::write(ostream& os) const
	{
		char oldfill = os.fill();
		if (conIO(os))
		{
			os << "| "
				//(justified left and padded with dots for title)
				<< setw(SDDS_SHELF_ID_LEN) << left << setfill(' ') << m_shelfId << " | ";

			if (strlen(m_title) > SDDS_TITLE_WIDTH)  //Print the box that contains only the max Title width
			{
				for (int i = 0; i < SDDS_TITLE_WIDTH; ++i)
				{
					os << m_title[i];
				}
			}
			else
			{
				os.fill('.');
				os << setw(SDDS_TITLE_WIDTH) << left << m_title;
			}
			os << " | ";
			os.fill(oldfill);

			if (m_membership == 0)
			{
				cout << " N/A ";

			}
			else
			{
				os << m_membership;

			}

			os << " | ";
			os << m_date;
			os << " |";

		}
		else
		{
			os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
		}

		return os;
	}
	istream& Publication::read(istream& is)
	{//First, clear all the attributes by freeing the memory and setting everything to their default values.

		if (m_title != nullptr)
			delete[] m_title;
		m_title = nullptr;
		m_shelfId[0] = '\0';
		m_membership = 0;
		m_libRef = -1;
		m_date.setToToday();

		char title[256]{};  // Change the title 256 size instead of capacity of sdds title
		char id[SDDS_SHELF_ID_LEN + 1]{};
		int memberShip = 0;
		int libRef = -1;
		Date date;

		if (conIO(is)) {
			cout << "Shelf No: ";//prompt statment
			//id[0] = '\0';
			is.getline(id, SDDS_SHELF_ID_LEN + 1, '\n');//read the shelf number up to its limit (see Lib.h).
			//if the number is not exactly the length it is supposed to be, set the istr to a fail state manually.
			if (strlen(id) != SDDS_SHELF_ID_LEN) {
				is.setstate(ios::failbit);
			}
			cout << "Title: ";
			is.getline(title, 257, '\n');//read title

			cout << "Date: ";
			is >> date;//read date

			//m_libRef = -1; //FIXED MY PROBLEM
		}
		else {
			is >> libRef;									// Read libRef from input, uisng tab
			is.ignore();
			is.getline(id, SDDS_SHELF_ID_LEN + 1, '\t');	// Read shelfId from input, using tab
			is.getline(title, 257, '\t');	// Read title from input, using tab    // Read line until t with size of 257
			is >> memberShip;								// Read membership from input, using tab
			is.ignore();
			is >> date;										// Read date from input
		}
		//if the date is in an invalid state set the istr to a fail state manually
		if (!date) {

			is.setstate(std::ios::failbit);
		}
		if (is) {//if is valid


			delete[] m_title;
			m_title = nullptr;
			m_title = new char[strlen(title) + 1];//Dynamically store the title into the title attribute
			strcpy(m_title, title);//copy title into m_title
			strcpy(m_shelfId, id);//copy the shelf id into the shelfId attribute
			set(memberShip);//set the membership
			m_date = date;
			setRef(libRef);//set the libRef attribute

		}

		return is;


	}
	Publication::operator bool() const
	{
		if (m_shelfId != nullptr && m_title != nullptr && m_title[0] != '\0' && m_shelfId[0] != '\0')
			return true;
		return false;
	}
}