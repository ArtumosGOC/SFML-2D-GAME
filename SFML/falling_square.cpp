#include "falling_square.h"

void falling_square::initializeVariables()
{
	this->Win_ = nullptr;

	unsigned int points;
	float enemySpawnTimer_;
	float enemySpawnTimerMax_;
	int maxEnemies;
	int Health;
	bool endGame;
	Clock clock;
	float FPS;
	float lastTime;
	float currentTime;

	this->FPS = 0.f;
	this->points = 1;
	this->enemySpawnTimerMax_ = 20.f;
	this->enemySpawnTimer_ = this->enemySpawnTimerMax_;
	this->maxEnemies = 20;
	this->mouseHeld = 0b0;
	this->health = 10;
	this->endGame = 0b0;
}

void falling_square::initializeWindow()
{
	this->videoMode_.height = 600;
	this->videoMode_.width = 800;

	this->Win_ = new RenderWindow(this->videoMode_, "SFML Framework", Style::Titlebar|Style::Close);
	this->Win_->setFramerateLimit(60);
	this->Win_->setVerticalSyncEnabled(0b0);
}

void falling_square::initEnemies()
{
	this->enemy.setPosition(10.0f, 10.0f);
	this->enemy.setSize(Vector2f(100.0f, 100.0f));
	this->enemy.setScale(Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(Color::Cyan);
	//this->enemy.setOutlineColor(Color::Green);
	//this->enemy.setOutlineThickness(1.f);
}

void falling_square::initFonts()
{
	if (!this->font.loadFromFile("Fonts/FetteClassicUNZFraktur.ttf"))//if (!this->font.loadFromFile("Fonts/ConnectionIii-Rj3W.otf"))
	{
		cout << "ERROR::GAME::INITFONTS::Failed to load font" << endl;
	}
}

void falling_square::initFPS()
{
	this->lastTime = 0.f;
	this->currentTime = this->clock.restart().asSeconds();
	this->FPS = 1.f / (this->currentTime - this->lastTime);
	this->lastTime = this->currentTime;
}

void falling_square::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(Color::White);
	this->uiText.setString("NONE");

}

falling_square::falling_square()
{
	this->initializeVariables();
	this->initializeWindow();
	this->initEnemies();
	this->initFonts();
	this->initText();
	this->initFPS();
}

falling_square::~falling_square()
{
	this->Win_->clear();
	delete this->Win_;
}

const bool falling_square::getWinIsOpen() const
{
	return this->Win_->isOpen();	
}

const bool falling_square::getEndGame() const
{
	return this->endGame;
}

void falling_square::spawnEnemy()
{
	//this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>(this->Win_->getSize().x - this->enemy.getSize().x)), 
	//	                    static_cast<float>(rand() % static_cast<int>(this->Win_->getSize().y - this->enemy.getSize().y)));

	this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>(this->Win_->getSize().x - this->enemy.getSize().x)), 0.f);

	int type = rand() % 6;

	switch (type)
	{
		case 0:
			this->enemy.setSize(Vector2f(20.0f, 20.0f));
			this->enemy.setFillColor(Color::Magenta);
			break;
		case 1:
			this->enemy.setSize(Vector2f(30.0f, 30.0f));
			this->enemy.setFillColor(Color::Blue);
			break;
		case 2:
			this->enemy.setSize(Vector2f(50.0f, 50.0f));
			this->enemy.setFillColor(Color::Red);
			break;
		case 3:
			this->enemy.setSize(Vector2f(60.0f, 60.0f));
			this->enemy.setFillColor(Color::Yellow);
			break;
		case 4:
			this->enemy.setSize(Vector2f(80.0f, 80.0f));
			this->enemy.setFillColor(Color::Cyan);
			break;
		case 5:
			this->enemy.setSize(Vector2f(100.0f, 100.0f));
			this->enemy.setFillColor(Color::Green);
			break;
	}
	this->enemies.push_back(this->enemy);
}

void falling_square::pollEvents()
{
	while (this->Win_->pollEvent(this->event_))
	{
		switch (event_.type)
		{
		case Event::Closed:
			this->Win_->close();
			break;
		case Event::KeyPressed:
			if (event_.key.code == Keyboard::Escape)
				this->Win_->close();
			break;
		}
	}
}

