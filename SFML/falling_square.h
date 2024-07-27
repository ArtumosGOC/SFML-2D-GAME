#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


using namespace sf;
using namespace std;

class falling_square
{
private:

	RenderWindow* Win_;
	VideoMode videoMode_;
	Event event_;
	

	Clock clock;
	float FPS;
	float lastTime;
	float currentTime;
	bool endGame;
	unsigned int points;
	int health;
	float enemySpawnTimer_;
	float enemySpawnTimerMax_;
	int maxEnemies;
	bool mouseHeld;

	Font font;

	Text uiText;

	vector<RectangleShape> enemies;
	Vector2i mousePosWin_;
	Vector2f mousePosView_;

	RectangleShape enemy;

	void initializeVariables();
	void initializeWindow();
	void initEnemies();
	void initFonts();
	void initFPS();
	void initText();


	
	
public:

	falling_square();
	virtual ~falling_square();

	const bool getWinIsOpen() const;
	const bool getEndGame() const;

	void spawnEnemy();

	void pollEvents();

	void updateEnemies();
	void updatemousePos();
	void updateFPS();
	void updateText();
	void update();

	void renderText(RenderTarget& target);
	void renderEnemies(RenderTarget& target);
	void render();

};

