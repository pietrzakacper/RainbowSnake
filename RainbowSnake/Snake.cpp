#include "Snake.h"
#include "Game.h"



using namespace sf;

Snake::Snake()
	:hasDirectionChanged(false)
{
	RectangleShape head;
	head.setFillColor(Color(255, 10 * 1, 0, 120));
	head.setSize(Vector2f((float)Game::APPLE_SIZE, (float)Game::APPLE_SIZE));
	head.setPosition(Game::SCRN_WIDTH/ 2, Game::SCRN_HEIGHT / 2);




	m_snakeParts.push_back(head);
	m_direction = DIR_UP;
}


Snake::~Snake()
{
}

Vector2f Snake::getDirection()
{

	Vector2f dir(0.f, 0.f);

	switch (m_direction)
	{
	case DIR_LEFT:
		dir.x = -1;
		break;

	case DIR_RIGHT:
		dir.x = 1;
		break;

	case DIR_UP:
		dir.y = -1;
		break;

	case DIR_DOWN:
		dir.y = 1;
		break;

	default:
		exit(-1);
		break;
	}
	hasDirectionChanged = false;
	return dir;
}

Vector2f Snake::getMovement()
{
	Vector2f direction = getDirection();
	Vector2f offset(direction.x * Game::APPLE_SIZE, direction.y * Game::APPLE_SIZE);
	return offset;
}

void Snake::Move()
{
	Vector2f prevPos = m_snakeParts[0].getPosition();
	m_snakeParts[0].move(getMovement());

	for (unsigned int i = 1; i < m_snakeParts.size(); i++)
	{
		Vector2f tmp = m_snakeParts[i].getPosition();
		m_snakeParts[i].setPosition(prevPos);
		prevPos = tmp;
	}
}


void Snake::ChangeDirection(Direction dir)
{
	if (std::abs(dir - m_direction) > 1 && !hasDirectionChanged)
	{
		m_direction = dir;
		hasDirectionChanged = true;
	}
}


void Snake::AddBodyPart()
{
	RectangleShape bodyPart(Vector2f((float)Game::APPLE_SIZE, (float)Game::APPLE_SIZE));

	setRainbowColor(bodyPart);

	bodyPart.setOutlineThickness(-2.f);
	bodyPart.setSize(Vector2f((float)Game::APPLE_SIZE, (float)Game::APPLE_SIZE));
	bodyPart.setPosition(-32, -32);
	m_snakeParts.push_back(bodyPart);
}

void Snake::setRainbowColor(RectangleShape& bodyPart)
{
	Color bodyPartColor;

	switch ((int)((m_snakeParts.size() - 1) % 150) / 25)
	{
	case 0:
		bodyPartColor = Color(255, 10 * ((m_snakeParts.size() - 1) % 25), 0);
		break;
	case 1:
		bodyPartColor = Color(255 - 10 * ((m_snakeParts.size() - 1) % 25), 255, 0);
		break;
	case 2:
		bodyPartColor = Color(0, 255, 10 * ((m_snakeParts.size() - 1) % 25));
		break;
	case 3:
		bodyPartColor = Color(0, 255 - 10 * ((m_snakeParts.size() - 1) % 25), 255);
		break;
	case 4:
		bodyPartColor = Color(10 * ((m_snakeParts.size() - 1) % 25), 0, 255);
		break;
	case 5:
		bodyPartColor = Color(255, 0, 255 - 10 * ((m_snakeParts.size() - 1) % 25));
		break;

	}
	bodyPartColor.a = 60;
	bodyPart.setFillColor(bodyPartColor);
	bodyPartColor.a = 80;
	bodyPart.setOutlineColor(bodyPartColor);
}

bool Snake::IsSelfBitting()
{	
	const Vector2f* head = &m_snakeParts[0].getPosition();
	const Vector2f* body;
	const Vector2f movement = getMovement();
	for (unsigned int i = 1; i < m_snakeParts.size(); i++)
	{
		body = &m_snakeParts[i].getPosition();
		if (*head + movement == *body)
		{
			return true;
		}
	}

	return false;
}

FloatRect Snake::GetHeadFloatRect() const
{
	return m_snakeParts[0].getGlobalBounds();
}

bool Snake::intersects(const Vector2f& position)
{
	for (unsigned int i = 0; i < m_snakeParts.size(); i++)
	{
		if (m_snakeParts[i].getPosition() == position)
		{
			return true;
		}
	}
	return false;
}



void Snake::draw(RenderTarget & target, RenderStates states) const
{
	for (unsigned int i = 0; i < m_snakeParts.size(); i++)
	{
		target.draw(m_snakeParts[i]);
	}

}

Vector2f Snake::getHeadPosition()
{
	return m_snakeParts[0].getPosition() + getMovement();
}

void Snake::update()
{
	//TODO snake update
}

Texture Snake::getRainbowTexture()
{
	static Clock textureClock;

	VertexArray headRectangle = VertexArray(Quads, 4);
	int alpha = 150;

	if (textureClock.getElapsedTime().asSeconds() > 25.5f)textureClock.restart();

	headRectangle[0].color = Color(10*textureClock.getElapsedTime().asSeconds() + 10, 0,0, alpha);
	headRectangle[1].color = Color(10*textureClock.getElapsedTime().asSeconds(), 10* textureClock.getElapsedTime().asSeconds()+ 10, 0, alpha);
	headRectangle[2].color = Color(0, 10 * textureClock.getElapsedTime().asSeconds() + 10,0, alpha);
	headRectangle[3].color = Color(0, 0, 10 * textureClock.getElapsedTime().asSeconds() +10, alpha);
	headRectangle[0].position = Vector2f(0, 0);
	headRectangle[1].position = Vector2f(Game::APPLE_SIZE, 0);
	headRectangle[2].position = Vector2f(Game::APPLE_SIZE, Game::APPLE_SIZE);
	headRectangle[3].position = Vector2f(0, Game::APPLE_SIZE);


	RenderTexture renderTexture;
	renderTexture.create(Game::APPLE_SIZE, Game::APPLE_SIZE);

	renderTexture.clear();
	
		renderTexture.draw(headRectangle);
	renderTexture.display();

	return renderTexture.getTexture();
}
