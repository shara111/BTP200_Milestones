/* Citation and Sources...
Final Project Milestone 2
Module: LibApp
Filename: LibApp.cpp
Version 1.0
Author	Fardad Soleimanloo
Revision History
-----------------------------------------------------------
Date      July 18, 2023
2023/13/7  Preliminary release
2023/3/7  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------
*/


#include <iostream>
#include "LibApp.h"
using namespace std;

namespace sdds {
	//Constructor
	LibApp::LibApp()
		: m_changed(false),
		m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?")
	{
		m_mainMenu << "Add New Publication"
			<< "Remove Publication"
			<< "Checkout publication from library"
			<< "Return publication to library";

		m_exitMenu << "Save changes and exit"
			<< "Cancel and go back to the main menu";

		load(); 
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
	}
	void LibApp::save()
	{
		cout << "Saving Data" << endl;
	}
	void LibApp::search()
	{
		cout << "Searching for publication" << endl;
	}
	void LibApp::returnPub()
	{
		search();
		cout << "Returning publication" << endl;
		cout << "Publication returned\n" << endl;
		m_changed = true;
	}
	void LibApp::newPublication()
	{
		cout << "Adding new publication to library" << endl;
		if (confirm("Add this publication to library?"))
		{
			m_changed = true;
			cout << "Publication added" << endl;
		}
	}
	void LibApp::removePublication()
	{
		cout << "Removing publication from library" << endl;
		search();
		if (confirm("Remove this publication from the library?"))
		{
			m_changed = true;
			cout << "Publication removed\n" << endl;
		}
	}
	void LibApp::checkOutPub()
	{
		search();
		if (confirm("Check out publication?"))
		{
			m_changed = true;
			cout << "Publication checked out\n" << endl;


		}
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


}