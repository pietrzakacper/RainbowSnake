#pragma once
#include "State.h"
#include "Game.h"

class MenuState :
	public State
{
public:
	MenuState(int STATE_ID, sf::RenderWindow& window, Font& font);
	~MenuState();

private:
	Text title;
	Text rainbow[7];
	Text menuOptions[2];
	Text signature;

public:
	virtual void init() override;
	virtual void update() override;
	virtual int handleEvents(Event&) override;
	virtual void render() override;
};



