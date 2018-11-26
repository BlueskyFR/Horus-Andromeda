#include <SFML/Graphics.hpp>

#include "Structures.h"
#include "Server.h"
#include "Spaceship.h"
#include "SaveFile.h"

void initSpaceship(int id, Spaceship &spaceship) {
	spaceship.texture = Texture();
	spaceship.texture.loadFromFile(std::string("res/spaceship" + std::to_string(id) + ".png"));
	//TODO: HANDLE ERROR

	spaceship.id = id;
	spaceship.sprite = Sprite();
	spaceship.sprite.setTexture(spaceship.texture);
	spaceship.sprite.setOrigin(SPACESHIP_SIZE / 2, SPACESHIP_SIZE / 2);
	spaceship.sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	spaceship.speed = Vector2f(0, 0);
	spaceship.missile.type = readSaveFile("missileType");
	//spaceship.weapon = 0;

	spaceship.isAlive = true;
	spaceship.shootDelay = 50;
	spaceship.life = 100;
}

void destroySpaceship(Spaceship &spaceship) {
	spaceship.isAlive = false;
	if (spaceship.id != 3)
		spaceship.texture.loadFromFile(std::string("res/spaceship" + std::to_string(spaceship.id) + "_dead.png"));
	spaceship.sprite.setTexture(spaceship.texture);
}

void updateSpaceship(RenderWindow &game, Spaceship &spaceship, bool firstCall, bool multiplayer)
{
	float spaceship_rotation_strength = readSaveFile("spaceship_rotation");

	static Keyboard::Key keyMoveUp = handleKeyBoard(Keyboard::Unknown, 0, 'r');
	static Keyboard::Key keyMoveDown = handleKeyBoard(Keyboard::Unknown, 1, 'r');
	static Keyboard::Key keyMoveLeft = handleKeyBoard(Keyboard::Unknown, 2, 'r');
	static Keyboard::Key keyMoveRight = handleKeyBoard(Keyboard::Unknown, 3, 'r');
	static Keyboard::Key keyRotationLeft = handleKeyBoard(Keyboard::Unknown, 4, 'r');
	static Keyboard::Key keyRotationRight = handleKeyBoard(Keyboard::Unknown, 5, 'r');
	static Keyboard::Key keyShoot = handleKeyBoard(Keyboard::Unknown, 6, 'r');

	if (firstCall == true)
	{
		keyMoveUp = handleKeyBoard(Keyboard::Unknown, 0, 'r');
		keyMoveDown = handleKeyBoard(Keyboard::Unknown, 1, 'r');
		keyMoveLeft = handleKeyBoard(Keyboard::Unknown, 2, 'r');
		keyMoveRight = handleKeyBoard(Keyboard::Unknown, 3, 'r');
		keyRotationLeft = handleKeyBoard(Keyboard::Unknown, 4, 'r');
		keyRotationRight = handleKeyBoard(Keyboard::Unknown, 5, 'r');
		keyShoot = handleKeyBoard(Keyboard::Unknown, 6, 'r');
		return;
	}

	if (!spaceship.isAlive)
		return;

	if (Keyboard::isKeyPressed(keyMoveUp))//move sprite up
	{
		speedSpaceship(spaceship, keyMoveUp, false);
	}
	if (Keyboard::isKeyPressed(keyMoveDown))//move sprite down
	{
		speedSpaceship(spaceship, keyMoveDown, false);//calculate speed direction//setUpPosition of the ship with the speed modification
	}
	if (Keyboard::isKeyPressed(keyMoveLeft))//move sprite left
	{
		speedSpaceship(spaceship, keyMoveLeft, false);
	}
	if (Keyboard::isKeyPressed(keyMoveRight))//move sprite right
	{
		speedSpaceship(spaceship, keyMoveRight, false);
	}
	if (Keyboard::isKeyPressed(keyRotationLeft))//rotate sprite left
	{
		rotateSpaceshipLeft(spaceship, spaceship_rotation_strength);
	}
	if (Keyboard::isKeyPressed(keyRotationRight))//rotate sprite right
	{
		rotateSpaceshipRight(spaceship, spaceship_rotation_strength);
	}
	if (Keyboard::isKeyPressed(keyShoot))//TO COMPLETE WITH KEYSHOOT
	{
		//rotateSpaceshipRight(spaceship);
	}

	speedSpaceship(spaceship, Keyboard::Unknown, false);//to deccelerate the spaceship
	moveSpaceship(spaceship);

	if (multiplayer)
		sendData(spaceship);

	game.draw(spaceship.sprite);
}

