/*******************************************************************************
 * File: 			Entry.hpp
 * Authors:		Jordan Bartos, Dan Tonthat, Andrew Swaim, Michael Stanley
 * Date:			12/14/2018
 * Description:	The header file for the journal entry class. A journal entry
 * 	contains all of the information contained in one journal entry as well as
 * 	stats on that entry such as word count, date, etc..
*******************************************************************************/

#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <string>

class Entry
{
	private:
		std::string* textBody;
		std::string* madeHappy;
		int wordCount;
		int date;
		int mood;
		
	protected:
	public:
		//constructors and destructor
		Entry();
		~Entry();

		//getters and setters
		void setTextBody(std::string*);
		std::string* getTextBody();
		int getWordCount();
		void countWords();
		void setDate(int);
		int getDate();
		void setMood(int);
		int getMood();
		std::string* getMadeHappy();
		void setMadeHappy(std::string*);

		//other functions
};


#endif
