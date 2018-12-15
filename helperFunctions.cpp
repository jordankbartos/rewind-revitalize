//A few additional functions

#include "helperFunctions.hpp"



/*******************************************************************************
 *						void pause()
 * Description: pauses the progress of the program until the user pushes enter.
*******************************************************************************/
void pause()
{
	std::cout << "\n\nPress [Enter] to continue.\n" << std::endl;
	std::string dummyString;
	std::getline(std::cin,dummyString);
}

/*******************************************************************************
 *					void clearTheScreen()
 * Description: clears the screen.
*******************************************************************************/
void clearTheScreen()
{
	//this was found at http://stackoverflow.com/questions/17335816/clear-scren
	//-using-c
	std::cout << "\033[2J\033[1;1H";
}
