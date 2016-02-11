#include "FailureState.h"



FailureState::FailureState(int STATE_ID, RenderWindow& window, Font& font, Image& image)
	:State(STATE_ID,window,font)
{
	
	backgroundTexture.loadFromImage(image);
	backgroundImage.setTexture(backgroundTexture);

}


FailureState::~FailureState()
{
}

void FailureState::init()
{

	title.setString("YOU LOOSE!");
	title.setFont(*_font);
	title.setCharacterSize(86);
	title.setColor(Color::Cyan);
	title.setOrigin(Vector2f(title.getGlobalBounds().width / 2.f, title.getGlobalBounds().height / 2.f));
	title.setPosition(Vector2f(Game::SCRN_WIDTH/2.f, (float)Game::APPLE_SIZE));

	const int howManyMenuOptions = 2;

	string menuOptionsStrings[howManyMenuOptions] = { "PLAY AGAIN", "RETURN TO MENU" };
	for (int i = 0; i < howManyMenuOptions; i++)
	{
		menuOptions[i].setString(menuOptionsStrings[i]);
		menuOptions[i].setFont(*_font);
		menuOptions[i].setCharacterSize(64);
		menuOptions[i].setColor(Color::White);
		menuOptions[i].setOrigin(Vector2f(menuOptions[i].getGlobalBounds().width / 2.f, menuOptions[i].getGlobalBounds().height / 2.f));
		menuOptions[i].setPosition(Vector2f((float)Game::SCRN_WIDTH / 2.f, (float)Game::SCRN_HEIGHT / 2.f - (float)Game::APPLE_SIZE + 2.5* (float)i*(float)Game::APPLE_SIZE));
	}


	
}

void FailureState::update()
{
	Vector2f mousePosition = Vector2f((float)Mouse::getPosition(*_window).x, (float)Mouse::getPosition(*_window).y);

	for (int i = 0; i < 2; i++)
	{
		if (menuOptions[i].getGlobalBounds().contains(mousePosition))
			menuOptions[i].setColor(sf::Color::Cyan);
		else menuOptions[i].setColor(sf::Color::White);
	}
	
}

int FailureState::handleEvents(Event& event)
{

	Vector2f mousePosition = Vector2f((float)Mouse::getPosition(*_window).x, (float)Mouse::getPosition(*_window).y);

	while (_window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			return Game::END;

		else if (event.type == Event::MouseButtonReleased && menuOptions[0].getGlobalBounds().contains(mousePosition))
		{
			cout << "Zwracam PLAT_STATE" << endl;
			return Game::PLAY_STATE;
		}
		else if (event.type == Event::MouseButtonReleased && menuOptions[1].getGlobalBounds().contains(mousePosition))
			return Game::MENU;
	}

	return STATE_ID;
}

void FailureState::render()
{	
	_window->clear();

	_window->draw(backgroundImage);

	

	_window->draw(title);

	for (int i = 0; i < 2; i++)
		_window->draw(menuOptions[i]);

	_window->display();
}