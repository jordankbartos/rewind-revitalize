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
	this->encryptedFile = "";
	this->numEntries = 0;
	this->avgWordCount = 0.0;
	this->longestPost = 0;
	this->shortestPost = INT_MAX;
	this->avgMood = 0.0;
	this->totalMood = 0;
	this->totalWord = 0;
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

	this->encryptedFile = username + ".log";
	// Get the full filename
	std::string filename = username + ".log";

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
	//create cstring of length to hold password plus null terminator
	char ch[100] = {0};

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
		// Get the first number of characters from the file that are equal to
		// the length of the provided password.
		ifs.get(ch,password.length()+1);
		input = ch;


		// Attempt to decrypt the line with the encryption key.
		encryptString(input,key);
		ifs.close();

		// Validate if the passwords match.
		if (input == password) {

			return true;
		}
		return false;
	}
}

/*******************************************************************************
* Function: void rewind()
* Description: Prints a happy memory from a random entry
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

	//char will receive one character at a time from the entries log for
	//encryption and storage in the encrypted file
	char ch = 0;

	//ofstream object for storing contents
	std::ofstream outputFile;
	outputFile.open(this->encryptedFile, std::ofstream::trunc);
	if(!outputFile)
	{
		std::cout << "Error opening storage file." << std::endl;
		return;
	}

	//encrypt and save the password
	for(unsigned int i = 0; i < password.length(); ++i)
	{
		ch = static_cast<int>(password.at(i)) ^ key;
		outputFile.put(ch);
	}

	//insert a "group seperator character" into the file
	ch = static_cast<char>(29) ^ key;
	outputFile.put(ch);

	//encrypt and save the contents of each entry
	std::string toEncrypt;
	int intToEncrypt;
	for (unsigned int i = 0; i < this->entries.size(); ++i)
	{
		//get and encrypt the text body
		toEncrypt = this->entries.at(i)->getTextBody();
		encryptString(toEncrypt,key);
		//put it into the file
		outputFile << toEncrypt;

		//put an encrypted "group seperator character" into the file
		ch = 29 ^ key;
		outputFile.put(ch);

		//get and encrypt and insert the madeHappy
		toEncrypt = this->entries.at(i)->getMadeHappy();
		encryptString(toEncrypt,key);
		outputFile << toEncrypt;

		//insert the encrypted "group seperator character" again
		outputFile.put(ch);

		//get and encrypt and insert the wordcount
		intToEncrypt = this->entries.at(i)->getWordCount();
		toEncrypt = std::to_string(intToEncrypt);
		encryptString(toEncrypt,key);
		outputFile << toEncrypt;

		//insert an encrypted newline char
		ch = '\n' ^ key;
		outputFile.put(ch);

		//get and encrypt and insert the date
		intToEncrypt = this->entries.at(i)->getDate();
		toEncrypt = std::to_string(intToEncrypt);
		encryptString(toEncrypt,key);
		outputFile << toEncrypt;

		//insert an encrypted newline char
		outputFile.put(ch);

		//get and encrypt and insert the mood
		intToEncrypt = this->entries.at(i)->getMood();
		toEncrypt = std::to_string(intToEncrypt);
		encryptString(toEncrypt,key);
		outputFile << toEncrypt;

		//insert an encrypted newline char
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
	char ch;
	char groupSeparatorChar = static_cast<char>(29);
	std::string str;

	//open a file and decrypt EntriesLog into it
	std::ofstream ofs;

	//open a temporary file to store the unencrypted log file
	ofs.open("tempUnEncryp.log");
	if(!ofs)
	{
		std::cout << "Error #1 opening temporary log file." << std::endl;
		return;
	}

	//open the EntriesLog file
	this->EntriesLog.open(encryptedFile);
	if(!this->EntriesLog)
	{
		std::cout << "Error opening encrypted log file." << std::endl;
	}

	//decrypt the EntriesLog file and insert contents into the temp file
	while(this->EntriesLog >> ch)
	{
		ch ^= key;
		ofs << ch;
	}

	this->EntriesLog.close();
	ofs.close();

	//re-open temp log file for reading
	std::ifstream ifs;
	ifs.open("tempUnEncryp.log");
	if(!ifs)
	{
		std::cout << "Error #2 opening temporary log file." << std::endl;
	}

	//ignore the password entry
	std::getline(ifs, str, groupSeparatorChar);

	//read the contents of an entry, generate a new entry object, append it
	//to the vector of entries, and continue until the EOF is reached
	if(!(ifs && ifs.peek() != EOF))
	{
		this->totalWord = 0;
		this->longestPost = 0;
		this->shortestPost = 0;
		this->totalMood = 0;
	}
	while(ifs && ifs.peek() != EOF)
	{
		//increment total number of entries
		this->numEntries++;

		//read text body
		std::getline(ifs, str, groupSeparatorChar);
		std::string textBody = str;

		//read made happy
		std::getline(ifs, str, groupSeparatorChar);
		std::string madeHappy = str;

		//read word count
		int wordCount = 0;
		ifs >> wordCount;
		this->totalWord += wordCount;
		if(this->longestPost < wordCount)
		{
			this->longestPost = wordCount;
		}
		if(this->shortestPost > wordCount)
		{
			this->shortestPost = wordCount;
		}

		//read date
		int date = 0;
		ifs >> date;

		//read mood
		int mood = 0;
		ifs >> mood;
		this->totalMood += mood;

		//ignore the newline that comes after mood
		ifs.ignore(1, '\n');

		//generate new Entry and add to vector of entries
		this->entries.push_back(new Entry(textBody,madeHappy,wordCount,date,mood));
	}
		if(numEntries != 0)
		{
			this->avgWordCount = this->totalWord / this->numEntries;
			this->avgMood = this->totalWord / this->numEntries;
		}

	//close both files
	ifs.close();
	remove("tempUnEncryp.log");


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
			//clearTheScreen();

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

	//Clear the screen
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
	numEntries++;
	totalMood += mood;
	totalWord += words;
	if(words > this->getLongestPost())
	{
		this->setLongestPost(words);
	}
	if(words < this->getShortestPost() || this->getShortestPost() == 0)
	{
		this->setShortestPost(words);
	}
	//Set average words
	double avgWords = static_cast<double>(this->getTotalWord());
	double wordsResult = avgWords / this->getNumEntries();
	this->setAvgWordCount(wordsResult);

	//Set averageMood
	double moodsAvg = static_cast<double>(this->getTotalMood());
	double moodResult = moodsAvg / this->getNumEntries();
	this->setAvgMood(moodResult);


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

double Journal::getAvgMood()
{
	return this->avgMood;
}

int Journal::getTotalMood()
{
	return this->totalMood;
}

int Journal::getTotalWord()
{
	return this->totalWord;
}

void Journal::setNumEntries(int num)
{
	this->numEntries = num;
}

void Journal::setAvgWordCount(double word)
{
	this->avgWordCount = word;
}

void Journal::setLongestPost(int l)
{
	this->longestPost = l;
}

void Journal::setShortestPost(int s)
{
	this->shortestPost = s;
}

void Journal::setAvgMood(double mood)
{
	this->avgMood = mood;
}
