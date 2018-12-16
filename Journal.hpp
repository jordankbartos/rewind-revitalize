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

#include "Entry.hpp"
#include "helperFunctions.hpp"
#include <vector>


class Journal
{
	private:
		std::string* encryptedFile;
		std::string* author;
		std::vector<Entry*> entries;	 	//a pointer to an array of entries
		std::string* password;
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
		std::string* getPassword();
		int getNumEntries();
		double getAvgWordCount();
		int getLongestPost();
		int getShortestPost();
		// int getAvgMood(); ??

		//other functions
		void rewind();			// gets a random happy memory.
		void encryptAndSave();	// Encrypts the user data to
		void decryptAndLoad();
		void displayEntry(int);
		void addEntry();
		std::string getPrompt();

};


#endif
