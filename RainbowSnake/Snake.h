#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Snake : public Drawable
{
public:
	Snake();
	~Snake();

	enum Direction {
		DIR_UP, DIR_DOWN, DIR_LEFT = 3, DIR_RIGHT
	};

	void Move();
	void ChangeDirection(Direction dir);
	void AddBodyPart();
	void setRainbowColor(RectangleShape& bodyPart);
	Texture rainbowTexture;
	Texture getRainbowTexture();
	bool IsSelfBitting();
	bool hasDirectionChanged;
	FloatRect GetHeadFloatRect() const;
	Vector2f getHeadPosition();
	bool intersects(const Vector2f& position);
	void update();
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

private:
	std::vector <sf::RectangleShape> m_snakeParts;
	Direction m_direction;
};

