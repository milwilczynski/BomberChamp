#pragma once
#pragma once

#include "Main.h"
#define MAX_NUMBER_OF_ITEMS 3

class MenuClass {
public:
	MenuClass();
	~MenuClass();

	inline static MenuClass& Instance() {
		static MenuClass instance;
		return instance;
	}


private:

};
class MenuController
{
public:
	MenuController(float width, float height);
	~MenuController();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];

};

