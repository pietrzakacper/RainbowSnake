#include "MenuState.h"
#include <iostream>



MenuState::MenuState(int STATE_ID, RenderWindow& window, Font& font)
	:State(STATE_ID,window,font)
{
}


MenuState::~MenuState()
{
}

void MenuState::init()

{
	title.setString("RAINBOW SNAKE");
	title.setFont(*_font);
	title.setCharacterSize(86);
	title.setColor(Color::Cyan);
	title.setOrigin(Vector2f(title.getGlobalBounds().width / 2.f, title.getGlobalBounds().height / 2.f));
	title.setPosition(Vector2f((float)Game::SCRN_WIDTH / 2.f, (float)Game::APPLE_SIZE));

	menuOptions[0].setString("PLAY");
	menuOptions[0].setFont(*_font);
	menuOptions[0].setCharacterSize(64);
	menuOptions[0].setColor(Color::White);
	menuOptions[0].setOrigin(Vector2f(menuOptions[0].getGlobalBounds().width / 2.f, menuOptions[0].getGlobalBounds().height / 2.f));
	menuOptions[0].setPosition(Vector2f((float)Game::SCRN_WIDTH / 2.f, (float)Game::SCRN_HEIGHT / 2.f - (float)Game::APPLE_SIZE));

	menuOptions[1].setString("EXIT");
	menuOptions[1].setFont(*_font);
	menuOptions[1].setCharacterSize(64);
	menuOptions[1].setColor(Color::White);
	menuOptions[1].setOrigin(Vector2f(menuOptions[1].getGlobalBounds().width / 2.f, menuOptions[1].getGlobalBounds().height / 2.f));
	menuOptions[1].setPosition(Vector2f((float)Game::SCRN_WIDTH / 2.f - 5.f, (float)Game::SCRN_HEIGHT / 2.f + (float)Game::APPLE_SIZE));
}

int MenuState::handleEvents(Event& event)
{
	Vector2f mousePosition = Vector2f((float)Mouse::getPosition(*_window).x, (float)Mouse::getPosition(*_window).y);

	while (_window->pollEvent(event))
	{
		if (event.type == Event::Closed || (event.type == Event::MouseButtonReleased && menuOptions[1].getGlobalBounds().contains(mousePosition)))
			return Game::END;

		else if (event.type == Event::MouseButtonReleased && menuOptions[0].getGlobalBounds().contains(mousePosition))
			return Game::PLAY_STATE;
	}

	return STATE_ID;
}

void MenuState::update()
{
	Vector2f mousePosition = Vector2f((float)Mouse::getPosition(*_window).x, (float)Mouse::getPosition(*_window).y);

	for (int i = 0; i < 2; i++) 
	{
		if (menuOptions[i].getGlobalBounds().contains(mousePosition))
		{
			menuOptions[i].setColor(Color::Cyan);
		}
		else menuOptions[i].setColor(Color::White);
	}
}

void MenuState::render()
{
	_window->clear();

	_window->draw(title);

	for (int i = 0; i < 2; i++)
		_window->draw(menuOptions[i]);

	_window->display();

}