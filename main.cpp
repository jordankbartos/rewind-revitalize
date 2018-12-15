/*******************************************************************************
 * File: main.cpp
 * Author: Andrew Swaim, Michael Stanley, Dan Tonthat, Jordan Bartos
 * Date: 12/15/2018
 * Description: main driver for Rewind Revitalize.
*******************************************************************************/

#include <iostream>		// cout
#include "Journal.hpp"
#include "helperFunctions.hpp"


int main()
{
	/* TESTING AREA */
	Journal* journal = new Journal("sampleLog.log");
	journal->displayEntry(1234567890);
	delete journal;

	char selection;		// To hold user selections.

	// Display the main menu.
	displayIntro();

	/* TODO: Perhaps have an option to login here or somewhere to
	 * prompt for the user password to do the decryption */

	// Display the main menu.
	do {

		selection = validateMenuChoice(displayMainMenu());

		switch (selection) {

		// User selected option 1: enter a new journal.
		case '1':
			// TODO
			break;

		// User selected option 2: show a happy memory.
		case '2':
			// TODO
			break;

		// User selected option 3: show statistics.
		case '3':
			// TODO
			break;

		// User selected option 4: exit. 
		case '4':
			/* This will do nothing and end the do-while loop
			 * to exit the program */
			break;

		// Input validator should prevent default from being reached.
		default:
			std::cout << "\n\nERROR: Something went wrong. "
				<< "Terminating program.\n\n";

			pause();
			return 0;

			break;
		}


	} while (selection != '4');

	// Indicate the program is ending.
	displayOutro();

	// TODO: Be sure to re-encrypt the user's data before exiting!

	pause();
	return 0;
}
