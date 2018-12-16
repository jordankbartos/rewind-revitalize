/*******************************************************************************
 * File: 			Journal.cpp
 * Authors:		Andrew Swaim, Michael Stanley, Dan Tonthat, Jordan Bartos
 * Date: 			12/14/2018
 * Description: 	implementation file for the Journal class
*******************************************************************************/

#include "Journal.hpp"
#include "helperFunctions.hpp"
#include <stdio.h>


/*******************************************************************************
 * Function: 			Journal()
 * Description: default constructor for a Journal object
*******************************************************************************/
Journal::Journal()
{
	this->encryptedFile = "";
	this->numEntries = 0;
	this->avgWordCount = 0;
	this->longestPost = 0;
	this->shortestPost = 0;
	this->avgMood = 0;
}

/*******************************************************************************
 * Function: 			~Journal()
 * Description: destructor for a journal object
*******************************************************************************/
Journal::~Journal()
{
	for(unsigned int i = 0; i < this->entries.size(); ++i)
	{
		delete this->entries.at(i);
	}
}

/*******************************************************************************
* Function: bool userNameExists(std::string)
* Description: Opens a log file with the name of the username and checks to
* see if the first line is blank. If so, returns false, otherwise true.
*******************************************************************************/
bool Journal::userNameExists(std::string username)
{
	// Get the full filename
	std::string filename = username + ".log";
	std::cout << filename << std::endl;

	// Open the file.
	std::ifstream ifs;
	ifs.open(filename.c_str());

	//if the filename does not exist, the file will not open
	if(!ifs)
	{
		return false;
	}

	/* Check if the file is empty. If so this user has no username or password
	 * recorded and is therefore a new user. */

	std::string input;
	getline(ifs, input);
	ifs.close();

	// If the first line is blank then this was a new file that was created.
	if (input.length() == 0) {

		// Delete the file and return false.
		if (remove(filename.c_str()) != 0) {

			// ERROR HANDLING: couldn't delete file for some reason.
			std::cout << "\nError deleting file.\n";
		}
		return false;
	}
	return true;
}

/*******************************************************************************
* Function: bool validatePassword(std::string)
* Description: Gets the second line of the file and attempts to decrypt it
* using the password as a key. If successful, also compares the decrypted
* password with the user entered password to determine validity.
*******************************************************************************/
bool Journal::validatePassword(std::string username, std::string password)
{
	std::string input;		// To hold an input from the file.
	std::string decrypted;	// To hold the decrypted password.

	int key = createKey(password);

	// Open the input file.
	std::string filename = username + ".log";
	std::ifstream ifs;
	ifs.open(filename.c_str());

	if (!ifs) {

		// ERROR HANDLING
		cout << "\nError: Could not open file for " << username << "\n";
		return false;
	}
	else {
		// Get the second line from the file.
		getline(ifs, input);
		getline(ifs, input);

		// Attempt to decrypt the line with the encryption key.
		char ch;
		for (unsigned int i = 0; i < input.length(); i++)
		{
			ch = input[i] ^ key;
			decrypted += ch;
		}
		ifs.close();

		// Validate if the passwords match.
		if (decrypted == password) {

			return true;
		}
		return false;
	}
}

/*******************************************************************************
* Function: void rewind()
* Description:
*******************************************************************************/
void Journal::rewind()
{
	if(!(this->entries.empty()))
	{
		int size = entries.size();
		int num = rand() % size;
		Entry* temp = (entries.at(num));
		int date = temp->getDate();
		clearTheScreen();
		int month = date / 1000000;
		int day = (date - (month * 1000000)) / 10000;
		int year = date - (month * 1000000) - (day * 10000);
		cout << "On " << month << "/" << day << "/" << year << endl;
		std::string happy = temp->getMadeHappy();
		cout << happy << endl;
		cout << "made you happy!" << endl;
		pause();
	}
	else
	{
		clearTheScreen();
		cout << "It looks like you currently do not have any journal entries" << endl << endl;
		cout << "Life is 10% what happens to you and 90% how you react to it - Lou Holtz" << endl;
		pause();
	}
}

/*******************************************************************************
* Function: int createKey(std::string)
* Description: generates a key using a password string.
*******************************************************************************/
int Journal::createKey(std::string password)
{
	int encryptionKey = 1;
	//generate and encryption key from the user-entered password
	for (unsigned int i = 0; i < password.length(); ++i)
	{
		encryptionKey += static_cast<int>(password.at(i));
	}
	return encryptionKey;
}

