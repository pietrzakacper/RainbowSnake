#include "PlayState.h"
#include <ctime>
#include <cstdlib>


PlayState::PlayState(int STATE_ID, RenderWindow& window, Font& font)
	:State(STATE_ID, window, font),
	endOfGame(false),
	switchToFailureScreen(false),
	drawSnake(true),
	alphaColorChannel(0)
{
}



PlayState::~PlayState()
{
	delete _snake;
	delete _apple;
	music.stop();
	
}

Vector2f PlayState::getRandomPosition()
{
	srand((unsigned int)time(NULL));

	Vector2i max(Game::SCRN_WIDTH / Game::APPLE_SIZE, Game::SCRN_HEIGHT / Game::APPLE_SIZE);
	Vector2f randomPosition;

	do
	{
		randomPosition = Vector2f(float(rand() % max.x), float(rand() % max.y));
		//Wiem, ¿e to nie jest za wydajne :( 
		//Ale za to przejrzyste :)
	} while (_snake->contains(randomPosition*(float)Game::APPLE_SIZE));

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
	
	_snake = new Snake();
	
	_apple = new RectangleShape();

	music.openFromFile("data/FreeKO_Fame.ogg");
	music.setLoop(true);
	music.setRelativeToListener(true);
	
	_apple->setSize(Vector2f((float)Game::APPLE_SIZE, (float)Game::APPLE_SIZE));
	_apple->setPosition(getRandomPosition()*(float)Game::APPLE_SIZE);
	setAppleFillColor();

	setBackground();
	mapBounds = FloatRect(0, 0, Game::SCRN_WIDTH, Game::SCRN_HEIGHT);

	transparentBackgroundLayer.setPosition(Vector2f(0,0));
	transparentBackgroundLayer.setSize(Vector2f(Game::SCRN_WIDTH, Game::SCRN_HEIGHT));
	transparentBackgroundLayer.setFillColor(Color(0, 0, 0, 0));

	music.setVolume(40.f);
	music.play();
	
	clock.restart();
	
}

void PlayState::setAppleFillColor()
{	
		
	_apple->setFillColor(getRandomColor());

}

Color PlayState::getRandomColor()
{
	int n = rand() % 150 + 1;

	switch (int(n % 150) / 25)
	{
	case 0:
		return Color(255, 10 * (n % 25), 0);
	case 1:
		return Color(255 - 10 * (n % 25), 255, 0);
	case 2:
		return Color(0, 255, 10 * (n % 25));
	case 3:
		return Color(0, 255 - 10 * (n % 25), 255);
	case 4:
		return Color(10 * (n % 25), 0, 255);
	case 5:
		return Color(255, 0, 255 - 10 * (n % 25));
	}
}

void PlayState::update()
{	

	if (clock.getElapsedTime().asMilliseconds() > 125 && !endOfGame)
	{
		if (doesFailureOccurs())
		{
			endOfGame = true;
			return;
		}

		setAppleFillColor();
		_snake->Move();


		if (_snake->GetHeadFloatRect() == _apple->getGlobalBounds())
		{
			_apple->setPosition(getRandomPosition()*(float)Game::APPLE_SIZE);
			_snake->AddBodyPart();
		}

		clock.restart();

	}

	else if (endOfGame)
		handleFailure();
}

bool PlayState::doesFailureOccurs()
{
	if (_snake->IsSelfBitting() || !mapBounds.contains(_snake->GetHeadPosition()))
		return true;

	return false;
}

void PlayState::handleFailure()
{
	music.setPitch(music.getPitch()*0.95);
	music.setVolume(music.getVolume() *0.95);

	if (!playFailureAnimation())switchToFailureScreen = true;

	alphaColorChannel+= 1.5f;
	transparentBackgroundLayer.setFillColor(Color(0, 0, 0, alphaColorChannel));
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
				_snake->ChangeDirection(Snake::DIR_LEFT);
				break;

			case Keyboard::Right:
				_snake->ChangeDirection(Snake::DIR_RIGHT);
				break;

			case Keyboard::Up:
				_snake->ChangeDirection(Snake::DIR_UP);
				break;

			case Keyboard::Down:
				_snake->ChangeDirection(Snake::DIR_DOWN);
				break;
			}
		}
		
	}
	if (switchToFailureScreen)return Game::FAILURE;
	return STATE_ID;

}

void PlayState::render()
{
	_window->clear();

	for (unsigned int i = 0; i <mapTiles.size(); i++)
		_window->draw(mapTiles[i]);
	
	_window->draw(*_apple);
	
	if(drawSnake)_window->draw(*_snake);

	_window->draw(transparentBackgroundLayer);

	_window->display();
}

bool PlayState::playFailureAnimation()
{	
	static int animationCounter;

	if (clock.getElapsedTime().asSeconds() > 0.3f && drawSnake)
	{
		drawSnake = false;
		clock.restart();
	}
	else if (clock.getElapsedTime().asSeconds() > 0.2f && !drawSnake)
	{
		drawSnake = true;
		animationCounter++;
		clock.restart();
	}

	if (animationCounter >= 3)
	{	
		animationCounter = 0;
		return false;
	}
	return true;
}