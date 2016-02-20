#pragma once
#include "State.h"
#include "MenuState.h"
#include <Windows.h>
#include "PlayState.h"
#include <iostream>
#include "FailureState.h"


class Game
{
public:
	static const int SCRN_WIDTH = 640;
	static const int SCRN_HEIGHT = 640;
	static const int APPLE_SIZE = 32;
	static enum {END, MENU, PLAY_STATE, FAILURE};
private:
	RenderWindow window;
	Font font;
	Event event;
	State * actualState;
	int actualStateID;
	void changeState();
	void handleState();
	
public:
	Game();
	~Game();
	void runGame();
	
	
};

