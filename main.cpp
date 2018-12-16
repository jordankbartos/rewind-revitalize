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
	srand(time(0));
	/* TESTING AREA */
	/*journal->displayEntry(1234567890);
	journal->encryptAndSave();*/



	Journal* journal = new Journal();
	journal->addEntry();
	
	delete journal;

	pause();
	return 0;
}
