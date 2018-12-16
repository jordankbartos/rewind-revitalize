/*******************************************************************************
 * File: 			Entry.cpp
 * Authors:		Jordan Bartos, Andrew Swaim, Dan Tonthat, Michael Stanley
 * Date: 			12/14/2018
 * Description: 	implementation file for the journal Entry class
*******************************************************************************/

#include "Entry.hpp"



/*******************************************************************************
 * Function:			Entry()
 * Description: default constructor for an Entry object
*******************************************************************************/
Entry::Entry()
{
	this->textBody = "";
	this->madeHappy ="";
	this->wordCount = 0;
	this->date = 0;
	this->mood = 0;
}

/*******************************************************************************
 * Function:			Entry(string,string,int,int,int)
 * Description: constructor for an Entry object that takes parameters for each
 * 	memeber variable
*******************************************************************************/
Entry::Entry(std::string tb, std::string mh, int wc, int d, int m)
{
	this->textBody = tb;
	this->madeHappy = mh;
	this->wordCount = wc;
	this->date = d;
	this->mood = m;
}


/*******************************************************************************
 * Function:			~Entry()
 * Description: destructor for an Entry object
*******************************************************************************/
Entry::~Entry()
{
}

/******************************************************************************
 * Function: 			void setTextBody(std::string)
 * Description: takes a pointer to a string and sets it as the textBody member
 * variable for the Entry object
*******************************************************************************/
void Entry::setTextBody(std::string body)
{
	this->textBody = body;
}

/*******************************************************************************
 * Function: 			std::string getTextBody();
 * Description: returns a pointer to the text body for the  journal entry
*******************************************************************************/
std::string Entry::getTextBody()
{
	return this->textBody;
}

/*******************************************************************************
 * Function:			int getWordCount();
 * Description: returns the number of words in the text body as an int
*******************************************************************************/
int Entry::getWordCount()
{
	return this->wordCount;
}

/*******************************************************************************
 * Function:			void countWords()
 * Description: counts the number of words in the body of the entry and sets it
 * to the member variable wordCount
*******************************************************************************/
void Entry::countWords()
{
	std::string counter = getTextBody();
	int len = counter.length();
	int words = 0; // Otherwise wouldn't count the last word.
	for(int i = 0; i < len; i++)
	{
		if(counter[i] == ' ' && counter[i + 1] != ' ')
		{
			words++;
		}
		if(counter[i] == '\n')
		{
			words++;
		}
	}

	this->wordCount = words;
}

/*******************************************************************************
 * Function:			void setDate(int)
 * Description: sets the date of the journal entry
*******************************************************************************/
void Entry::setDate(int d)
{
	this->date = d;
}

/*******************************************************************************
 * Function:			int getDate()
 * Description: returns the date as an int.
*******************************************************************************/
int Entry::getDate()
{
	return this->date;
}

/*******************************************************************************
 * Function:			void setMood(int)
 * Description: sets the member variable mood
*******************************************************************************/
void Entry::setMood(int m)
{
	this->mood = m;
}

/*******************************************************************************
 * Function:			int getMood()
 * Description: returns the mood of the entry
*******************************************************************************/
int Entry::getMood()
{
	return this->mood;
}

/*******************************************************************************
 * Function:			std::string* getMadeHappy()
 * Description: returns a pointer to the "what made you happy today" string from
 * the journal entry
*******************************************************************************/
std::string Entry::getMadeHappy()
{
	return this->madeHappy;
}

/*******************************************************************************
 * Function:			void setMadeHappy(string)
 * Description:Sets the string for made happy
*******************************************************************************/
void Entry::setMadeHappy(std::string happy)
{
	this->madeHappy = happy;
}



/*******************************************************************************
 * Function:
 * Description:
*******************************************************************************/
/*******************************************************************************
 * Function:
 * Description:
*******************************************************************************/
