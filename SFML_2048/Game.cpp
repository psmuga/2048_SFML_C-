#include "Game.h"

unsigned int Game::score = 0;
unsigned int Game::highScore = 0;
sf::Font Game::font = sf::Font();


float Game::padding = 10.f;
float Game::gridSize = (400.f - (padding * 2.f));
float Game::tileSize = (gridSize - (5 * padding)) / 4;

sf::Text Game::titleText = sf::Text("2048", font, 48);
sf::Text Game::gameOverText = sf::Text("Game Over!", font, 50);
sf::Text Game::scoreText = sf::Text(std::to_string(score), font, 32);
sf::Text Game::scoreDecoratorText = sf::Text("", font, 15);
sf::Text Game::tileText = sf::Text("", font);

sf::RectangleShape Game::gridBackgroundRect(sf::Vector2f(gridSize, gridSize));
sf::RectangleShape Game::gameOverBackground(sf::Vector2f(gridSize, gridSize));
sf::RectangleShape Game::gridTile(sf::Vector2f(tileSize, tileSize));

sf::Color Game::windowBGColour = sf::Color(255, 245, 201, 255);
sf::Color Game::gridBGColour = sf::Color(54, 138, 255, 255);
sf::Color Game::textColour = sf::Color(67, 53, 40, 255);

void Game::reset()
{
	if (score > highScore)
	{
		highScore = score;
		try
		{
			File::WriteToFile(highScore);
		}
		catch (exception& rhs)
		{
			MessageBoxA(nullptr, rhs.what(), "error", MB_ICONERROR | MB_OK);
		}		
	}
	score = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			boardTable.gridTable[i][j].setValue(0);
		}
	}
	showGameOver = false;
	boardTable.addNumber();
	boardTable.addNumber();
}

bool Game::isGameOver() const
{
	if (boardTable.getEmptyCells().size() > 0 || boardTable.getMovesLeft() > 0) 
		return false;	
	else 
		return true;
}

void Game::RenderScoreInfo() const
{
	scoreText.setString(to_string(score));
	scoreText.setPosition(sf::Vector2f(350 - 70, 30));
	window.draw(scoreText);
	scoreDecoratorText.setString("score:");
	scoreDecoratorText.setPosition(sf::Vector2f(scoreText.getPosition().x - scoreDecoratorText.getGlobalBounds().width - 5, 47));
	window.draw(scoreDecoratorText);
	scoreDecoratorText.setString("highscore: " + to_string(highScore));
	scoreDecoratorText.setPosition(sf::Vector2f(scoreDecoratorText.getPosition().x, 72));
	window.draw(scoreDecoratorText);
}

void Game::RenderBoard() const
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) 
		{
			gridTile.setPosition(sf::Vector2f(20 + (i * (tileSize + padding)), 120 + (j * (tileSize + padding))));
			gridTile.setFillColor(boardTable.gridTable[i][j].getColor());
			window.draw(gridTile);

			if (boardTable.gridTable[i][j].getValue() > 0) 
			{
				tileText.setString(std::to_string(boardTable.gridTable[i][j].getValue()));
				sf::Vector2f textPosition = (gridTile.getPosition() + (gridTile.getSize() / 2.f));
				textPosition.x -= tileText.getGlobalBounds().width / 2.f;
				textPosition.y -= (tileText.getGlobalBounds().height + padding) / 2.f;
				tileText.setPosition(textPosition);
				window.draw(tileText);
			}
		}
	}
}

void Game::RenderGamerOver() const
{
	gameOverBackground.setFillColor(sf::Color(250, 248, 239, 175));
	gameOverBackground.setPosition(sf::Vector2f(10, 110));
	gameOverText.setStyle(sf::Text::Bold);
	gameOverText.setFillColor(textColour);
	gameOverText.setPosition(sf::Vector2f(60, 265));

	window.draw(gameOverBackground);
	window.draw(gameOverText);
	scoreDecoratorText.setString("Press enter to restart");
	scoreDecoratorText.setPosition(sf::Vector2f(gameOverText.getPosition().x + 57, gameOverText.getPosition().y + gameOverText.getLocalBounds().height + padding * 2));
	window.draw(scoreDecoratorText);
}

void Game::renderScreen() const
{
	window.clear(windowBGColour);
	window.draw(gridBackgroundRect);
	RenderBoard();
	RenderScoreInfo();
	if (showGameOver)
		RenderGamerOver();

	window.draw(titleText);
	window.display();
}

void Game::play()
{
	auto moveDone = false;
	auto scheduledNumberAdd = false;
	sf::Clock clock;
	clock.restart();
	sf::Time addTimeout = sf::milliseconds(75);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed && !moveDone && !scheduledNumberAdd)
			{
				unsigned char tilesMoved = 0;
				unsigned int help = 0;
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					tie(tilesMoved, help) = boardTable.moveUp();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					tie(tilesMoved, help) = boardTable.moveRight();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					tie(tilesMoved, help) = boardTable.moveDown();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					tie(tilesMoved, help) = boardTable.moveLeft();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
				{
					showGameOver = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					reset();
					continue;
				}
				moveDone = true;
				score += help;
				if (tilesMoved > 0) 
				{
					scheduledNumberAdd = true;
					clock.restart();
				}
			}
			if (event.type == sf::Event::KeyReleased && moveDone)
			{
				if (isGameOver())
					showGameOver = true;
				moveDone = false;
			}
		}
		if (scheduledNumberAdd && clock.getElapsedTime() > addTimeout)
		{
			boardTable.addNumber();
			scheduledNumberAdd = false;
		}
		renderScreen();
	}
}

Game::Game(sf::RenderWindow& A): window(A)
{
	showGameOver = false;
	boardTable =  Board();	
	try
	{
		font.loadFromFile("files/atwriter.ttf");
	}
	catch (...)
	{
		MessageBoxA(nullptr, "Font fail!", "error", MB_ICONERROR | MB_OK);
	}
	try
	{
		highScore = File::ReadFromFile();
	}
	catch (const exception& rhs)
	{
		MessageBoxA(nullptr, rhs.what(), "error", MB_ICONERROR | MB_OK);
		highScore = 0;
	}

	gridBackgroundRect.setFillColor(gridBGColour);
	gridBackgroundRect.setPosition(sf::Vector2f(10, 110));

	titleText.setStyle(sf::Text::Bold);
	titleText.setFillColor(textColour);
	titleText.setPosition(sf::Vector2f(10, 25));

	scoreText.setStyle(sf::Text::Bold);
	scoreText.setFillColor(textColour);
	scoreDecoratorText.setFillColor(textColour);

	tileText.setFont(font);
	tileText.setCharacterSize(32);
	tileText.setStyle(sf::Text::Bold);
	tileText.setFillColor(textColour);

	reset();
}

Game::~Game()
{
}
