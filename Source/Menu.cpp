#include "../Headers/Menu.h"
#include "../Headers/Game.h"
MenuClass::MenuClass()
{
}

MenuClass::~MenuClass() {
	
}


MenuController::MenuController(float width, float height)
{
	if (!font.loadFromFile("./Assets/arial.ttf"))
	{
		// handle error
	}
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setFont(font);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 4, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.65));


	menu[1].setFont(font);
	menu[1].setString("Exit");
	menu[1].setPosition(sf::Vector2f(width / 4, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.05));


	selectedItemIndex = 0;
}


MenuController::~MenuController()
{
}

void MenuController::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void MenuController::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void MenuController::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
