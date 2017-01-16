#pragma once
#include  "Block.h"
#include <deque>
#include <tuple>

using namespace std;

class Board
{
	friend class Game;
	Block gridTable[4][4];
	void addNumber();
	vector<sf::Vector2i> getEmptyCells() const;
	unsigned int getMovesLeft() const;
	unsigned int combine(deque<int>& cellList);

	tuple<unsigned int, unsigned int> moveDown();
	tuple<unsigned int, unsigned int> moveUp();
	tuple<unsigned int, unsigned int> moveLeft();
	tuple<unsigned int, unsigned int> moveRight();
public:
	Board(const Board &rhs);
	Board();
	~Board() = default;
};

