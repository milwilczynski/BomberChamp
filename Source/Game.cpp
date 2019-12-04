#include "../Headers/Game.h"
#include "../Headers/Bomberchamp.h"
#include "../Headers/Background.h"
#include "../Headers/Main.h"
#include "../Headers/Menu.h"

GameClass::GameClass()		//konstrutkor glownej klasy
	:
	apk_currentGameStatus(CurrentGameStatus::Initializing),
	apk_window(VideoMode(800,600,32), "BomberChamp", Style::Close),
	apk_currentLevel(new SceneLevel())
{
	//playerOne
	
	TextureClass::Load("Bomberchamp_F", "Assets/Sprites/Bomberman/Front/Bman_F_f00.png");
	TextureClass::Load("Bomberchamp_S", "Assets/Sprites/Bomberman/Side/Bman_F_f00.png");
	TextureClass::Load("Bomberchamp_B", "Assets/Sprites/Bomberman/Back/Bman_B_f00.png");
	
	//playerTwo
	TextureClass::Load("Bomberchamp2_F", "Assets/Sprites/Creep/Front/Creep_F_f00.png");
	TextureClass::Load("Bomberchamp2_S", "Assets/Sprites/Creep/Side/Creep_S_f00.png");
	TextureClass::Load("Bomberchamp2_B", "Assets/Sprites/Creep/Back/Creep_B_f00.png");
		
	//bloczki

	TextureClass::Load("Tile_Solid", "Assets/Sprites/Blocks/SolidBlock.png");
	TextureClass::Load("Tile_Expload", "Assets/Sprites/Blocks/Expload.png");
	TextureClass::Load("Tile_Ground", "Assets/Sprites/Blocks/BackgroundTile.png");


	TextureClass::Load("Bomb", "Assets/Sprites/Bomb/Bomb_f03.png");
	TextureClass::Load("Expload", "Assets/Sprites/Flame/Flame_f00.png");
	

}



GameClass::~GameClass() //destuktor glownej klasy
{
	if (apk_window.isOpen())
	{
		apk_window.close();
	}
	if(apk_currentLevel)
	{
		delete apk_currentLevel;
	}
	
}
void GameClass::SetPause() {
	apk_currentGameStatus = CurrentGameStatus::Paused;
}
void GameClass::MenuRun()
{
	apk_currentGameStatus = CurrentGameStatus::Menu;

	if (apk_currentGameStatus == CurrentGameStatus::Menu)
	{

		sf::Texture texture;
		sf::Sprite background;
		sf::Vector2u TextureSize;
		sf::Vector2u WindowSize;
		if (!texture.loadFromFile("./Assets/Sprites/Background/title_flat.jpg"))
		{

		}
		else {
			TextureSize = texture.getSize();
			WindowSize = apk_window.getSize();

			float ScaleX = (float)WindowSize.x / TextureSize.x;
			float ScaleY = (float)WindowSize.y / TextureSize.y;

			background.setTexture(texture);
			background.setScale(ScaleX, ScaleY);
		}
		MenuController menu(apk_window.getSize().x, apk_window.getSize().y);
		while (apk_window.isOpen())
		{
			sf::Event event;

			while (apk_window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Up:
						menu.MoveUp();
						break;

					case sf::Keyboard::Down:
						menu.MoveDown();
						break;

					case sf::Keyboard::Return:
						switch (menu.GetPressedItem())
						{
						case 0:
							GameRun();
							apk_window.clear();
							apk_currentGameStatus = CurrentGameStatus::Running;
							break;
						case 1:
							apk_window.close();
							break;
						}

						break;
					}

					break;
				case sf::Event::Closed:
					apk_window.close();

					break;

				}
			}
			apk_window.clear();
			apk_window.draw(background);
			menu.draw(apk_window);
			apk_window.display();
		}

	}

}

void GameClass::GameRun() {

		Color bgColor(30, 30, 30);

		Clock clock;
		float time = 1 / 60.f;

		{
			for (auto y = 0u; y < 15; y++)
			{
				for (auto x = 0u; x < 20; x++)
				{
					auto *tile = new Background(BackgroundType::TGround);
					tile->SetLocation(grim::Vector2(x * 40, y * 40));
					apk_currentLevel->Add(tile); //zla nazwa, ale chodzi o dodanie XD
				}
			}

			std::vector<std::vector<unsigned char>> tiles =
			{
				{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,},
				{2, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,},
				{2, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,},
				{2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2,},
				{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,},
				{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,},
				{2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2,},
				{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,},
				{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,},
				{2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2,},
				{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,},
				{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2,},
				{2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 0, 2, 0, 2,},
				{2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 2,},
				{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,}
			};

			for (auto y = 0u; y < 15; y++)
			{
				for (auto x = 0u; x < 20; x++)
				{
					unsigned char &tile = tiles[y][x];
					if (tile == BackgroundType::TSolid)
					{
						auto *tile = new Background(BackgroundType::TSolid);
						tile->SetLocation((grim::Vector2f(x * 40, y * 40)));
						apk_currentLevel->Add(tile); //zla nazwa, ale chodzi o dodanie XD

					}

					if (tile == BackgroundType::TExpload)
					{
						auto *tile = new Background(BackgroundType::TExpload);
						tile->SetLocation((grim::Vector2f(x * 40, y * 40)));
						apk_currentLevel->Add(tile); //zla nazwa, ale chodzi o dodanie XD

					}

				}
			}
		}



		auto *bomberchampFirst = new Bomberchamp(true);
		bomberchampFirst->SetLocation(grim::Vector2(60, 60));
		apk_currentLevel->Add(bomberchampFirst);

		auto *bomberchampSecond = new Bomberchamp(false);
		bomberchampSecond->SetLocation(grim::Vector2(740, 540));
		apk_currentLevel->Add(bomberchampSecond);


		//FloatRect collider(Vector2f(60, 60), Vector2f(40, 40));


		// sprawdzamy czy status aplikacji nie ulegl zmianie i odpowiednie czyscimy pamiec
		while (apk_currentGameStatus != CurrentGameStatus::CleanMemory)
		{

			float frameStartTime = clock.getElapsedTime().asSeconds();

			Event windowEvent;
			while (apk_window.pollEvent(windowEvent))
			{
				if (windowEvent.type == Event::Closed)
				{
					apk_currentGameStatus = CurrentGameStatus::CleanMemory;
				}
			}
			apk_window.clear(bgColor);

			apk_currentLevel->Update(time);
			apk_currentLevel->Draw();




			if (apk_currentGameStatus == CurrentGameStatus::Paused) {
				Font font;
				font.loadFromFile("./Assets/arial.ttf");
				Text endingText;
				endingText.setString("Game is over, click ANY KEY to continue.");
				endingText.setPosition(sf::Vector2f(225, 275));
				endingText.setFillColor(sf::Color::White);
				endingText.setOutlineColor(sf::Color::Red);
				endingText.setCharacterSize(20);
				endingText.setFont(font);

				apk_window.draw(endingText);

				while (apk_window.pollEvent(windowEvent)) {
					switch (windowEvent.type) {
					case sf::Event::KeyPressed:
						apk_currentGameStatus = CurrentGameStatus::CleanMemory;
						break;
					default:
						break;
					}
				}
			}
			time = clock.getElapsedTime().asSeconds() - frameStartTime;
			
			apk_window.display();
			
		}
}

