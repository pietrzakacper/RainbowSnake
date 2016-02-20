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
	Snake* _snake;
	RectangleShape* _apple;
	Clock clock;
	vector <RectangleShape> mapTiles;
	FloatRect mapBounds;
	Music music;
	RectangleShape transparentBackgroundLayer;
	Texture appleTexture;

	bool endOfGame;
	bool drawSnake;
	bool switchToFailureScreen;

	Vector2f getRandomPosition();
	Color getRandomColor();
	void setBackground();
	void setAppleFillColor();
	
	bool playFailureAnimation();
	bool doesFailureOccurs();
	void handleFailure();
	float alphaColorChannel;
public:
	virtual void init() override;
	virtual void update() override;
	virtual int handleEvents(Event&) override;
	virtual void render() override;

};

