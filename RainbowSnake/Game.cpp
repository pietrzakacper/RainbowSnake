#include "Game.h"





Game::Game()
	:actualStateID(END)
	
{
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(VideoMode(SCRN_WIDTH, SCRN_HEIGHT), "Snake", Style::Close, settings);//TODO panel interfejsu
	window.clear();
	window.display();

	if (!font.loadFromFile("data/font.ttf"))
	{
		MessageBox(NULL, "Font not found! Chceck data folder!", "ERROR", NULL);
		return;
	}

	actualStateID=MENU;
	
	
}


Game::~Game()
{
}

void Game::runGame()
{
	actualState = new MenuState(MENU, window, font);
	actualState->init();

	while (actualStateID != END)
	{
		if (actualStateID != actualState->getSTATE_ID())
			changeState();
		
		handleState();
		
	}
	window.close();
}

void Game::changeState()
{
	actualState = nullptr;

	switch (actualStateID)
	{
		case MENU:
			actualState = new MenuState(MENU, window, font);
			break;
		case PLAY_STATE:
			actualState = new PlayState(PLAY_STATE, window, font);
			break;
	}
	
	actualState->init();
}

void Game::handleState()
{	
	actualStateID = actualState->handleEvents(event);
	actualState->update();
	actualState->render();
}