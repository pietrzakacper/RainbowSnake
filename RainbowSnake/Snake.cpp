#include "Snake.h"



const int BODY_SIZE = 32;
using namespace sf;

Snake::Snake()
	:hasDirectionChanged(false)
{
	RectangleShape head;
	head.setFillColor(Color(255, 10 * 1, 0, 70));
	head.setSize(Vector2f((float)BODY_SIZE, (float)BODY_SIZE));
	head.setPosition(640 / 2, 640 / 2);




	m_snakeParts.push_back(head);
	m_direction = DIR_UP;
}


Snake::~Snake()
{
}


void Snake::Move()
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
	Vector2f prevPos = m_snakeParts[0].getPosition();
	Vector2f offset(dir.x * BODY_SIZE, dir.y * BODY_SIZE);
	m_snakeParts[0].move(offset);

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
	RectangleShape bodyPart(Vector2f((float)BODY_SIZE, (float)BODY_SIZE));

	setRainbowColor(bodyPart);

	bodyPart.setOutlineThickness(-2.f);
	bodyPart.setSize(Vector2f((float)BODY_SIZE, (float)BODY_SIZE));
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
	bodyPartColor.a = 40;
	bodyPart.setFillColor(bodyPartColor);
	bodyPartColor.a = 60;
	bodyPart.setOutlineColor(bodyPartColor);
}

bool Snake::IsSelfBitting()
{
	FloatRect *head = &m_snakeParts[0].getGlobalBounds();
	FloatRect *body;

	for (unsigned int i = 1; i < m_snakeParts.size(); i++)
	{
		body = &m_snakeParts[i].getGlobalBounds();
		if (head->intersects( *body)) 
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

bool Snake::intersects(const Vector2f position)
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
	return m_snakeParts[0].getPosition();
}