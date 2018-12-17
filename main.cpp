/*******************************************************************************
 * File: main.cpp
 * Author: Andrew Swaim, Michael Stanley, Dan Tonthat, Jordan Bartos
 * Date: 12/15/2018
 * Description: main driver for Rewind Revitalize.
*******************************************************************************/

#include "Journal.hpp"
#include "helperFunctions.hpp"

using std::cin;
using std::cout;
using std::string;
using std::ofstream;

int main()
{
	srand(time(0));
	char selection;			// To hold user menu selections.
	string username;
	string password;
	bool newUser = false;
	bool validPassword = false;

	// For writing the username and password to a file if the user
	// wants to create a new account.
	ofstream ofs;

	// Display the main menu.
	clearTheScreen();
	displayIntro();
	pause();

	// Create the journal.
	Journal* journal = new Journal();

	// This do-while loop handles the username.
	do {

		// Prompt for username.
		do {
			clearTheScreen();
			cout << "\nPlease enter your username: ";
			getline(cin, username);
			if(!validateInput(username,20))
			{
				std::cout << "Username must be between 1 and 20 characters " <<
							"and must contain only alphanumeric characters\n" <<
							"or \'-\' or \'_\'." << std::endl;
				pause();
			}

		} while(!validateInput(username,20));


		/* Check if the username exists by determining is there is
		 * a "username.txt" file. */
		selection = 'y';
		if (!journal->userNameExists(username)) {

			selection = ' ';

			/* If not found, prompt to make a new account.
			 * If user answer no, loop again to prompt for username. */
			std::cout << "\nUsername not found. "
				<< "Do you want to make a new account (Y/N)? ";

			// answer will be 'y' or 'n'
			selection = getYesNoAnswer();

			/* If yes openUserFile should handle creating a new log file
			 * with the given username */
			if (selection == 'y') {

				// Open a file with the name of the username.
				string filename = username + ".log";
				ofs.open(filename.c_str());

				// Add the username as the first line.
				ofs << username << "\n";

				newUser = true;
			}
		}

	} while (selection != 'y');

	// This do-while loop handles the user password.
	do {

		// Check if the user is a new user.
		if (newUser) {

			string password2;	// To hold the user re-entered password.
			do {

				// Have the user create a new password for their account.
				clearTheScreen();
				cout << "\nPlease enter a new password: ";
				getline(cin, password);

				// Have the user confirm the new password.
				cout << "\nPlease confirm your password: ";
				getline(cin, password2);

				// Check if the two passwords match.
				if (password != password2) {

					cout << "\nSorry, those passwords do not match.";
				}
				else {

					// Write the password to the file as the second line
					// and close the file.
					ofs << password << "\n";
					ofs.close();
					validPassword = true;
				}

			} while (!validPassword);
		}
		// If the user is not a new user...
		else {

			// Prompt for the user password.
			cout << "\nPlease enter your password: ";
			getline(std::cin, password);

			/* Check if the password is valid. This should get the
			 * decrypted password from the log file, attempt to decrypt
			 * with the given password, and then validate that they are
			 * the same. */
			if (journal->validatePassword(username, password)) {

				validPassword = true;
			}
			else {

				cout << "\nThat is not a valid password.\n";
			}
		}

	} while (!validPassword);

	// If password was successful, decrypt the journal entries.
	journal->decryptAndLoad(password);
	int searcher;
	// Display the main menu.
	do {

		// Display main menu and get user choice.
		clearTheScreen();
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
			clearTheScreen();
			cout << "\n\nLIFETIME STATISTICS\n"
				<< "\nNumber of Entries: " << journal->getNumEntries()
				<< "\nAverage Word Count: " << journal->getAvgWordCount()
				<< "\nLongest Entry: " << journal->getLongestPost()
				<< "\nShortest Entry: " << journal->getShortestPost()
				<< "\nAverage Mood: " << journal->getAvgMood()
				<< "\n";
			pause();
			break;

			//Search and display entry
		case '4':
				clearTheScreen();
				cout << "\n\nEnter the date of the entry/entries you wish to view" << endl;
				cout << "Use the format mmddyyyy" << endl;
				searcher = validateIntRange(0, 99999999);
				journal->displayEntry(searcher);
				break;

		// User selected option 5: exit.
		case '5':
			/* This will do nothing and end the do-while loop
			 * to exit the program */
			break;

		/* EXCEPTION HANDLING:
		 * Input validator should prevent 'default' from being reached. */
		default:
			cout << "\n\nERROR: Something went wrong. "
				<< "Terminating program.\n\n";
			pause();
			return 0;
			break;
		}

	} while (selection != '5');

	// Indicate the program is ending.
	displayOutro();

	// Be sure to re-encrypt the user's data before exiting!
	journal->encryptAndSave(password);
	delete journal;

	pause();
	return 0;
}
