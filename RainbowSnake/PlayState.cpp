#include "PlayState.h"
#include <ctime>
#include <cstdlib>


PlayState::PlayState(int STATE_ID, RenderWindow& window, Font& font)
	:State(STATE_ID, window, font)
{
}



PlayState::~PlayState()
{
}

Vector2f PlayState::getRandomPosition()
{
	srand((unsigned int)time(NULL));

	Vector2i max(Game::SCRN_WIDTH / Game::APPLE_SIZE, Game::SCRN_HEIGHT / Game::APPLE_SIZE);
	Vector2f randomPosition;

	do
	{
		randomPosition = Vector2f(float(rand() % max.x), float(rand() % max.y));


	} while (snake->intersects(randomPosition*(float)Game::APPLE_SIZE));

	return randomPosition;
}

void PlayState::setBackground()
{
	
	for (int j = 0; j < Game::SCRN_WIDTH / Game::APPLE_SIZE; j++)
		for (int i = 0; i < Game::SCRN_HEIGHT / Game::APPLE_SIZE; i++)
		{
			RectangleShape square;
			square.setSize(Vector2f((float)Game::APPLE_SIZE, (float)Game::APPLE_SIZE));
			square.setFillColor(Color::Black);
			square.setOutlineThickness(-1.f);
			square.setOutlineColor(Color(55, 55, 55));
			square.setPosition(Vector2f(j*(float)Game::APPLE_SIZE, i*(float)Game::APPLE_SIZE));
			mapTiles.push_back(square);	
		}
	
}

void PlayState::init() 
{
	
	snake = new Snake();
	apple = new RectangleShape();

	apple->setSize(Vector2f((float)Game::APPLE_SIZE, (float)Game::APPLE_SIZE));
	apple->setFillColor(Color(230,230,230,90));
	apple->setOutlineThickness(-1.f);
	apple->setOutlineColor(Color::Cyan);
	apple->setPosition(getRandomPosition()*(float)Game::APPLE_SIZE);

	setBackground();
	mapBounds = FloatRect(0, 0, Game::SCRN_WIDTH, Game::SCRN_HEIGHT);
	
	clock.restart();

	
}

void PlayState::update()
{
	snake->update();

	if (clock.getElapsedTime().asMilliseconds() >125)//TODO poziomy trudnoœci
	{
		snake->Move();
		

		if (snake->GetHeadFloatRect() == apple->getGlobalBounds())
		{
			
			
			apple->setPosition(getRandomPosition()*(float)Game::APPLE_SIZE);
			snake->AddBodyPart();
		}

		clock.restart();
	}

	if (snake->IsSelfBitting())
	{
		
		cout << "Ugryzienie..." << endl;
	}


	if (!mapBounds.contains(snake->getHeadPosition()))
	{
		cout << "Wyjœcie poza ekran" << endl;
	}

}

int PlayState::handleEvents(Event& event)
{

	while (_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			return Game::END;

		else if (event.type == Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case Keyboard::Left:
				snake->ChangeDirection(Snake::DIR_LEFT);
				break;

			case Keyboard::Right:
				snake->ChangeDirection(Snake::DIR_RIGHT);
				break;

			case Keyboard::Up:
				snake->ChangeDirection(Snake::DIR_UP);
				break;

			case Keyboard::Down:
				snake->ChangeDirection(Snake::DIR_DOWN);
				break;
			}
		}
	}
		return STATE_ID;

}

void PlayState::render()
{
	_window->clear();

	for (unsigned int i = 0; i <mapTiles.size(); i++)
		_window->draw(mapTiles[i]);
	
	_window->draw(*apple);
	
	_window->draw(*snake);

	_window->display();
}