#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <math.h>

#include "Structures.h"
#include "Asteroid.h"
#include "Spaceship.h"
#include "Missile.h"
#include "Score.h"
#include "GameEngine.h"
#include "SaveFile.h"
#include "Boss.h"
#include "Server.h"
#include "Heart.h"
#include "TargetMissile.h"

using namespace sf;
using namespace std;

void startGame(RenderWindow &game, Sprite *background, bool multiplayer, SoundBuffer *buffer, SoundBuffer *dejavuBuffer) {
	// Init

	Event event;
	game.setFramerateLimit(60);
	initRandom();

	Asteroid asteroids[ASTEROIDS_TABLE_LENGTH];
	Missile missiles[MISSILE_TABLE_LENGTH];
	Missile bossMissiles[MISSILE_TABLE_LENGTH];

	noAsteroidExist(asteroids);
	initMissiles(missiles);
	if (!multiplayer)
		initMissiles(bossMissiles);

	Heart heart;
	initHeart(heart);
	TargetMissile targetMissile;
	initTargetMissile(targetMissile);

	Spaceship spaceship1;
	Spaceship spaceship2;
	Spaceship boss;

	Font font;
	font.loadFromFile("res/Righteous-Regular.ttf");

	Sound sound;
	sound.setBuffer(*buffer);
	sound.play();

	int compteurFramesAvecDrift;
	int lastCompteurFramesAvecDrift = 0;

	Sound dejavu;
	dejavu.setBuffer(*dejavuBuffer);

	int frames = 0;
	int bossWillCome = 0;
	
	float secsInterval = INITIAL_SPAWN_INTERVAL;
	bool initGame = true, reduce = true;

	int timeElapsedSinceLastShoot = 0;
	int bossTimeElapsedSinceLastShoot = 0;
	int score = 0;

	initSpaceship(1, spaceship1);
	IpAddress ipAddress = "127.0.0.1";
	unsigned short port = 1234;
	if (multiplayer) {
		initSpaceship(2, spaceship2);
		cout << "Adresse IP : ";
		cin >> ipAddress;
		if (ipAddress.toString() == "") {
			ipAddress = "127.0.0.1";
		}
	}
	else
		bossInit(3, boss);


	// INITIALISATION DE STATIQUES DANS LES FONCTIONS
	updateSpaceship(game, spaceship1, true, multiplayer);
	speedSpaceship(spaceship1, Keyboard::Unknown, true);
	shoot(spaceship1, missiles, &timeElapsedSinceLastShoot, true, multiplayer);
	

	if (multiplayer) {
		startListener(ipAddress, port, asteroids, missiles, spaceship1, spaceship2);
		sendConnectionRequest();
		
		printf("Waiting for another client to connect...\n"); //really shlag code to wait for the other thread to find a client
		asteroids[0].exists = 0;

		while (asteroids[0].exists == 0)
		{
			game.pollEvent(event);
			//printf("Waiting for another client to connect...\n");
		}
		asteroids[0].exists = 0;
	}

	// Game loop
	while (spaceship1.isAlive || (multiplayer && spaceship2.isAlive)) {
		game.clear();
		game.draw(*background);

		if ((Keyboard::isKeyPressed(Keyboard::Q) || Keyboard::isKeyPressed(Keyboard::D)) && Keyboard::isKeyPressed(Keyboard::Up))
		{
			compteurFramesAvecDrift++;
		}
		else
		{
			compteurFramesAvecDrift = 0;
		}

		if (compteurFramesAvecDrift == 180)
		{
			sound.pause();
			dejavu.play();
		}
		if (lastCompteurFramesAvecDrift > compteurFramesAvecDrift && lastCompteurFramesAvecDrift > 180)
		{
			dejavu.stop();
			sound.play();
		}

		lastCompteurFramesAvecDrift = compteurFramesAvecDrift;

		if (!multiplayer)
			asteroidManager(asteroids, frames, secsInterval, initGame, reduce);

		asteroidsNextFrame(asteroids);
		drawAsteroids(&game, asteroids);
		missilesNextFrame(missiles);
		drawMissiles(&game, missiles);

		shoot(spaceship1, missiles, &timeElapsedSinceLastShoot, false, multiplayer);

		updateSpaceship(game, spaceship1, false, multiplayer);

		if (multiplayer) {
			handleVirtualPlayer(spaceship2);
			game.draw(spaceship2.sprite);
		}

		lifeBar(&game, &font, spaceship1.life);
		drawScore(&game, font, score);

		if (!multiplayer) {
			if (((int)frames) % 60 == 0)//add one second to counter every 60 frames
				++bossWillCome;

			if (bossWillCome > BOSS_SPAWN_TIME)//if true the boss spawn
				boss.isAlive = 1;


			if (heart.exists == 1)
			{
				updateHeart(game, spaceship1, heart);
				collidesWithHeart(spaceship1, heart);
				game.draw(heart.sprite);
			}
			if (targetMissile.exists == 1)
			{
				updateTargetMissile(game, spaceship1, targetMissile);
				collidesWithTargetMissile(spaceship1, targetMissile);
				for (int i = 0; i < MISSILE_TABLE_LENGTH; i++)// damage boss from player missiles to target missiles
				{
					if (missiles[i].exists)
					{
						collidesWithTargetMissile(missiles[i], targetMissile);
					}
				}
			}

			if (boss.isAlive)
			{
				missilesNextFrame(bossMissiles);
				drawMissiles(&game, bossMissiles);

				bossUpdate(game, boss, spaceship1);
				bossShoot(boss, bossMissiles, &bossTimeElapsedSinceLastShoot, false);

				bossLifeBar(&game, boss);

				for (int i = 0; i < MISSILE_TABLE_LENGTH; i++)//damage players from boss
				{
					if (bossMissiles[i].exists)
					{
						if (spaceship1.isAlive && collidesWithSpaceshipMissile(spaceship1, bossMissiles[i]))
						{
							bossMissiles[i].exists = false;
							bossLoosesLife(&spaceship1, missiles[i].type.damage);
							spaceship1.speed.y -= SPACESHIP_BOUNCING_COEFFICIENT;
						}
					}
				}

				if (targetMissile.exists == 0 && bossWillCome % 10 == 0)//new creation of targetMissile
				{

					targetMissile.exists = 1;
					targetMissile.sprite.setPosition(boss.sprite.getPosition().x, boss.sprite.getPosition().y - SPACESHIP_SIZE);
				}
				collidesWithSpaceshipBoss(spaceship1, boss);

				for (int i = 0; i < MISSILE_TABLE_LENGTH; i++)// damage boss from player
				{
					if (missiles[i].exists)
					{
						collidesWithTargetMissile(missiles[i], targetMissile);//check with targeted missiles
						if (spaceship1.isAlive &&  collidesWithSpaceshipMissile(boss, missiles[i]))//check with normal missiles
						{
							missiles[i].exists = false;
							loosesLife(&boss);
						}
					}
				}

				if (boss.life <= 0)
				{
					bossWillCome = 0;
					destroySpaceship(boss);
					boss.isAlive = 0;
					initMissiles(bossMissiles);
					score += SCORE_BOSS;
					heart.exists = 1;
					heart.sprite.setPosition(boss.sprite.getPosition().x, boss.sprite.getPosition().y);
					bossInit(3, boss);

				}
				if (spaceship1.life <= 0)
				{
					destroySpaceship(spaceship1);
				}
			}
		}

		// Spaceship collisions
		for (int i = 0; i < ASTEROIDS_TABLE_LENGTH; i++) {
			if (!asteroids[i].exists)
				continue;
			if (spaceship1.isAlive && collidesWith(asteroids[i], spaceship1))
			{
				loosesLife(&spaceship1);
				asteroids[i].exists = 0;
				spaceship1.speed.x *= -1 * asteroids[i].speed*SPACESHIP_BOUNCING_COEFFICIENT;
				spaceship1.speed.y *= -1 * asteroids[i].speed*SPACESHIP_BOUNCING_COEFFICIENT;

				if (multiplayer)
				{
					sendData(asteroids[i], i);
				}

				if (spaceship1.life <= 0)
				{
					destroySpaceship(spaceship1);
					sendData(spaceship1);
				}
			}
		}

		// Missile collisions
		for (int i = 0; i < MISSILE_TABLE_LENGTH; i++) {
			if (missiles[i].exists) {
				for (int j = 0; j < ASTEROIDS_TABLE_LENGTH; j++) {
					if (asteroids[j].exists && collidesWith(asteroids[j], missiles[i])) {

						switch (asteroids[j].type) {
						case 1:
							score += 1;
							break;
						case 2:
							score += 2;
							break;
						case 3:
							score += 50;
							break;
						}

						// Destroy the asteroid if touched by the missile
						asteroids[j].exists = false;
						// Then destroy the missile
						missiles[i].exists = false;

						if (multiplayer)
						{
							sendData(asteroids[j], j);
						}
					}
				}
			}
		}

		game.display();

		game.pollEvent(event);

		/*if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			spaceship1.isAlive = false;

			if (multiplayer)
				spaceship2.isAlive = false;
		}*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			spaceship1.isAlive = false;
			spaceship2.isAlive = false;
		}
		
	}

	
	gameOver(&game, background, font, score);
	score += readSaveFile("money");
	writeToSaveFile("money", score);
}

void gameOver(RenderWindow *gameOverWindow, Sprite *background, Font font, int money)
{
	float mouseX, mouseY;
	float text_gameOverWidth, text_moneyWidth, backWidth;
	char moneyChain[24];

	gameOverWindow->clear();
	gameOverWindow->draw(*background);

	RectangleShape box_back_menu(Vector2f(SETTINGS_BOX_WIDTH, SETTINGS_BOX_HEIGHT));
	box_back_menu.setFillColor(Color::Blue);
	box_back_menu.setOutlineThickness(OUTLINE_SETTINGS_BOX);
	box_back_menu.setPosition(850, 650);

	Text text_gameOver;
	text_gameOver.setFont(font);
	text_gameOver.setString("Game Over !");
	text_gameOver.setCharacterSize(150);
	text_gameOver.setFillColor(Color::Red);
	text_gameOver.setOutlineThickness(5);
	text_gameOverWidth = text_gameOver.getLocalBounds().width;
	text_gameOver.setPosition((WINDOW_WIDTH - text_gameOverWidth) / 2, 250);

	Text text_money;
	text_money.setFont(font);
	sprintf(moneyChain, "Tu as gagné %i $", money);
	text_money.setString(moneyChain);
	text_money.setCharacterSize(50);
	text_money.setFillColor(Color::Yellow);
	text_moneyWidth = text_money.getLocalBounds().width;
	text_money.setPosition((WINDOW_WIDTH - text_moneyWidth) / 2, 450);
	Text back;
	back.setFont(font);
	back.setString("Menu");
	back.setCharacterSize(70);
	backWidth = back.getLocalBounds().width;
	back.setPosition(850 + (SETTINGS_BOX_WIDTH - backWidth) / 2, 650);

	gameOverWindow->draw(box_back_menu);
	gameOverWindow->draw(back);
	gameOverWindow->draw(text_money);
	gameOverWindow->draw(text_gameOver);
	gameOverWindow->display();

	while (gameOverWindow->isOpen())
	{
		mouseX = Mouse::getPosition(*gameOverWindow).x;
		mouseY = Mouse::getPosition(*gameOverWindow).y;
		Event event;
		while (gameOverWindow->pollEvent(event))
		{
			if (event.type == Event::Closed)
				return;
			if (box_back_menu.getGlobalBounds().contains(Vector2f(mouseX, mouseY)))
				if (Mouse::isButtonPressed(Mouse::Left)) {
					return;
				}
		}
	}

}
