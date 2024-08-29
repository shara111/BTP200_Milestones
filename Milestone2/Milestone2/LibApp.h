/* Citation and Sources...
Final Project Milestone 2
Module: LibApp
Filename: LibApp.h
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

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
namespace sdds {
	class LibApp 
	{
		bool m_changed; //A flag to keep track of changes made to the application data. 
		//This flag is initially set to false. If any change is made to the data of the application, this flag is set to true.
		Menu m_mainMenu;
		Menu m_exitMenu;

		bool confirm(const char* message); //Instantiate a Menu in this functionand initialize it with the message argument.
		void load();  // prints: "Loading Data"<NEWLINE>
		void save();  // prints: "Saving Data"<NEWLINE>
		void search();  // prints: "Searching for publication"<NEWLINE>

		void returnPub();  /*  Calls the search() method.
							   prints "Returning publication"<NEWLINE>
							   prints "Publication returned"<NEWLINE>
							   sets m_changed to true;
						   */

		//Methods with confirmation
		void newPublication(); //prints "Adding new publication to library"+newline
		void removePublication(); //prints "Removing publication from library"+newline
		void checkOutPub(); //calls the search method
		//calls the confirm method with Check out publication ? "

	public:
		//Constructor
		LibApp();
		//the run method
		void run();
	};
}
#endif // !SDDS_LIBAPP_H


