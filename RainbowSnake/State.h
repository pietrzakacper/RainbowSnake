#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class State
{
public:
	State(int STATE_ID, RenderWindow&, Font& font);
	virtual ~State();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual int handleEvents(Event&) = 0;
	virtual void render() = 0;
	int getSTATE_ID() const;

protected:
	Font* _font;
	RenderWindow* _window;
	const int STATE_ID;
};


