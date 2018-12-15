//A few additional functions

#include "helperFunctions.hpp"
#include <sstream>		// stringstream
#include <string>		// string
#include <iostream>		// cin, cout, getline
#include <cctype>		// tolower


/*******************************************************************************
* Function					void displayIntro()
* Description: Displays the intro the program.
*******************************************************************************/
void displayIntro() {

	std::cout << "\n\nWELCOME!\n\n"
		<< "to Rewind Revitalize!\n";
}

/*******************************************************************************
* Function					char displayMainMenu()
* Description: Displays the main menu for the program. Returns the maximum
* selection in order to validate the user's selection.
*******************************************************************************/
char displayMainMenu() {

	std::cout << "\n\nMAIN MENU\n\n"
		<< "1) Make a new journal entry\n"
		<< "2) Show me a happy memory\n"
		<< "3) View lifetime statistics\n"
		<< "4) Exit\n\n";

	return '4';
}


/*******************************************************************************
* Function					char displayMainMenu()
* Description: Displays the main menu for the program. Returns the maximum
* selection in order to validate the user's selection.
*******************************************************************************/
void displayOutro() {

	std::cout << "\n\nHave a wonderful day!\n";
	// Maybe display a random inspirational quote on exiting?
}

/*******************************************************************************
 * Function:				void pause()
 * Description: pauses the progress of the program until the user pushes enter.
*******************************************************************************/
void pause()
{
	std::cout << "\n\nPress [Enter] to continue.\n" << std::endl;
	std::string dummyString;
	std::getline(std::cin,dummyString);
}


/*******************************************************************************
 * Function					void clearTheScreen()
 * Description: clears the screen.
*******************************************************************************/
void clearTheScreen()
{
	/* THIS METHOD DOES NOT SEEM TO BE WORKING FOR ME :(   -ANDREW */

	//this was found at http://stackoverflow.com/questions/17335816/clear-scren
	//-using-c
	std::cout << "\033[2J\033[1;1H";
}

/*******************************************************************************
* Function					char validateMenuChoice(char)
* Description: validates a numerical menu selection made by the user to
* to determine if they selected a valid option. If the selection in the valid
* range from 1 to the max possible selection, returns the selection as a char.
*******************************************************************************/
char validateMenuChoice(char max) {

	bool validChoice = false;	// Error flag
	std::string input;			// To hold a line of user input
	char selection;				// To hold the final menu selection by the user
	std::stringstream ss;		// stringstream for validating user input.

	// Do-while loop will run until the user enters a valid input.
	do {

		// Read a line of input from the user.
		getline(std::cin, input);

		// Load stringstream with the user input.
		ss.str(input);

		// Get first char and make sure nothing is left over.
		if (ss >> selection && !(ss >> input)) {

			// Make sure the selection is in a valid range.
			if (selection >= '1' && selection <= max) {

				validChoice = true;
			}
		}

		// Display error message and loop again if input is invalid.
		if (validChoice == false) {

			std::cout << "\nSorry, you must select an option between"
				<< "1 and " << max << ". Please re-enter selection.\n";

			// Clear stringstream buffer to prepare for next loop.
			ss.clear();
		}

	} while (validChoice == false);

	return selection;
}

/*******************************************************************************
* Function					char getYesNoAnswer()
* Description: gets a valid yes or no answer from the user. Returns a 'y' if
* the user answers y/Y or a 'n' if the user answers n/N. 
*******************************************************************************/
char getYesNoAnswer() {

	bool validChoice = false;	// Error flag
	std::string input;			// To hold a line of user input
	char answer;				// To hold the answer by the user
	std::stringstream ss;		// stringstream to validate user input

	// Do-while loop will run until the user inputs a valid answer.
	do {

		// Get a line of user input.
		getline(std::cin, input);

		// Load the stringstream with user input.
		ss.str(input);

		// Get the first char and make sure there is nothing left over.
		if (ss >> answer && !(ss >> input)) {

			// Convert to lowercase.
			answer = std::tolower(answer);

			// Check if valid answer.
			if (answer == 'y' || answer == 'n') {

				validChoice = true;
			}
		}

		// If input invalid, display error message and loop again.
		if (validChoice == false) {

			std::cout << "\nSorry, you must enter a 'y' or 'n' answer. "
				<< "Please re-enter answer.\n";

			// Clear stringstream buffer to prepare for next loop.
			ss.clear();
		}

	} while (validChoice == false);

	return answer;
}

