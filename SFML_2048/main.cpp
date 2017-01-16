#include  <SFML/Graphics.hpp>
#include <cassert>
#include <Windows.h>
#include "Game.h"

using namespace std;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	
	sf::RenderWindow window(sf::VideoMode(400, 500), "2048", sf::Style::Close | sf::Style::Titlebar);

	Game nowa(window);
	nowa.play();

	return 0;
}