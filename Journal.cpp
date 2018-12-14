/*******************************************************************************
 * File: 			Journal.cpp
 * Authors:		Andrew Swaim, Michael Stanley, Dan Tonthat, Jordan Bartos
 * Date: 			12/14/2018
 * Description: 	implementation file for the Journal class
*******************************************************************************/

#include "Journal.hpp"



/*******************************************************************************
 * Function: 			Journal()
 * Description: default constructor for a Journal object
*******************************************************************************/
Journal::Journal()
{
}

/*******************************************************************************
 * Function: 			~Journal()
 * Description: destructor for a journal object
*******************************************************************************/
Journal::~Journal()
{
}

/*******************************************************************************
 * Function:			getPassword()
 * Description: returns a pointer to the password member variable
*******************************************************************************/
std::string* Journal::getPassword()
{
	return this->password;
}

/*******************************************************************************
 * Function:			void encryptAndSave()
 * Description: encrypts and saves all the journal entries that belong to the
 * 	Journal object in a specially formatted log file. Uses the password as an
 * 	encryption key
*******************************************************************************/
void Journal::encryptAndSave()
{
}

/*******************************************************************************
 * Function:			void decryptAndLoad()
 * Description: decrypts and loads all the journal entries in a journal log file
 * 	instantiating each journal entry as a new Entry object and adding each one
 * 	to the array of Entry* entries member variable. Uses the password as a
 * 	decryption key
*******************************************************************************/
void Journal::decryptAndLoad()
{
}

/*******************************************************************************
 * Function:			void displayEntry(string*)
 * Description: displays an entry from the journal. Takes a string that should
 * 	correspond to a date (or maybe a search criteria??), searches entries that
 *	match and displays them
*******************************************************************************/
void Journal::displayEntry(std::string* search)
{
}

/*******************************************************************************
 * Function:			void addEntry()
 * Description: guides the user through the process of adding a journal entry,
 * 	collecting all necessary input and then instantiating a new Entry object
 * 	and adding it to the array of Entry* entries.
*******************************************************************************/
void Journal::addEntry()
{
}

/*******************************************************************************
 * Function:
 * Description:
*******************************************************************************/
