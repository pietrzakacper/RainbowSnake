#pragma once
#include "State.h"
#include "MenuState.h"
#include <Windows.h>



class Game
{
public:
	static const int SCRN_WIDTH = 640;
	static const int SCRN_HEIGHT = 640;
	static const int APPLE_SIZE = 32;
	static const int END = 0;
	static const int MENU = 1;
	static const int PLAY_STATE = 2;
private:
	RenderWindow window;
	Font font;
	Event event;
	int actualStateID;
	void changeState(State *actualState);
	void handleState(State *actualState);
	
public:
	Game();
	~Game();
	void runGame();
	
	
};

