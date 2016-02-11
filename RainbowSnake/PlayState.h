#pragma once
#include "State.h"
#include "Snake.h"
#include "Game.h"
#include <SFML/Audio.hpp>


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
	bool endOFGAME, drawSnake, switchToFailureScreen;
	vector <RectangleShape> mapTiles;
	FloatRect mapBounds;
	Music music;
	RectangleShape transparentBackgroundLayer;
	int alphaColorChannel;
	Texture appleTexture;

	Vector2f getRandomPosition();
	void setBackground();
	void updateAppleRainbowTexture();
	bool playFailureAnimation();
	void handleFailure();
public:
	virtual void init() override;
	virtual void update() override;
	virtual int handleEvents(Event&) override;
	virtual void render() override;

};

