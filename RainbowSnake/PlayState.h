#pragma once
#include "State.h"
#include "Snake.h"
#include "Game.h"


class PlayState :
	public State
{
public:
	PlayState(int STATE_ID, sf::RenderWindow& window, Font& font);
	~PlayState();

private:
	Snake* snake;
	RectangleShape* apple;
	Clock clock;

	vector <RectangleShape> mapTiles;
	FloatRect mapBounds;

	Vector2f getRandomPosition();
	void setBackground();

public:
	virtual void init() override;
	virtual void update() override;
	virtual int handleEvents(Event&) override;
	virtual void render() override;

};

