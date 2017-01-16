#include "Block.h"

map<int, sf::Color> Block::numberColours = {
	{0,sf::Color(65, 99, 255, 255) },
	{2,sf::Color(238, 228, 218, 255) },
	{4,sf::Color(237, 224, 200, 255) },
	{8,sf::Color(242, 177, 121, 255) },
	{16,sf::Color(245, 149, 99, 255) },
	{32,sf::Color(246, 124, 95, 255) },
	{64,sf::Color(246, 94, 59, 255) },
	{128,sf::Color(237, 207, 114, 255) },
	{256,sf::Color(237, 204, 97, 255) },
	{512,sf::Color(237, 200, 80, 255) },
	{1024,sf::Color(237, 197, 63, 255) },
	{2048,sf::Color(237, 194, 46, 255) }
};

void Block::setValue(unsigned int rhs)
{
	this->value = rhs;
	this->setColor(this->value);
}

void Block::setColor(unsigned int rhs)
{
	color = numberColours[rhs];
}

unsigned int Block::getValue() const
{
	return this->value;
}

sf::Color Block::getColor() const
{
	return this->color;
}

Block::Block()
{
	value = 0;
	setColor(0);
}


