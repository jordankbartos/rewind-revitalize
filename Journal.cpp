/*******************************************************************************
 * File: 			Journal.cpp
 * Authors:		Andrew Swaim, Michael Stanley, Dan Tonthat, Jordan Bartos
 * Date: 			12/14/2018
 * Description: 	implementation file for the Journal class
*******************************************************************************/

#include "Journal.hpp"





/*******************************************************************************
 * Function: 			Journal()
 * Description: default constructor for a Journal object
*******************************************************************************/
Journal::Journal()
{
	this->encryptedFile = NULL;
	this->author = NULL;
	this->password = NULL;
	this->numEntries = 0;
	this->avgWordCount = 0;
	this->longestPost = 0;
	this->shortestPost = 0;
}

/*******************************************************************************
 * Function: 			Journal(std::string*)
 * Description: a constructor for a journal object that takes a pointer to a
 * 	string that corresponds to a journal log file and populates the journal
 * 	with entries from the log file
*******************************************************************************/
Journal::Journal(std::string filename)
{
	//initialize EntrielsLog fstream object with the file name and open for
	//reading
	this->EntriesLog.open(filename, std::fstream::in);

	//if the entry log fails to open, construct the object as a default journal
	if(!EntriesLog)
	{
		this->encryptedFile = NULL;
		this->author = NULL;
		this->password = NULL;
		this->numEntries = 0;
		this->avgWordCount = 0;
		this->longestPost = 0;
		this->shortestPost = 0;
		return;
	}


	this->encryptedFile = new std::string("encryptedFile.txt");

	//first thing in file will be the author's name followed by a newline char
	//100 is the maximum password size
	this->author = new std::string;
	std::getline(EntriesLog,*this->author);


	//second thing in file will be the passowrd followed by a newline char
	this->password = new std::string;
	std::getline(EntriesLog,*this->password);

	//next come the entries in order. Keep reading entries until the EOF is
	//reached
	int endFile = 0;
	while(EntriesLog && endFile != EOF)
	{
		//collect the information for the journal entry in local variables
		std::string tmp;

		//get entryDate
		std::getline(this->EntriesLog,tmp);
		int entryDate = stoi(tmp);

		//get wordcount
		std::getline(this->EntriesLog,tmp);
		int wordCount = stoi(tmp);

		//get mood
		std::getline(this->EntriesLog,tmp);
		int mood = stoi(tmp);

		//get textBody
		std::string textBody;
		std::getline(this->EntriesLog,textBody);

		//get madeHappy
		std::string madeHappy;
		std::getline(this->EntriesLog, madeHappy, '\n');

		//generate a journal entry object and add it to the vector of
		//journal entries
		this->entries.push_back(new Entry(textBody, madeHappy, wordCount,
				entryDate, mood));

		//peek at next character to see if loop loop needs to end
		endFile = EntriesLog.peek();
	}

	this->EntriesLog.close();
}

/*******************************************************************************
 * Function: 			~Journal()
 * Description: destructor for a journal object
*******************************************************************************/
Journal::~Journal()
{
	delete this->author;
	delete this->password;
	for(unsigned int i = 0; i < this->entries.size(); ++i)
	{
		delete this->entries.at(i);
	}
}

/*******************************************************************************
 * Function:			getPassword()
 * Description: returns a pointer to the password member variable
*******************************************************************************/
std::string* Journal::getPassword()
{
	return this->password;
}

/*******************************************************************************
 * Function:			void encryptAndSave()
 * Description: encrypts and saves all the journal entries that belong to the
 * 	Journal object in a specially formatted log file. Uses the password as an
 * 	encryption key
*******************************************************************************/
void Journal::encryptAndSave()
{
	//generate the encryption key from the password
	int encryptionKey=1;
	for(unsigned int i = 0; i < this->password->length(); ++i)
	{
		encryptionKey += static_cast<int>(this->password->at(i));
	}

	std::cout << "encryptionKey: " << encryptionKey << std::endl;

	//char will receive one character at a time from the entries log for
	//encryption and storage in the encrypted file
	char ch = 0;

	//ofstream object for storing contents
	std::ofstream outputFile;
	outputFile.open(*this->encryptedFile, std::ofstream::trunc);

	this->EntriesLog.open("sampleLog.log");

	while(EntriesLog >> ch)
	{
		ch ^= encryptionKey;
		outputFile.put(ch);
	}


	outputFile.close();
}

/*******************************************************************************
 * Function:			void decryptAndLoad()
 * Description: decrypts and loads all the journal entries in a journal log file
 * 	instantiating each journal entry as a new Entry object and adding each one
 * 	to the array of Entry* entries member variable. Uses the password as a
 * 	decryption key
*******************************************************************************/
void Journal::decryptAndLoad()
{
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
			clearTheScreen();

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
	int date = (now->tm_mday) * 1000000;
	//Month
	date += ((now->tm_mon + 1) * 10000);
	//year
	date += (now->tm_year + 1900);
	cout << "Date: " << date << endl;
	newEntry->setDate(date);

	//Mood

	//Clear the clearTheScreen
	clearTheScreen();
	cout << "How would you rate your mood? (1 -5)" << endl;
	int mood = checkValidity(1, 5);
	newEntry->setMood(mood);
	clearTheScreen();

	//Prompt the user for what made them happy
	cout << "In one sentence, what is something that made you happy today? " << endl;
	std::string tempString;
	getline(cin, tempString);
	//Store in happy
	newEntry->setMadeHappy(tempString);
	clearTheScreen();

	//Prompt the user for main entry
	std::string prompt = getPrompt();
	cout << prompt << endl << endl;
	cout << "Enter QUIT on a separate line when finished" << endl << endl;
	//Get input for main entry
	tempString = "";
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
	newEntry->countWords();
	cout << "Words: " << newEntry->getWordCount() << endl;
	pause();

	//Testing display the info
	clearTheScreen();

	cout << "Happy line: " << endl;
	cout << newEntry->getMadeHappy();
	pause();

	clearTheScreen();

	cout << "Mood: " << newEntry->getMood() << endl;
	pause();

	clearTheScreen();
	cout << "Main: " << endl;
	cout << endl << newEntry->getTextBody() << endl;

	pause();
	this->entries.push_back(newEntry);

	delete newEntry;
}
/*******************************************************************************
 * Function:			string getPrompt()
 * Description: returns a string for a randomly selected prompt. Prompts are
 * stored in a text file and the function randomly decides which line to use.
*******************************************************************************/
std::string Journal::getPrompt()
{
	//Initialize random number and open prompt file
	int num = rand();
	fstream input;
	std::string prompt;
	input.open("prompts.txt");
	if(!input)
	{
		cout << "File open error" << endl;
		return "No file found";
	}

	//Get random num in range
	num = num % 40 + 1;
	//Loop until the correct line is found
	for(int i = 0; i < num; i++)
	{
		getline(input, prompt);
	}
	input.close();
	return prompt;

}

/*******************************************************************************
 * Function:
 * Description:
*******************************************************************************/
