#include "Game.h"





Game::Game()
	:actualStateID(0)
	
{
	window.create(VideoMode(SCRN_WIDTH, SCRN_HEIGHT), "Snake", Style::Close);//TODO panel interfejsu
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
	State * actualState;
	actualState = new MenuState(MENU, window, font);
	actualState->init();

	while (actualStateID != END)
	{
		if (actualStateID != actualState->getSTATE_ID())
			changeState(actualState);

		handleState(actualState);
		
	}
	window.close();
}

void Game::changeState(State *actualState)
{
	switch (actualStateID)
	{
		case MENU:
			
			actualState = new MenuState(MENU, window, font);
			actualState->init();
			break;
	
	}
}

void Game::handleState(State * actualState)
{
	actualState->update();
	actualStateID = actualState->handleEvents(event);
	actualState->render();
}