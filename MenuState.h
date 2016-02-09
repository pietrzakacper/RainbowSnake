#pragma once
#include "State.h"
#include "Game.h"

class MenuState : public State
{
private:
	Text title;
	Text menuOptions[2];
	Text signature;

public:
	MenuState(int STATE_ID, sf::RenderWindow& window, Font& font);
	~MenuState();

	virtual void init() override;
	virtual void update() override;
	virtual int handleEvents(Event&) override;
	virtual void render() override;
};