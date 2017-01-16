#include "Board.h"


void Board::addNumber()
{
	int newCellOptions[2] = { 2, 4 };
	vector<sf::Vector2i> puste = getEmptyCells();
	if (puste.size() == 0) {
		return;
	}
	else {
		int randEmpty = rand() % puste.size();
		gridTable[puste.at(randEmpty).x][puste.at(randEmpty).y].setValue(newCellOptions[rand() % 2]);
	}
}

vector<sf::Vector2i> Board::getEmptyCells() const
{
	vector<sf::Vector2i> freeElements;
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			if (gridTable[i][j].getValue() == 0) {
				freeElements.push_back(sf::Vector2i(i, j));
			}
		}
	}
	return freeElements;
}

unsigned Board::getMovesLeft() const
{
	auto movesLeft = 0;
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			if (gridTable[i][j].getValue() > 0)
			{
				if (i + 1 < 4 && (gridTable[i][j].getValue() == gridTable[i + 1][j].getValue() || gridTable[i + 1][j].getValue() == 0))
				{
					movesLeft++;
				}
				if (j + 1 < 4 && (gridTable[i][j].getValue() == gridTable[i][j + 1].getValue() || gridTable[i][j + 1].getValue() == 0))
				{
					movesLeft++;
				}
			}
		}
	}
	return movesLeft;
}

unsigned int Board::combine(deque<int>& cellList)
{
	if (cellList.size() < 2)
	{
		return 0;
	}
	unsigned int pomoc = 0;
	unsigned int index = 0;
	while (index < cellList.size() - 1)
	{
		unsigned int cell1 = cellList.at(index);
		unsigned int cell2 = cellList.at(index + 1);

		if (cell1 == cell2)
		{
			cellList.at(index) = cell1 * 2;
			pomoc += cellList.at(index);
			cellList.erase(cellList.begin() + index + 1);
		}

		index++;
	}

	return pomoc;
}

tuple<unsigned int,unsigned int> Board::moveDown()
{
	unsigned int tilesMoved = 0;
	unsigned int scorehelp = 0;
	for (int i = 0; i < 4; i++)
	{
		deque<int> cellList;
		for (int j = 3; j >= 0; j--)
		{
			if (gridTable[i][j].getValue() != 0) {
				cellList.push_back(gridTable[i][j].getValue());
			}
		}
		scorehelp += combine(cellList);

		unsigned int tileBefore;
		for (int k = 3; k >= 0; k--)
		{
			tileBefore = gridTable[i][k].getValue();

			if (cellList.size() > 0)
			{
				gridTable[i][k].setValue(cellList.front());
				cellList.pop_front();
			}
			else
			{
				gridTable[i][k].setValue(0);
			}

			if (gridTable[i][k].getValue() != tileBefore)
			{
				tilesMoved++;
			}
		}
	}
	return make_tuple(tilesMoved, scorehelp);
}

tuple<unsigned, unsigned> Board::moveUp()
{
	unsigned int tilesMoved = 0;
	unsigned int scorehelp = 0;
	for (int i = 0; i < 4; i++)
	{
		deque<int> cellList;
		for (int j = 0; j < 4; j++)
		{
			if (gridTable[i][j].getValue() != 0)
			{
				cellList.push_back(gridTable[i][j].getValue());
			}
		}
		scorehelp += combine(cellList);

		unsigned int tileBefore;
		for (int k = 0; k < 4; k++)
		{
			tileBefore = gridTable[i][k].getValue();

			if (cellList.size() > 0)
			{
				gridTable[i][k].setValue(cellList.front());
				cellList.pop_front();
			}
			else {
				gridTable[i][k].setValue(0);
			}

			if (gridTable[i][k].getValue() != tileBefore)
			{
				tilesMoved++;
			}
		}
	}
	return make_tuple(tilesMoved, scorehelp);
}

tuple<unsigned, unsigned> Board::moveLeft()
{
	unsigned int tilesMoved = 0;
	unsigned int scorehelp = 0;
	for (int i = 0; i < 4; i++)
	{
		deque<int> cellList;
		for (int j = 0; j < 4; j++)
		{
			if (gridTable[j][i].getValue() != 0)
			{
				cellList.push_back(gridTable[j][i].getValue());
			}
		}
		scorehelp += combine(cellList);

		unsigned int tileBefore;
		for (int k = 0; k < 4; k++)
		{
			tileBefore = gridTable[k][i].getValue();

			if (cellList.size() > 0)
			{
				gridTable[k][i].setValue(cellList.front());
				cellList.pop_front();
			}
			else
			{
				gridTable[k][i].setValue(0);
			}

			if (gridTable[k][i].getValue() != tileBefore)
			{
				tilesMoved++;
			}
		}
	}
	return make_tuple(tilesMoved, scorehelp);
}

tuple<unsigned, unsigned> Board::moveRight()
{
	unsigned int tilesMoved = 0;
	unsigned int scorehelp = 0;
	for (int i = 0; i < 4; i++)
	{
		std::deque<int> cellList;
		for (int j = 3; j >= 0; j--) {
			if (gridTable[j][i].getValue() != 0) {
				cellList.push_back(gridTable[j][i].getValue());
			}
		}
		scorehelp += combine(cellList);

		unsigned int tileBefore;
		for (int k = 3; k >= 0; k--)
		{
			tileBefore = gridTable[k][i].getValue();

			if (cellList.size() > 0)
			{
				gridTable[k][i].setValue(cellList.front());
				cellList.pop_front();
			}
			else
			{
				gridTable[k][i].setValue(0);
			}

			if (gridTable[k][i].getValue() != tileBefore)
			{
				tilesMoved++;
			}
		}
	}
	return make_tuple(tilesMoved, scorehelp);
}





Board::Board(const Board& rhs)
{
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			gridTable[i][j] = rhs.gridTable[i][j];
		}
	}
}

Board::Board()
{
	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
		{
			gridTable[i][j] = Block();
		}
	}
}



