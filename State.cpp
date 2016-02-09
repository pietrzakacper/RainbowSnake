#include "State.h"

State::State(int STATE_ID, sf::RenderWindow& window, Font& font)
	: STATE_ID(STATE_ID),
	_window(&window),
	_font(&font)
{

}

State::~State()
{
	
}

int State::getSTATE_ID() const
{
	return STATE_ID;
}