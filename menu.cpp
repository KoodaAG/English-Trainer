#include "Menu.h"

Menu::Menu()
{
	actualPos = 1;
}

Menu::~Menu()
{

}

void Menu::addMenu(const std::string& menu_p)
{
	menu.push_back(menu_p);
}

void Menu::displayMenu()
{
	int textXPos = 20;
	int gap = 2;
	int i = 0;

	

	for (auto m : menu)
	{
		++i;
		gotoxy(textXPos, gap* i);
		std::cout << "[" << i << "] " << m << std::endl;	
	}

	textattr(ic::BG_BLUE);
	gotoxy(textXPos, gap * actualPos);
	std::cout << "[" << actualPos << "] " << menu.at(actualPos -1) << std::endl;

	textattr(ic::BG_BLACK);
	textcolor(ic::FG_WHITE);
	
}

void Menu::menuDown()
{
	if (actualPos < menu.size())
	{
		actualPos += 1;
	}
}

void Menu::menuUp()
{
	if (actualPos > 1)
	{
		actualPos -= 1;
	}
}

void Menu::drawSwitchBox()
{
	
}
