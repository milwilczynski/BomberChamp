#include "Headers/Main.h"
#include "Headers/Menu.h"
#include "Headers/Game.h"
float gameSpeed = 1.0f;

void draw_all(RenderWindow &window, std::vector<Sprite*> &sprites)
{
	for (auto *sprite : sprites)
		window.draw(*sprite);
}


int main()
{
	auto &gameLaunch = GameClass::Instance();
	gameLaunch.MenuRun();




	return 0;
}