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
	/*journal->displayEntry(1234567890);
	journal->encryptAndSave();*/

	char selection;			// To hold user menu selections.
	std::string* password = new std::string();
	bool validPassword = false;

	// Display the main menu.
	//displayIntro();

	// Create the journal.
	Journal* journal = new Journal("sampleLog.log");
	journal->addEntry();

/*
	do {

		// Prompt for the user password to do the decryption.
		std::cout << "\nPlease enter your password: ";
		getline(std::cin, *password);

		// Validate password.
		if (*password == *journal->getPassword()) {

			validPassword = true;
		}
		else {

			std::cout << "\nThat is not a valid password.\n";
		}

	} while (!validPassword);

	// If password was successful, decrypt the journal entries.
	journal->decryptAndLoad();

	// Display the main menu.
	do {

		// Display main menu and get user choice.
		selection = validateMenuChoice(displayMainMenu());

		switch (selection) {

		// User selected option 1: enter a new journal.
		case '1':

			journal->addEntry();
			break;

		// User selected option 2: show a happy memory.
		case '2':

			journal->rewind();
			break;

		// User selected option 3: show statistics.
		case '3':

			// TODO: ANY OTHER STATS TO SHOW??
			std::cout << "\n\nLIFETIME STATISTICS\n"
				<< "\nNumber of Entries: " << journal->getNumEntries()
				<< "\nAverage Word Count: " << journal->getAvgWordCount()
				<< "\nLongest Entry: " << journal->getLongestPost()
				<< "\nShortest Entry: " << journal->getShortestPost()
				<< "\nAverage Mood: " // << journal->getAvgMood() ??
				<< "\n";
			break;

		// User selected option 4: exit.
		case '4':
			/* This will do nothing and end the do-while loop
			 * to exit the program */
/*
			break;

		/* EXCEPTION HANDLING:
		 * Input validator should prevent 'default' from being reached. */
/*
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

	// Be sure to re-encrypt the user's data before exiting!
	journal->encryptAndSave(); */
	delete journal;

	pause();

	return 0;
}
