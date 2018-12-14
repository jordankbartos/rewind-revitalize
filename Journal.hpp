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

class Journal
{
	private:
		std::string* author;
		std::vector<Entry*> entries;	 	//a pointer to an array of entries
		std::string* password;
		int numEntries;
		double avgWordCount;
		int longestPost;
		int shortestPost;
		std::fstream EntriesLog; //a pointer to an fstream object for saving/loading a log file
	protected:
	public:
		//constructors and destructors
		Journal();
		Journal(std::string);
		~Journal();
		//getters and setters
		std::string* getPassword();
		//other functions
		void encryptAndSave();
		void decryptAndLoad();
		void displayEntry(std::string);
		void addEntry();
		
};


#endif
