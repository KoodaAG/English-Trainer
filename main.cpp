#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <random>
#include <assert.h>
#include "Menu.h"

using namespace std;

vector<map<string, string>> loadUnit(unsigned un);		// Get Unit phrases from file
void read();
void write();
void menuGetKey(Menu&);
void unitGetKey(Menu&, vector<map<string, string>>& unit);
//vector<map<string, string>> getRandomWords(vector<map<string, string>>& unit);


int main()
{
	cout << "<--! NOTE WRITE THE VOCABULARIES IN THE UNIT TXT FILES !" << endl;
	// Display Menu Options
	Menu mainMenu;
	mainMenu.addMenu("Read");
	mainMenu.addMenu("Write");
	mainMenu.displayMenu();

	menuGetKey(mainMenu);

	return 0;
}



//// Return vector with random vocabularies
//vector<map<string, string>> getRandomWords(vector<map<string, string>>& unit)
//{
//	random_device rd;   // non-deterministic generator
//	std::default_random_engine gen(rd());
//	std::uniform_int_distribution<int> dist(0, 9);
//
//	vector<map<string, string>> randomWord;
//
//	for (int i = 0; i < 10; i++)
//		randomWord.push_back(unit.at(dist(gen)));
//
//	return randomWord;
//}
//


// User wants to read - remember vocabularies
void read()
{
	vector<map<string, string>> unit;					// Contains the english and german vocabularies
	//vector<map<string, string>> randomWord;			// Contains 10 random vocabularies to learn

	Menu unitList;
	unitList.addMenu("Unit 1");
	unitList.addMenu("Unit 2");
	unitList.addMenu("Unit 3");
	unitList.addMenu("Unit 4");
	unitList.addMenu("Unit 5");
	unitList.addMenu("Unit 6");
	unitList.addMenu("Unit 7");
	unitList.displayMenu();

	unitGetKey(unitList, unit);
	//randomWord = getRandomWords(unit);

	system("cls");
	cout << "\t\tOutput Vocabularies!" << endl;

	for (int i = 0; i < unit.size(); i++)
		cout << unit.at(i).begin()->first << " - " << unit.at(i).begin()->second << endl;

	system("pause");
}

// User wants to check his knowlege about writing vocabularies
void write()
{
	vector<map<string, string>> unit;					// Contains the english and german vocabularies

	Menu unitList;
	unitList.addMenu("Unit 1");
	unitList.addMenu("Unit 2");
	unitList.addMenu("Unit 3");
	unitList.addMenu("Unit 4");
	unitList.addMenu("Unit 5");
	unitList.addMenu("Unit 6");
	unitList.addMenu("Unit 7");
	unitList.displayMenu();

	unitGetKey(unitList, unit);
	system("cls");
	
	string enter;

	for (int i = 0; i < unit.size(); i++) {
		cout << "\t\tOutput Vocabularies!" << endl;
		cout << "Enter the english definition" << endl << endl;
		cout << unit.at(i).begin()->first << ": ";
		cin >> enter;
		cin.ignore();
		cin.sync();
		cin.clear();
		if (enter != unit.at(i).begin()->second)
		{
			cout << "Wrong!";
			Sleep(2000);
			system("cls");
		}
		else
		{
			cout << "Right!";
			Sleep(2000);
			system("cls");
		}
	}

}

// Get the right file out of the main folder
vector<map<string, string>> loadUnit(unsigned un)
{
	vector<map<string, string>> unit;

	string path = "Unit_";
	path += static_cast<char>('0' + un);
	path += ".txt";

	cout << "OPEN: " << path << endl;

	try {

		ifstream file(path);
		string line, firstword, secondword;
		stringstream buf;
		map<string, string> mapBuf;

		while (std::getline(file, line))
		{
			buf.str(line);
			buf >> firstword >> secondword;
			mapBuf.insert({ firstword, secondword });
			unit.push_back(mapBuf);
		}

		file.close();
	}
	catch (exception e) {
		assert(e.what());
	}


	return unit;
}

// Handle main menu input
void menuGetKey(Menu& m)
{
	while (!GetAsyncKeyState(VK_ESCAPE))				// Run aslong we didnt push 'ESC'
	{
		if (GetAsyncKeyState(VK_UP)) {
			m.menuUp();
			system("cls");
			m.displayMenu();
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			m.menuDown();
			system("cls");
			m.displayMenu();
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			system("cls");
			if (m.getActualPos() == 1) {
				Sleep(500);
				read();
				break;
			}
			else if (m.getActualPos() == 2) {
				Sleep(500);
				write();
				break;
			}
		}
		Sleep(90);
	}

	system("cls");
}

// Handle unit switch menu input
void unitGetKey(Menu& m, vector<map<string, string>>& unit)
{
	while (!GetAsyncKeyState(VK_ESCAPE))				// Run aslong we didnt push 'ESC'
	{
		if (GetAsyncKeyState(VK_UP)) {
			m.menuUp();
			system("cls");
			m.displayMenu();
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			m.menuDown();
			system("cls");
			m.displayMenu();
		}
		if (GetAsyncKeyState(VK_RETURN)) {
			unit = loadUnit(m.getActualPos());
			return;
		}
		Sleep(90);
	}
}