/*******************************************************************************
 * Function:			void encryptAndSave()
 * Description: encrypts and saves all the journal entries that belong to the
 * 	Journal object in a specially formatted log file. Uses the password as an
 * 	encryption key
*******************************************************************************/
void Journal::encryptAndSave(std::string password)
{
	//generate the encryption key from the password
	int key = createKey(password);

	std::cout << "encryptionKey: " << key << std::endl;

	//char will receive one character at a time from the entries log for
	//encryption and storage in the encrypted file
	char ch = 0;

	//ofstream object for storing contents
	std::ofstream outputFile;
	outputFile.open(this->encryptedFile, std::ofstream::trunc);

	this->EntriesLog.open("sampleLog.log");

	while(EntriesLog >> ch)
	{
		ch ^= key;
		outputFile.put(ch);
	}


	outputFile.close();
}

/*******************************************************************************
 * Function:			void decryptAndLoad()
 * Description: decrypts and loads all the journal entries in a journal log file
 * 	instantiating each journal entry as a new Entry object and adding each one
 * 	to the array of Entry* entries member variable. Uses the password as a
 * 	decryption key. This function will not be called
*******************************************************************************/
void Journal::decryptAndLoad(std::string password)
{
	int key = createKey(password);

	//attempt to decrypt the file
	//make a txt file to store decrypted contents
	std::ofstream decryptedFile("decryptedFile.txt");
	//decrypt and store each character
	char ch;
	this->EntriesLog.seekg(0);
	this->EntriesLog.clear();
	while(this->EntriesLog >> ch)
	{
		ch ^= key;
		decryptedFile.put(ch);
	}

	/*
	//attempt to read the password from the decrypted file
	std::string tmp;
	getline(decryptedFile,tmp,'\n');
	//compare the password to the user-entered password
	if(tmp.compare(password == 0)
	{
		//if they are the same, populate the journal with entries and return
		return true;
	}
	//if any of this fails, return error and get new password
	return false;*/
}

/*******************************************************************************
 * Function:			void displayEntry(string*)
 * Description: displays an entry from the journal. Takes a string that should
 * 	correspond to a date (or maybe a search criteria??), searches entries that
 *	match and displays them
*******************************************************************************/
void Journal::displayEntry(int search)
{
	for(unsigned int i = 0; i < this->entries.size(); ++i)
	{
		if(this->entries.at(i)->getDate() == search)
		{
			//clearTheScreen();		CLEAR SCREEN NOT WORKING

			std::cout << "Date: "
					<< this->entries.at(i)->getDate() << "\n";
			std::cout << "Mood: "
					<< this->entries.at(i)->getMood() << "\n";
			std::cout << "\nMade me happy:\n"
					<< this->entries.at(i)->getMadeHappy() << "\n\n";
			std::cout << "Entry:\n"
					<< this->entries.at(i)->getTextBody() << std::endl;

			pause();
		}
	}
	return;
}

/*******************************************************************************
 * Function:			void addEntry()
 * Description: guides the user through the process of adding a journal entry,
 * 	collecting all necessary input and then instantiating a new Entry object
 * 	and adding it to the array of Entry* entries.
*******************************************************************************/
void Journal::addEntry()
{
	//https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
	std::time_t t = time(0);
	std::tm* now = std::localtime(&t);
	Entry* newEntry = new Entry();

	//Date
	//day
	int date = (now->tm_mon + 1) * 1000000;
	//Month
	date += ((now->tm_mday) * 10000);
	//year
	date += (now->tm_year + 1900);
	cout << "Date: " << date << endl;
	newEntry->setDate(date);
	//Mood

	//Clear the clearTheScreen
	clearTheScreen();
	cout << "How would you rate your mood? (1 - 5)" << endl;
	int mood = validateIntRange(1, 5);
	newEntry->setMood(mood);
	clearTheScreen();

	//Prompt the user for what made them happy
	cout << "In one sentence, what is something that made you happy today? " << endl;
	std::string happy;
	getline(cin, happy);
	newEntry->setMadeHappy(happy);
	pause();
	clearTheScreen();
	//Prompt the user for main entry
	std::string prompt = getPrompt();
	cout << prompt << endl << endl;
	cout << "Enter QUIT on a separate line when finished" << endl << endl;
	//Get input for main entry
	std::string tempString = "";
	std::string body = "";
	bool quit = false;
	while(!quit)
	{
		getline(cin, tempString);
		if(tempString != "QUIT")
		{
			body += tempString;
		}
		else
		{
			quit = true;
		}

	}
	newEntry->setTextBody(body);
	clearTheScreen();
	//Count the words
	int words = countWords(body);
	newEntry->setWordCount(words);
	//Store it
	this->entries.push_back(newEntry);
	pause();

}

// Getters and setters
int Journal::getNumEntries()
{
	return this->numEntries;
}

double Journal::getAvgWordCount()
{
	return this->avgWordCount;
}

int Journal::getLongestPost()
{
	return this->longestPost;
}

int Journal::getShortestPost()
{
	return this->shortestPost;
}

int Journal::getAvgMood()
{
	return this->avgMood;
}

/*******************************************************************************
 * Function:
 * Description:
*******************************************************************************/
