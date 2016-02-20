#pragma once
#include "State.h"
#include "Game.h"

class FailureState :
	public State
{
public:
	FailureState(int STATE_ID, sf::RenderWindow& window, Font& font, Image& image);
	~FailureState();
private:
	Text title;
	Text menuOptions[2];
	Texture backgroundTexture;
	Sprite backgroundImage;
	void titleInit();
	void menuOptionsInit();

public:
	virtual void init() override;
	virtual void update() override;
	virtual int handleEvents(Event&) override;
	virtual void render() override;
};