void speedSpaceship(Spaceship &spaceship, Keyboard::Key KeyPressed, bool firstCall)
{

	static Keyboard::Key keyMoveUp = handleKeyBoard(Keyboard::Unknown, 0, 'r');
	static Keyboard::Key keyMoveDown = handleKeyBoard(Keyboard::Unknown, 1, 'r');
	static Keyboard::Key keyMoveLeft = handleKeyBoard(Keyboard::Unknown, 2, 'r');
	static Keyboard::Key keyMoveRight = handleKeyBoard(Keyboard::Unknown, 3, 'r');

	if (firstCall == true)
	{
		keyMoveUp = handleKeyBoard(Keyboard::Unknown, 0, 'r');
		keyMoveDown = handleKeyBoard(Keyboard::Unknown, 1, 'r');
		keyMoveLeft = handleKeyBoard(Keyboard::Unknown, 2, 'r');
		keyMoveRight = handleKeyBoard(Keyboard::Unknown, 3, 'r');
		return;
	}

	if (KeyPressed != Keyboard::Unknown)
	{
		if (KeyPressed == keyMoveUp)
		{

			spaceship.speed.x += cos(converterDegreeRadian(spaceship.sprite.getRotation() + 90 * 3))*SPACESHIP_ACCELERATION;
			spaceship.speed.y += sin(converterDegreeRadian(spaceship.sprite.getRotation() + 90 * 3))*SPACESHIP_ACCELERATION;
		}
		else if (KeyPressed == keyMoveLeft)
		{
			spaceship.speed.x += cos(converterDegreeRadian(spaceship.sprite.getRotation() + 90 * 2))*SPACESHIP_ACCELERATION;
			spaceship.speed.y += sin(converterDegreeRadian(spaceship.sprite.getRotation() + 90 * 2))*SPACESHIP_ACCELERATION;
		}
		else if (KeyPressed == keyMoveDown)
		{
			spaceship.speed.x += cos(converterDegreeRadian(spaceship.sprite.getRotation() + 90))*SPACESHIP_ACCELERATION;
			spaceship.speed.y += sin(converterDegreeRadian(spaceship.sprite.getRotation() + 90))*SPACESHIP_ACCELERATION;
		}
		else if (KeyPressed == keyMoveRight)
		{
			spaceship.speed.x += cos(converterDegreeRadian(spaceship.sprite.getRotation()))*SPACESHIP_ACCELERATION;
			spaceship.speed.y += sin(converterDegreeRadian(spaceship.sprite.getRotation()))*SPACESHIP_ACCELERATION;
		}

	}
	else//if KeyPressed==NOKEYPRESSED
	{

		spaceship.speed.x *= SPACESHIP_DECELERATION;
		spaceship.speed.y *= SPACESHIP_DECELERATION;

	}

	if (spaceship.speed.x > SPACESHIP_MAX_SPEED)
		spaceship.speed.x = SPACESHIP_MAX_SPEED;
	else if (spaceship.speed.x < -SPACESHIP_MAX_SPEED)
		spaceship.speed.x = -SPACESHIP_MAX_SPEED;

	if (spaceship.speed.y > SPACESHIP_MAX_SPEED)
		spaceship.speed.y = SPACESHIP_MAX_SPEED;
	else if (spaceship.speed.y < -SPACESHIP_MAX_SPEED)
		spaceship.speed.y = -SPACESHIP_MAX_SPEED;
}

void spaceshipCollisionWindow(Spaceship &spaceship)
{
	Vector2f endMovement = Vector2f(spaceship.sprite.getPosition().x + spaceship.speed.x, spaceship.sprite.getPosition().y + spaceship.speed.y);//Future position of the spaceship
	if ((endMovement.y <= SPACESHIP_RADIUS_DIAG) || (endMovement.y >= WINDOW_HEIGHT - SPACESHIP_RADIUS_DIAG))//If a spaceship bump into the up or down part of the window
		spaceship.speed.y *= -1 * SPACESHIP_BOUNCING_COEFFICIENT;//make it bounce in the opposite direction !
	else if ((endMovement.x <= SPACESHIP_RADIUS_DIAG) || (endMovement.x >= WINDOW_WIDTH - SPACESHIP_RADIUS_DIAG))//If a spaceship bump into the left or right part of the window
		spaceship.speed.x *= -1 * SPACESHIP_BOUNCING_COEFFICIENT;//make it bounce in the opposite direction !
}

void rotateSpaceshipLeft(Spaceship &spaceship, float spaceship_rotation_strength)
{
	spaceship.sprite.setRotation(spaceship.sprite.getRotation() - spaceship_rotation_strength);
}

void rotateSpaceshipRight(Spaceship &spaceship, float spaceship_rotation_strength)
{
	spaceship.sprite.setRotation(spaceship.sprite.getRotation() + spaceship_rotation_strength);
}

void moveSpaceship(Spaceship &spaceship)
{
	spaceshipCollisionWindow(spaceship);
	spaceship.sprite.setPosition(Vector2f(spaceship.sprite.getPosition().x + spaceship.speed.x, spaceship.sprite.getPosition().y + spaceship.speed.y));
}

void handleVirtualPlayer(Spaceship &spaceship) {
	spaceship.speed.x *= SPACESHIP_DECELERATION;
	spaceship.speed.y *= SPACESHIP_DECELERATION;

	if (spaceship.speed.x > SPACESHIP_MAX_SPEED)
		spaceship.speed.x = SPACESHIP_MAX_SPEED;
	else if (spaceship.speed.x < -SPACESHIP_MAX_SPEED)
		spaceship.speed.x = -SPACESHIP_MAX_SPEED;

	if (spaceship.speed.y > SPACESHIP_MAX_SPEED)
		spaceship.speed.y = SPACESHIP_MAX_SPEED;
	else if (spaceship.speed.y < -SPACESHIP_MAX_SPEED)
		spaceship.speed.y = -SPACESHIP_MAX_SPEED;
	
	moveSpaceship(spaceship);
}

float converterDegreeRadian(float number)
{
	return number / 360 * 2 * PI;
}


void loosesLife(Spaceship *spaceship)
{
	spaceship->life -= (100 / readSaveFile("max_shots_before_dead"));
}

void lifeBar(RenderWindow *window, Font *font, int pvSpaceship)
{
	char pvNumber[10];
	float nbPvWidth;
	RectangleShape bar( Vector2f(2 * pvSpaceship, 25) );
	bar.setPosition(20, 20);
	bar.setFillColor(Color::Red);

	Text nbPv;
		nbPv.setFont(*font);
	sprintf(pvNumber, "%i", pvSpaceship);
	nbPv.setString(pvNumber);
	nbPv.setCharacterSize(20);
	nbPvWidth = nbPv.getLocalBounds().width;
	nbPv.setPosition(20 + (200 - nbPvWidth) / 2, 20);
	window->draw(bar);
	window->draw(nbPv);
}