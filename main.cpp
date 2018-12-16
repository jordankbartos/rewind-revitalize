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
	char selection;			// To hold user menu selections.
	string username;
	string password;
	bool newUser = false;
	bool validPassword = false;

	// For writing the username and password to a file if the user
	// wants to create a new account.
	ofstream ofs;

	// Display the main menu.
	displayIntro();

	// Create the journal.
	Journal* journal = new Journal();

	// This do-while loop handles the username.
	do {

		// Prompt for username.
		cout << "\nPlease enter your username: ";
		getline(cin, username);

		/* Check if the username exists by determining is there is 
		 * a "username.txt" file. */
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

	} while (selection != 'n');

	// This do-while loop handles the user password.
	do {
		
		// Check if the user is a new user.
		if (newUser) {

			string password2;	// To hold the user re-entered password.
			do {

				// Have the user create a new password for their account.
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
			if (journal->validatePassword(password)) {

				validPassword = true;
			}
			else {

				cout << "\nThat is not a valid password.\n";
			}
		}

	} while (!validPassword);

	// If password was successful, decrypt the journal entries.
	journal->decryptAndLoad(password);

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
			
			cout << "\n\nLIFETIME STATISTICS\n"
				<< "\nNumber of Entries: " << journal->getNumEntries()
				<< "\nAverage Word Count: " << journal->getAvgWordCount()
				<< "\nLongest Entry: " << journal->getLongestPost()
				<< "\nShortest Entry: " << journal->getShortestPost()
				<< "\nAverage Mood: " << journal->getAvgMood()
				<< "\n";
			break;

		// User selected option 4: exit. 
		case '4':
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

	} while (selection != '4');

	// Indicate the program is ending.
	displayOutro();

	// Be sure to re-encrypt the user's data before exiting!
	journal->encryptAndSave(password);
	delete journal;

	pause();
	return 0;
}
