#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>


#define _USE_MATH_DEFINES

#include <math.h>
#include "Structures.h"
#include "Keys.h"

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

ConvexShape missileShapeGenerator2000(char type)
{
	ConvexShape missile;

	if (type == 0)
	{
		missile.setPointCount(4);
		missile.setPoint(0, sf::Vector2f(0, 0));
		missile.setPoint(1, sf::Vector2f(4, 0)); 
		missile.setPoint(2, sf::Vector2f(4, 10));
		missile.setPoint(3, sf::Vector2f(0, 10));
		missile.setFillColor(sf::Color::White);
		missile.setOutlineColor(sf::Color::White);
		missile.setOutlineThickness(0);
	}

	return missile;
}

bool shoot(Spaceship spaceshipWow, Missile *missiles, int *timeElapsedSinceLastShoot)
{

	bool hasShooted = 0;
	static bool wasShootKeyPressedLastLoop;

	if (*timeElapsedSinceLastShoot > spaceshipWow.shootDelay || (!wasShootKeyPressedLastLoop && *timeElapsedSinceLastShoot > 20 ) )
	{
		if (Keyboard::isKeyPressed(shootKey))
		{
			int i = 0;

			while (missiles[i].exists)
			{
				i++;
			}

			missiles[i].exists = 1;
			missiles[i].shape = missileShapeGenerator2000(spaceshipWow.missile.type);
			missiles[i].angle = (spaceshipWow.sprite.getRotation() - 90) / 360 * 2 * M_PI;
			missiles[i].speed = 10;// vitesse du vaisseau A MODIFIER
			missiles[i].damage = 1; // A MODIFIER si plusieurs types de missiles
			missiles[i].shape.setPosition(Vector2f(spaceshipWow.sprite.getPosition().x, spaceshipWow.sprite.getPosition().y));
			missiles[i].originSpaceship = spaceshipWow.id;

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


	for (i = 0; i<MISSILE_TABLE_LENGTH; i++)
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