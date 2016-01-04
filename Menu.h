#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "ic.hpp"

using namespace ic::shorties;

class Menu
{
public:
	Menu();
	~Menu();

	void menuUp();
	void menuDown();

	void addMenu(const std::string&);
	void displayMenu();

	void drawSwitchBox();

	short getActualPos() { return actualPos; }
private:
	short actualPos;
	std::vector<std::string> menu;
};
