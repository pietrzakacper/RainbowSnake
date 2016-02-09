#include <SFML\Graphics.hpp> 

using namespace sf;
using namespace std;

class State
{
public:

	State(int STATE_ID, sf::RenderWindow&, Font& font);
	virtual ~State();
	virtual void init() = 0;
	virtual void update() = 0;
	virtual int handleEvents(sf::Event&) = 0;
	virtual void render() = 0;
	int getSTATE_ID() const;

protected:
	Font* _font;
	sf::RenderWindow* _window;
	const int STATE_ID;
};