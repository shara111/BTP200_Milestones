/* Citation and Sources...
Final Project Milestone 5
Module: LibApp
Filename: LibApp.cpp
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
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Publication.h"
#include "Book.h"
#include "LibApp.h"
#include "PublicationSelector.h"
#include "Date.h"
#include "Lib.h"
#include "Menu.h"
#include "Utils.h"
#include "Streamable.h"
using namespace std;

namespace sdds {
	//Constructor
	LibApp::LibApp(const char* filename)
		:
		m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?"),
		m_nolp(0),
		m_pubTypeMenu("Choose the type of publication:")
	{
		this->m_changed = false;

		if (filename)
		{
			strcpy(this->m_filename, filename);
		}

		this->m_mainMenu << "Add New Publication"
			<< "Remove Publication"
			<< "Checkout publication from library"
			<< "Return publication to library";

		m_exitMenu << "Save changes and exit"
			<< "Cancel and go back to the main menu";

		this->m_pubTypeMenu << "Book";
		this->m_pubTypeMenu << "Publication";
		load();

		//MS5
	}
	bool LibApp::confirm(const char* message)
	{
		Menu confirmMenu(message); //create an instantiate menu in this function and initialize it with the message argument
		confirmMenu << "Yes";

		if (confirmMenu.run() == 1)
		{
			return true;
		}
		cout << "\n";
		return false;
	}
	void LibApp::load()
	{
		cout << "Loading Data" << endl;

		ifstream file(this->m_filename); //opening the file using ifstream 

		/*if (!file)
		{
			cout << "Error opening file: " << m_filename << endl;
			return;
		}*/
		char kind;

		//The function enters a loop that reads data from the file until the end of the file is reached.
		//it reads one character at a time to determine the type of publication :
		for (int i = 0; i < SDDS_LIBRARY_CAPACITY and file;i++)
		{
			file >> kind;
			file.ignore();

			if (file)
			{
				if (kind == 'P')
				{
					m_ppa[i] = new Publication;
				}
				else if (kind == 'B')
				{
					m_ppa[i] = new Book;
				}
				if (m_ppa[i])
				{
					file >> *m_ppa[i];
					m_nolp++;
					m_llrn = m_ppa[i]->getRef();
				}

			}
		}
	}
	void LibApp::save()
	{
		cout << "Saving Data" << endl;
		ofstream file(this->m_filename); //opening the file

		if (!file)
		{
			cout << "Error opening file: " << m_filename << endl;
			return;
		}
		for (int i = 0; i < m_nolp; i++)
		{
			if (m_ppa[i]->getRef() != 0)
			{
				file << *m_ppa[i] << endl;
			}
		}
		//cout << "Saving Data" << endl;
	}
	int LibApp::search(int mode)
	{
		PublicationSelector that("Select one of the following found matches:");
		int typechoice = m_pubTypeMenu.run();
		char s;

		if (typechoice == 2)
		{
			s = 'P';
		}
		else if (typechoice == 1)
		{
			s = 'B';
		}
		else
		{
			cout << "Aborted!" << endl;
		}

		char title[256]{};
		cout << "Publication Title: ";
		cin.getline(title, 256);

		if (mode == 1)
		{

			//Go through all the publications in the PPAand base...
			//more left
			for (int i = 0; i < m_nolp; i++)
			{
				if (m_ppa[i]->getRef() != 0 and
					m_ppa[i]->operator==(title) and
					m_ppa[i]->type() == s)
				{
					that << m_ppa[i];
				}
			}
		}
		if (mode == 2)
		{
			for (int i = 0; i < m_nolp; i++)
			{
				if (m_ppa[i]->getRef() != 0 and
					m_ppa[i]->operator==(title) and
					m_ppa[i]->type() == s and
					m_ppa[i]->onLoan())
				{
					that << m_ppa[i];
				}
			}
		}
		if (mode == 3)
		{
			for (int i = 0; i < m_nolp; i++)
			{
				if (m_ppa[i]->getRef() != 0 and
					m_ppa[i]->operator==(title) and
					m_ppa[i]->type() == s and

					//fixed my error
					!m_ppa[i]->onLoan())
				{
					that << m_ppa[i];
				}
			}
		}
		int libref = 0;

		if (that)
		{
			that.sort();

			libref = that.run();
			if (libref > 0)
			{
				cout << *getPub(libref) << endl;
			}
			else
			{
				cout << "Aborted!" << endl;
			}
		}
		else
		{
			cout << "No matches found!" << endl;
		}
		return libref;
	}
	Publication* LibApp::getPub(int libRef)
	{
		Publication* pub = nullptr;
		for (int i = 0; i < m_nolp; i++)
		{
			//if match is found
			if ( m_ppa[i]->getRef() == libRef)
			{
				pub = m_ppa[i];
			}
		}
		return pub;
	}
	void LibApp::returnPub()
	{
		cout << "Return publication to the library" << endl;
		int libref = search(2);
		if (libref > 0)
		{
			if (confirm("Return Publication?"))
			{
				int day = Date() - getPub(libref)->checkoutDate();

				if (day > SDDS_MAX_LOAN_DAYS)
				{
					double penalty = (day - SDDS_MAX_LOAN_DAYS) * 0.5;
					cout << fixed << setprecision(2) << "Please pay $" << penalty << " penalty for being " << (day - SDDS_MAX_LOAN_DAYS) << " days late!" << endl;
				}

				getPub(libref)->set(0);  //membership number of the publication
				m_changed = true;
			}
			cout << "Publication returned" << endl;
		}
		cout << endl;
	}
	void LibApp::newPublication()
	{
		bool ok = false;

		if (m_nolp == SDDS_LIBRARY_CAPACITY)
		{
			cout << "Library is at its maximum capacity!" << endl;
			ok = true;
		}
		if (!ok)
		{
			cout << "Adding new publication to the library" << endl;
			int typeChoice = m_pubTypeMenu.run();
			Publication* that = nullptr;

			if (typeChoice == 0)
			{
				cout << "Aborted!" << endl;
				ok = true;
			}
			else if (typeChoice == 1)
			{
				that = new Book;
				cin >> *that;
			}
			else if (typeChoice == 2)
			{
				that = new Publication;
				cin >> *that;
			}

			if (cin.fail())
			{
				cin.ignore(1000, '\n');
				cin.clear();
				cout << "Aborted!" << endl;
				ok = true;
			}
			else
			{
				if (!ok and confirm("Add this publication to the library?"))
				{
					if (*that)
					{
						m_llrn++;
						that->setRef(m_llrn);
						m_ppa[m_nolp] = that;
						m_nolp++;
						m_changed = true;
						cout << "Publication added" << endl;
					}
					else
					{
						cout << "Failed to add publication!" << endl;
						delete that;
					}
				}
			}
		}
		cout << endl;
	}
	void LibApp::removePublication()
	{
		cout << "Removing publication from the library" << endl;
		int libref = search(1);
		if (libref)
		{
			if (confirm("Remove this publication from the library?"))
			{
				getPub(libref)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl;
			}
		}
		cout << endl;
	}
	void LibApp::checkOutPub()
	{
		cout << "Checkout publication from the library" << endl;

		int libref = search(3);
		if (libref)
		{
			if (confirm("Check out publication?"))
			{
				cout << "Enter Membership number: ";
				int memberId = 0;
				bool ok = false;

				while(!ok) 
				{
					cin >> memberId;
					if (!cin or memberId < 10000 or memberId > 99999) {
						std::cout << "Invalid membership number, try again: ";
						cin.clear();
						cin.ignore(3000, '\n');
					}
					else
					{
						ok = true;
					}
				} 

				//while (memberId < 10000 || memberId > 99999);

				// Find the selected publication and update its membership number
				 // (HAVE NOT DONE) set the membership number of the selected publication the integer value.
				getPub(libref)->set(memberId);
				m_changed = true;
				cout << "Publication checked out" << endl;
			}
		}
		cout << endl;
	}
	//The run Method
	void LibApp::run()
	{
		while (true) //to repeatedly display and process the menu until the user chooses to exit
		{
			int selection = m_mainMenu.run();

			if (selection == 0)
			{
				if (!m_changed)
				{
					cout << "\n";
					cout << "-------------------------------------------" << endl;
					cout << "Thanks for using Seneca Library Application" << endl;
					break;
				}
				else
				{
					int exitSelection = m_exitMenu.run();
					if (exitSelection == 1)
					{
						save();
						cout << "\n";
						cout << "-------------------------------------------" << endl;
						cout << "Thanks for using Seneca Library Application" << endl;
						break;
					}
					else if (exitSelection == 2)
					{
						cout << "\n";
						continue;
					}
					else
					{
						if (confirm("This will discard all the changes are you sure?"))
						{
							cout << "\n";
							cout << "-------------------------------------------" << endl;
							cout << "Thanks for using Seneca Library Application" << endl;
							break;
						}
						else
						{
							continue;
						}

					}
				}
			}
			else if (selection == 1)
			{
				newPublication();
			}
			else if (selection == 2)
			{
				removePublication();
			}
			else if (selection == 3)
			{
				checkOutPub();
			}
			else if (selection == 4)
			{
				returnPub();
			}
		}
	}
	LibApp::~LibApp()
	{
		for (int i = 0; i < m_nolp; i++)
		{
			delete m_ppa[i];
		}
	}


}