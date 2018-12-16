//header file for some helper functions
#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include "Entry.hpp"

void displayIntro();
char displayMainMenu();
void displayOutro();
void clearTheScreen();
void pause();
char validateMenuChoice(char);
char getYesNoAnswer();
int validateIntRange(int, int);
std::string getPrompt();
int countWords(std::string);


#endif
