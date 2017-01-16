#pragma once
#include  <SFML/Graphics.hpp>
#include <cassert>
#include <map>
#include <utility>
#include <Windows.h>
#include  "File.h"
#include "Board.h"
#include <tuple>

using namespace std;

class Game
{
	Board  boardTable;
	sf::RenderWindow& window;

	bool showGameOver;
	static sf::Font font;
	static unsigned int score;
	static unsigned int highScore;	

	static sf::Text titleText;
	static sf::Text gameOverText;
	static sf::Text scoreText;
	static sf::Text scoreDecoratorText;
	static sf::Text tileText;

	static float padding;
	static float gridSize;
	static float tileSize;

	static sf::RectangleShape gridBackgroundRect;
	static sf::RectangleShape gameOverBackground;
	static sf::RectangleShape gridTile;

	static sf::Color windowBGColour;
	static sf::Color gridBGColour;
	static sf::Color textColour;

	void reset();
	bool isGameOver() const;
	void RenderScoreInfo() const;
	void RenderBoard() const;
	void RenderGamerOver() const;
	void renderScreen() const;

public:
	void play();
	Game(sf::RenderWindow & A);
	~Game();
};

