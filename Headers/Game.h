#pragma once
#include "Main.h"
#include "TextureClass.h"
#include "SceneLevel.h"

//definicja klasy GameClass opartej na singletonie
class GameClass final 
{
public:
	enum CurrentGameStatus
	{
		Initializing = 0,			// Ten status zostanie ustawiony gdy wejdziemy do konstruktora klasy gry.
		Running = 1,			// Ten status zostanie ustawiony gdy rozpoczniemy gre.
		Paused = 2,			// Ten status zostanie ustawiony gdy uzytkownik zapauzuje gre.
		CleanMemory = 3,				// Ten status zostanie ustawiony gdy wejdziemy do destruktora klasy gry.
		Menu = 4
	};
	~GameClass(); //destruktor

	//Uruchamia glowny kod gry
	void MenuRun();

	void GameRun();
	void SetPause();
	// Zwraca status gry
	inline CurrentGameStatus GetStatus() const
	{
		return apk_currentGameStatus;
	}

	// Zwraca okno gry
	inline RenderWindow& GetWindow()
	{
		return apk_window;
	}



	// funkcja tworzaca istancje	

	inline static GameClass& Instance()
	{
		static GameClass instance;
		return instance;
	}

	inline SceneLevel *GetCurrentLevel()
	{
		return apk_currentLevel;
	}



private:
	GameClass();
	//blokada konstruktora kopiujacego
	GameClass(const GameClass &) = delete;

	//usuniecie operatora przypisania
	void operator=(const GameClass &) = delete;
	CurrentGameStatus			apk_currentGameStatus;			// Aktualny status gry.
	RenderWindow	apk_window;			// Okno gry.
	SceneLevel	*apk_currentLevel;
};