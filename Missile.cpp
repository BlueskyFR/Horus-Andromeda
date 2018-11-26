#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#define _USE_MATH_DEFINES

#include <math.h>
#include "Structures.h"
#include "Server.h"
#include "Settings.h"

using namespace sf;


void initMissiles(Missile *missiles)
{
	for (int i = 0; i < MISSILE_TABLE_LENGTH; i++)
	{
		missiles[i].exists = false;
	}
}

void drawMissiles(RenderWindow *fenetre, Missile *missiles)
{
	int i;

	for (i = 0; i < MISSILE_TABLE_LENGTH; i++)
	{
		if (missiles[i].exists)
		{
			fenetre->draw(missiles[i].shape);
		}
	}
}

ConvexShape missileShapeGenerator2000(char type, float angle)
{
	ConvexShape missile;

	if (type == 0)
	{
		missile.setPointCount(4);
		missile.setPoint(0, sf::Vector2f(0, 0));
		missile.setPoint(1, sf::Vector2f(3, 0));
		missile.setPoint(2, sf::Vector2f(3, 10));
		missile.setPoint(3, sf::Vector2f(0, 10));
		missile.setFillColor(sf::Color::White);
		missile.setRotation(angle);
	}
	else if (type == 1)
	{
		missile.setPointCount(6);
		missile.setPoint(0, sf::Vector2f(0, 7));
		missile.setPoint(1, sf::Vector2f(7, 0));
		missile.setPoint(2, sf::Vector2f(14, 8));
		missile.setPoint(3, sf::Vector2f(14, 14));
		missile.setPoint(4, sf::Vector2f(7, 21));
		missile.setPoint(5, sf::Vector2f(0, 14));
		missile.setFillColor(sf::Color::Red);
		missile.setRotation(angle);
	}
	else if (type == 15)
	{
		missile.setPointCount(4);
		missile.setPoint(0, sf::Vector2f(0, 0));
		missile.setPoint(1, sf::Vector2f(3, 0));
		missile.setPoint(2, sf::Vector2f(3, 10));
		missile.setPoint(3, sf::Vector2f(0, 10));
		missile.setFillColor(sf::Color::Green);
		missile.setRotation(angle);
	}


	return missile;
}

bool shoot(Spaceship spaceshipWow, Missile *missiles, int *timeElapsedSinceLastShoot, bool firstCall, bool multiplayer)
{

	bool hasShooted = 0;
	static bool wasShootKeyPressedLastLoop;
	static Keyboard::Key shootKey = handleKeyBoard(Keyboard::Unknown, 6, 'r');

	if (firstCall == 1)
	{
		shootKey = handleKeyBoard(Keyboard::Unknown, 6, 'r');
		return 0;
	}

	if (*timeElapsedSinceLastShoot > spaceshipWow.shootDelay || (!wasShootKeyPressedLastLoop && *timeElapsedSinceLastShoot > 20))
	{
		if (Keyboard::isKeyPressed(shootKey))
		{
			int i = 0;

			while (missiles[i].exists)
			{
				i++;
			}

			missiles[i].exists = 1;
			missiles[i].shape = missileShapeGenerator2000(spaceshipWow.missile.type, spaceshipWow.sprite.getRotation());
			missiles[i].angle = (spaceshipWow.sprite.getRotation() - 90) / 360 * 2 * M_PI;
			missiles[i].speed = 10;// vitesse du vaisseau A MODIFIER
			missiles[i].damage = 1; // A MODIFIER si plusieurs types de missiles
			missiles[i].shape.setPosition(Vector2f(spaceshipWow.sprite.getPosition().x, spaceshipWow.sprite.getPosition().y));
			missiles[i].originSpaceship = spaceshipWow.id;

			if (multiplayer)
				sendData(missiles[i]);

			hasShooted = 1;
			*timeElapsedSinceLastShoot = 0;

		}
	}

	if (Keyboard::isKeyPressed(shootKey))
	{
		wasShootKeyPressedLastLoop = 1;
	}
	else
	{
		wasShootKeyPressedLastLoop = 0;
	}

	*timeElapsedSinceLastShoot = *timeElapsedSinceLastShoot + 1;

	return hasShooted;
}

void missilesNextFrame(Missile *missiles)
{
	int i;
	float x;
	float y;


	for (i = 0; i < MISSILE_TABLE_LENGTH; i++)
	{
		if (missiles[i].exists)
		{

			x = missiles[i].shape.getPosition().x;
			y = missiles[i].shape.getPosition().y;

			x += missiles[i].speed * cos(missiles[i].angle);
			y += missiles[i].speed * sin(missiles[i].angle);

			if (y > WINDOW_HEIGHT || y < 0)
			{
				missiles[i].exists = 0;
			}
			else if (x > WINDOW_WIDTH || x < 0)
			{
				missiles[i].exists = 0;
			}

			missiles[i].shape.setPosition(Vector2f(x, y));
		}
	}

}