void falling_square::updateEnemies()
{
	
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer_ >= this->enemySpawnTimerMax_)
		{
			this->spawnEnemy();
			this->enemySpawnTimer_ = 0.f;
		}
		else
			this->enemySpawnTimer_ += 1.f;
	}

	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].move(0.f, points*0.01f);
		if (this->enemies[i].getPosition().y > this->Win_->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			if (this->enemies[i].getFillColor() == Color::Magenta)
			{
				this->health -= 1;
			}
			else if (this->enemies[i].getFillColor() == Color::Blue)
			{
				this->health -= 2;
			}
			else if (this->enemies[i].getFillColor() == Color::Red)
			{
				this->health -= 3;
			}
			else if (this->enemies[i].getFillColor() == Color::Yellow)
			{
				this->health -= 5;
			}
			else if (this->enemies[i].getFillColor() == Color::Cyan)
			{
				this->health -= 7;
			}
			else if (this->enemies[i].getFillColor() == Color::Green)
			{
				this->health -= 8;
			}
		}
		for(int j = 0; j < this->enemies.size(); j++)
		{
			if (this->enemies[i].getGlobalBounds().intersects(this->enemies[j].getGlobalBounds()) && i != j)
			{
				this->enemies.erase(this->enemies.begin() + j);
			}
		}
	}

	if(Mouse::isButtonPressed(Mouse::Left))
	{
		if (!this->mouseHeld)
		{
			this->mouseHeld = 0b1;
			bool deleted = 0b0;
			for (size_t i = 0; i < this->enemies.size(); i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView_))
				{
					if (this->enemies[i].getFillColor() == Color::Magenta)
					{
						this->health += 10;
						this->points += 20;
					}
					else if (this->enemies[i].getFillColor() == Color::Blue)
					{
						this->health += 7;
						this->points += 14;
					}
					else if (this->enemies[i].getFillColor() == Color::Red)
					{
						this->health += 5;
						this->points += 10;
					}
					else if (this->enemies[i].getFillColor() == Color::Yellow)
					{
						this->health += 3;
						this->points += 6;
					}
					else if (this->enemies[i].getFillColor() == Color::Cyan)
					{
						this->health += 2;
						this->points += 4;
					}
					else if (this->enemies[i].getFillColor() == Color::Green)
					{
						this->health += 1;
						this->points += 1;
					}

					deleted = 0x01;
					this->health += 1;
					this->enemies.erase(this->enemies.begin() + i);
					
				}	
			}
		}
	}
	else
	{
		this->mouseHeld = 0b0;
	}
	cout << "Points: " << this->points << " || " << "Health: " << this->health << endl;
}

void falling_square::updatemousePos()
{
		this->mousePosWin_ = Mouse::getPosition(*this->Win_);
		this->mousePosView_ = this->Win_->mapPixelToCoords(this->mousePosWin_);
}

void falling_square::updateFPS()
{
	this->lastTime = 0.f;
	this->currentTime = this->clock.restart().asSeconds();
	this->FPS = 1.f / (this->currentTime - this->lastTime);
	this->lastTime = this->currentTime;
}

void falling_square::updateText()
{
	stringstream ss;
	ss << "Points: \t" << this->points << " \n" << "Health: \t" << this->health << " \n" << 
		"FPS: \t" << (round(this->FPS * 100.0) / 100.0);
	ss.precision(2);
	this->uiText.setString(ss.str());
}

void falling_square::update()
{
	this->pollEvents();
	if (!this->endGame)
	{
	this->updatemousePos();
	this->updateText();
	this->updateFPS();
	this->updateEnemies();
	}
	if (this->health <= 0)
	{
		this->endGame = 0b1;
		cout << "Game Over" << endl;
		cout << "Points: " << this->points << endl;
	}
}

void falling_square::renderText(RenderTarget& target)
{
	target.draw(this->uiText);
}

void falling_square::renderEnemies(RenderTarget& target)
{
	for (auto &e: this->enemies)
	{
		target.draw(e);
	}
}

void falling_square::render()
{
	this->Win_->clear();
	this->renderEnemies(*this->Win_);
	this->renderText(*this->Win_);
	this->Win_->display();
}
