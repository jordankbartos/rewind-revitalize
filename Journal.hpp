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
#include <stdio.h>
#include <limits.h>
#include "Entry.hpp"
#include "helperFunctions.hpp"


class Journal
{
	private:
		std::string encryptedFile;

		// To hold the entries loaded from the log file.
		std::vector<Entry*> entries;

		// Member variables to hold entry statistics.
		int numEntries;
		double avgWordCount;
		int longestPost;
		int shortestPost;
		double avgMood;
		int totalWord;
		int totalMood;

		// For saving/loading a log file.
		std::fstream EntriesLog;

		// Private methods.
		//int createKey(std::string);

	public:
		//constructors and destructors
		Journal();
		~Journal();

		//getters and setters
		int getNumEntries();
		double getAvgWordCount();
		int getLongestPost();
		int getShortestPost();
		double getAvgMood();
		int getTotalMood();
		int getTotalWord();
		void setNumEntries(int);
		void setAvgWordCount(double);
		void setLongestPost(int);
		void setShortestPost(int);
		void setAvgMood(double);

		//other functions
		int createKey(std::string);
		bool userNameExists(std::string);
		bool validatePassword(std::string, std::string);
		void rewind();
		void encryptAndSave(std::string);
		void decryptAndLoad(std::string);
		void displayEntry(int);
		void addEntry();

};


#endif
