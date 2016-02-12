#include "PlayState.h"
#include <ctime>
#include <cstdlib>


PlayState::PlayState(int STATE_ID, RenderWindow& window, Font& font)
	:State(STATE_ID, window, font),
	endOFGAME(false),
	switchToFailureScreen(false),
	drawSnake(true)
{
}



PlayState::~PlayState()
{
	delete snake;
	delete apple;
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
	.; for (int i = 0; i < 250; i++)snake->AddBodyPart();
	apple = new RectangleShape();
	music.openFromFile("data/FreeKO_Fame.ogg");
	music.setLoop(true);
	music.setRelativeToListener(true);
	
	apple->setSize(Vector2f((float)Game::APPLE_SIZE, (float)Game::APPLE_SIZE));
	//apple->setFillColor(Color(230,230,230,90));
	apple->setTexture(&appleTexture);
	updateAppleRainbowTexture();
	apple->setPosition(getRandomPosition()*(float)Game::APPLE_SIZE);

	setBackground();
	mapBounds = FloatRect(0, 0, Game::SCRN_WIDTH, Game::SCRN_HEIGHT);

	transparentBackgroundLayer.setPosition(Vector2f(0,0));
	transparentBackgroundLayer.setSize(Vector2f(Game::SCRN_WIDTH, Game::SCRN_HEIGHT));
	alphaColorChannel = 0;
	transparentBackgroundLayer.setFillColor(Color(0, 0, 0, alphaColorChannel));
	
	clock.restart();
	music.setVolume(40.f);
	music.play();
}

void PlayState::updateAppleRainbowTexture()
{	
	RectangleShape rainbow;
	rainbow.setSize(Vector2f(Game::APPLE_SIZE, Game::APPLE_SIZE));
	rainbow.setPosition(Vector2f(0, 0));

		Color rectangleNarrowtColor;
		int n = rand() % 150 + 1;

		switch (int(n % 150) / 25)
		{
		case 0:
			rectangleNarrowtColor = Color(255, 10 * (n % 25), 0);
			break;
		case 1:
			rectangleNarrowtColor = Color(255 - 10 * (n % 25), 255, 0);
			break;
		case 2:
			rectangleNarrowtColor = Color(0, 255, 10 * (n % 25));
			break;
		case 3:
			rectangleNarrowtColor = Color(0, 255 - 10 * (n % 25), 255);
			break;
		case 4:
			rectangleNarrowtColor = Color(10 * (n % 25), 0, 255);
			break;
		case 5:
			rectangleNarrowtColor = Color(255, 0, 255 - 10 * (n % 25));
			break;

		}
	
		rainbow.setFillColor(rectangleNarrowtColor);


	RenderTexture rainbowTexture;
	rainbowTexture.create(Game::APPLE_SIZE, Game::APPLE_SIZE);

	rainbowTexture.clear();

	rainbowTexture.draw(rainbow);

	rainbowTexture.display();

	appleTexture = rainbowTexture.getTexture();

}

void PlayState::update()
{	

	if (clock.getElapsedTime().asMilliseconds() > 125 && !endOFGAME)//TODO poziomy trudnoœci
	{
		updateAppleRainbowTexture();

		if (snake->IsSelfBitting())
		{

			endOFGAME = true;
		}


		else if (!mapBounds.contains(snake->getHeadPosition()))
		{
			endOFGAME = true;
		}

		if (!endOFGAME) 
		{
			snake->Move();

			if (snake->GetHeadFloatRect() == apple->getGlobalBounds())
			{
				apple->setPosition(getRandomPosition()*(float)Game::APPLE_SIZE);
				snake->AddBodyPart();
			}

			clock.restart();
		}
	}
	
	if (endOFGAME)
		handleFailure();


}

void PlayState::handleFailure()
{
	music.setPitch(music.getPitch()*0.95);
	music.setVolume(music.getVolume() *0.95);

	if (!playFailureAnimation())switchToFailureScreen = true;

	if (alphaColorChannel < 120)
	{
		alphaColorChannel+=1;
		transparentBackgroundLayer.setFillColor(Color(0, 0, 0, alphaColorChannel));
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
	if (switchToFailureScreen)return Game::FAILURE;
	return STATE_ID;

}

void PlayState::render()
{
	_window->clear();

	for (unsigned int i = 0; i <mapTiles.size(); i++)
		_window->draw(mapTiles[i]);
	
	_window->draw(*apple);
	
	if(drawSnake)_window->draw(*snake);

	_window->draw(transparentBackgroundLayer);

	_window->display();
}

bool PlayState::playFailureAnimation()
{	
	static int animationCounter;
	static Clock clock;

	if (clock.getElapsedTime().asSeconds() > 0.3f && drawSnake)
	{
		drawSnake = false;
		clock.restart();
	}
	else if (clock.getElapsedTime().asSeconds() > 0.2f && !drawSnake)
	{
		drawSnake = true;
		clock.restart();
		animationCounter++;
	}

	if (animationCounter >= 3)
	{	
		animationCounter = 0;
		return false;
	}
	return true;
}