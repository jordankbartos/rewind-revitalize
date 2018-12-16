//header file for some helper functions
#ifndef HELPERFUNCTIONS_HPP
#define HELPERFUNCTIONS_HPP

#include "Entry.hpp"

// Display messages or prompts.
void displayIntro();
char displayMainMenu();
void displayOutro();
std::string getPrompt();

// Utility functions.
void clearTheScreen();
void pause();

// Validation functions.
char validateMenuChoice(char);
char getYesNoAnswer();
int validateIntRange(int, int);
std::string getPrompt();
int countWords(std::string);


// TODO
bool isValidUsername(std::string);
bool isValidPassword(std::string);


#endif
