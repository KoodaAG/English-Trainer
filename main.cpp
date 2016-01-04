#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <random>
#include "Menu.h"

using namespace std;

vector<map<string, string>> loadUnit(unsigned un);		// Get Unit phrases from file

void read();
void write();

void menuGetKey(Menu&);
void unitGetKey(Menu&, vector<map<string, string>>& unit);

vector<map<string, string>> getRandomWords(vector<map<string, string>>& unit)
{
	random_device rd;   // non-deterministic generator
	mt19937 gen(rd());  // to seed mersenne twister.
	uniform_int_distribution<> dist(0, unit.size()-1); // distribute results between 1 and 6 inclusive.

	vector<map<string, string>> randomWord;

	for (int i = 0; i < 10; ++i)
		randomWord.push_back(unit.at(dist(gen)));

	return randomWord;
}

int main()
{
	// Display Menu Options
	Menu mainMenu;
	mainMenu.addMenu("Read");
	mainMenu.addMenu("Write");
	mainMenu.displayMenu();

	menuGetKey(mainMenu);

	return 0;
}

void read()
{
	vector<map<string, string>> unit;					// Contains the english and german vocabularies
	vector <map<string, string>> randomWord;			// Contains 10 random vocabularies to learn

	Menu unitList;
	unitList.addMenu("Unit 1");
	unitList.addMenu("Unit 2");
	unitList.addMenu("Unit 3");
	unitList.addMenu("Unit 4");
	unitList.addMenu("Unit 5");
	unitList.addMenu("Unit 6");
	unitList.addMenu("Unit 7");
	unitList.displayMenu();

	menuGetKey(unitList);
	randomWord = getRandomWords(unit);

	for (int i = 0; i < 10; ++i)
		cout << randomWord.at(i).begin()->first << " - " << randomWord.at(i).begin()->second << endl;

}

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

	menuGetKey(unitList);

}

vector<map<string, string>> loadUnit(unsigned un)
{
	vector<map<string, string>> unit;

	string path = "unit_"+ static_cast<char>('0'+un);
	path.append(".txt");

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
	return unit;
}

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
			if (m.getActualPos() == 1)
				read();
			else if (m.getActualPos() == 2)
				write();
		}
		Sleep(90);
	}

	system("cls");
}

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
			break;
		}
		Sleep(90);
	}
	system("cls");
}
