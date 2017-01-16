#pragma once
#include <SFML/Graphics.hpp>
#include <map>
using namespace std;
class Block
{
	unsigned int value;
	sf::Color color;
	
	static map<int, sf::Color> numberColours;
public:
	void setValue(unsigned int rhs);
	void setColor(unsigned int rhs);
	unsigned int getValue() const;
	sf::Color getColor() const;

	Block();
	~Block() = default;
};

