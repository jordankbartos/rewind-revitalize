/*******************************************************************************
 * File: 			Journal.hpp
 * Authors:		Andrew Swaim, Michael Stanley, Dan Tonthat, Jordan Bartos
 * Date:			12/14/2018
 * Description:	The header file for the Journal class. The Journal class
 * 	manages all the entries for the journal, encrypts and saves the journal,
 * 	can read the journal log file and load a journal from it, etc
*******************************************************************************/

#ifndef JOURNAL_HPP
#define JOURNAL_HPP

#include <fstream>
#include <vector>
#include "Entry.hpp"
#include "helperFunctions.hpp"

class Journal
{
	private:
		std::string encryptedFile;
		//std::string* author;				// author stored in log file only now.
		std::vector<Entry*> entries;	 	//a pointer to an array of entries
		//std::string* password;			// password stored in log file only now.

		int numEntries;
		double avgWordCount;
		int longestPost;
		int shortestPost;
		// int avgMood; ??

		std::fstream EntriesLog; 		//a pointer to an fstream object for
									//saving/loading a log file
	protected:
	public:
		//constructors and destructors
		Journal();
		Journal(std::string);
		~Journal();

		//getters and setters
		// std::string getPassword();	REMOVE
		int getNumEntries();
		double getAvgWordCount();
		int getLongestPost();
		int getShortestPost();
		// int getAvgMood(); ??

		//other functions
		bool userNameExists(std::string);
	    void openUserFile(std::string);
		bool validatePassword(std::string);
		void rewind();			// gets a random happy memory.
		void encryptAndSave();	// Encrypts the user data to
		void decryptAndLoad();
		void displayEntry(int);
		void addEntry();
		std::string getPrompt();

};


#endif
