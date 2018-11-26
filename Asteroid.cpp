#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "Structures.h"
#include "Asteroid.h"

using namespace sf;

void initRandom() {
	srand(time(NULL));
}

void asteroidManager(Asteroid *asteroids, int &frames, float &secsInterval, bool &initGame, bool &reduce) {
	frames++;

	if (initGame && frames > 300) { // 300 frames = 5 seconds
		for (int i = 0; i < INITIAL_ASTEROID_COUNT; i++) {
			asteroids[i] = generateAsteroid(PROBABILITIES);
		}

		frames = 0;
		initGame = false;
	}

	if (frames > secsInterval * 60) {
		frames = 0;

		if (reduce) {
			secsInterval *= SPAWN_MULTIPLICATOR_FACTOR;
			if (secsInterval < MIN_SPAWN_INTEVAL) {
				secsInterval = MIN_SPAWN_INTEVAL;
				reduce = false;
			}
		}

		for (int i = 0; i < ASTEROIDS_TABLE_LENGTH; i++) {
			if (!asteroids[i].exists) {
				asteroids[i] = generateAsteroid(PROBABILITIES);
				break;
			}
		}
	}
}

bool collidesWith(Asteroid asteroid, Missile missile) {
	return asteroid.shape.getGlobalBounds().intersects(missile.shape.getGlobalBounds());
}

bool collidesWith(Asteroid asteroid, Spaceship player) {
    FloatRect hitboxAsteroid = FloatRect(asteroid.shape.getGlobalBounds());
    FloatRect hitboxPlayer = FloatRect(player.sprite.getGlobalBounds());
    hitboxAsteroid.height /= 1.7;
    hitboxAsteroid.width /= 1.7;
    hitboxPlayer.height /= 1.7;
    hitboxPlayer.width /= 1.7;

	return hitboxAsteroid.intersects(hitboxPlayer);
}


Asteroid generateAsteroid(const int typeProbabilities[NB_TYPES]) {
	Asteroid asteroid;
	ConvexShape shape = ConvexShape();
	shape.setPointCount(6);

	// Position
	float x, y;

	switch ((rand() % 4) + 1)
	{
	case 1: // TOP
		x = rand() % WINDOW_WIDTH;
		y = -SPAWN_MARGIN;
		break;
	case 2: // RIGHT
		x = WINDOW_WIDTH + SPAWN_MARGIN;
		y = rand() % WINDOW_HEIGHT;
		break;
	case 3: // BOTTOM
		x = rand() % WINDOW_WIDTH;
		y = WINDOW_HEIGHT + SPAWN_MARGIN;
		break;
	case 4: // LEFT
		x = -SPAWN_MARGIN;
		y = rand() % WINDOW_HEIGHT;
		break;
	}

	shape.setPosition(x, y);

	int totalProbability = 0;
	for (int i = 0; i < NB_TYPES; i++)
		totalProbability += typeProbabilities[i];

	// Type generation
	int randomTypeProbability = (rand() % totalProbability) + 1;

	int totalStack = 0;
	for (int i = 0; i < NB_TYPES; i++) {
		if (randomTypeProbability <= totalStack + typeProbabilities[i]) {
			asteroid.type = i + 1;
			break;
		}
		totalStack += typeProbabilities[i];
	}

	// Color from type
	switch (asteroid.type)
	{
	case 1: // Normal, bounces
		shape.setFillColor(Color::Color(109, 0, 0));
		break;
	case 2: // Passing by
		shape.setFillColor(Color::Color(32, 129, 0));
		break;
	case 3: // Passing by, little and rare
		shape.setFillColor(Color::Yellow);
		break;
	}

	// Outline
	shape.setOutlineThickness(1.0);
	shape.setOutlineColor(Color::White);

	// Speed (Range : 1-3)
	asteroid.speed = (rand() % MAX_SPEED) + 1;
	if (asteroid.type == 3)
		asteroid.speed += MAX_SPEED;

	// Angle
	int angleAuthorization;
	if (x > WINDOW_WIDTH && y < 0)
		angleAuthorization = (rand() % 2) + 1;
	else if (x > WINDOW_WIDTH && y > WINDOW_HEIGHT)
		angleAuthorization = (rand() % 2) + 2;
	else if (x < 0 && y > WINDOW_HEIGHT)
		angleAuthorization = (rand() % 2) + 3;
	else if (x < 0 && y < 0) {
		angleAuthorization = (rand() % 2) + 1;
		if (angleAuthorization == 2)
			angleAuthorization = 4;
	}
	else if (y < 0)
		angleAuthorization = 1;
	else if (x > WINDOW_WIDTH)
		angleAuthorization = 2;
	else if (y > WINDOW_HEIGHT)
		angleAuthorization = 3;
	else if (x < 0)
		angleAuthorization = 4;
	else
		angleAuthorization = 5;

	float baseAngle, maxAngle;

	switch (angleAuthorization)
	{
	case 1: // Top
		baseAngle = M_PI + atan(((WINDOW_HEIGHT / 2.0) - y) / (float)x);
		maxAngle = atan(x / (float)((WINDOW_HEIGHT / 2.0) - y)) + atan((WINDOW_WIDTH - x) / (float)((WINDOW_HEIGHT / 2.0) - y));
		break;
	case 2: // Right
		baseAngle = (M_PI / 2) + atan((x - (WINDOW_WIDTH / 2.0)) / (float)y);
		maxAngle = atan((WINDOW_HEIGHT - y) / (float)(x - (WINDOW_HEIGHT / 2.0))) + atan(y / (float)(x - (WINDOW_WIDTH / 2.0)));
		break;
	case 3: // Bottom
		baseAngle = atan((y - (WINDOW_HEIGHT / 2.0)) / (float)(WINDOW_WIDTH - x));
		maxAngle = atan(x / (float)(y - (WINDOW_HEIGHT / 2.0))) + atan((WINDOW_WIDTH - x) / (float)(y - (WINDOW_HEIGHT / 2.0)));
		break;
	case 4: // Left
		baseAngle = ((3 * M_PI) / 2) + atan(((WINDOW_WIDTH / 2.0) - x) / (float)(WINDOW_HEIGHT - y));
		maxAngle = atan(y / (float)((WINDOW_WIDTH / 2.0) - x)) + atan((WINDOW_HEIGHT - y) / (float)((WINDOW_WIDTH / 2.0) - x));
		break;
	default: // ERROR
		throw _EXCEPTION_;
		break;
	}

	asteroid.angle = baseAngle + ((rand() % ((int)(maxAngle * FLOAT_PRECISION))) / (float)FLOAT_PRECISION);

	// Angular velocity
	asteroid.angularVelocity = ((rand() % (int)(MAX_ANGULAR_VELOCITY * 2.0 * FLOAT_PRECISION)) / (float)FLOAT_PRECISION)
		- MAX_ANGULAR_VELOCITY;

	// Exists
	asteroid.exists = true;
	// Has already entered window?
	asteroid.hasEnteredWindow = false;

	// Generate points
	shape.setPointCount(NB_POINTS);


	for (int i = 0; i < NB_POINTS; i++) {
		float currentAngle = ((2 * M_PI) / NB_POINTS) * (i + 1);
		float generatedRadius;
		if (asteroid.type == 3)
			generatedRadius = MIN_ASTEROID_SPECIAL_RADIUS + (rand() % ((ASTEROID_SPECIAL_RANDOMNESS_RANGE * 2) + 1)) - ASTEROID_SPECIAL_RANDOMNESS_RANGE;
		else
			generatedRadius = MIN_ASTEROID_RADIUS + (rand() % ((ASTEROID_RANDOMNESS_RANGE * 2) + 1)) - ASTEROID_RANDOMNESS_RANGE;

		shape.setPoint(i, Vector2f(cos(currentAngle) * generatedRadius, sin(currentAngle) * generatedRadius));
	}

	// Finalizing and returning object
	asteroid.shape = shape;
	return asteroid;
}

void asteroidsNextFrame(Asteroid *asteroids)
{
	int i;
	float x;
	float y;

	for (i = 0; i<ASTEROIDS_TABLE_LENGTH; i++)
	{
		if (asteroids[i].exists)
		{

			x = asteroids[i].shape.getPosition().x;
			y = asteroids[i].shape.getPosition().y;

			x += asteroids[i].speed * cos(asteroids[i].angle);
			y -= asteroids[i].speed * sin(asteroids[i].angle);

			asteroids[i].shape.setRotation(asteroids[i].angularVelocity + asteroids[i].shape.getRotation());

			if (asteroids[i].type == 1)
			{
				if ((y + MIN_ASTEROID_RADIUS > WINDOW_HEIGHT || y - MIN_ASTEROID_RADIUS < 0) && asteroids[i].hasEnteredWindow)
				{
					asteroids[i].angle = -asteroids[i].angle;
				}
				else if ((x + MIN_ASTEROID_RADIUS > WINDOW_WIDTH || x - MIN_ASTEROID_RADIUS < 0) && asteroids[i].hasEnteredWindow)
				{
					asteroids[i].angle = M_PI - asteroids[i].angle;
				}
			}

			if (asteroids[i].type == 2 || asteroids[i].type == 3)
			{
				if ((y - MIN_ASTEROID_RADIUS > WINDOW_HEIGHT || y < 0) && asteroids[i].hasEnteredWindow)
				{
					asteroids[i].exists = false;
				}
				else if ((x - MIN_ASTEROID_RADIUS > WINDOW_WIDTH || x < 0) && asteroids[i].hasEnteredWindow)
				{
					asteroids[i].exists = false;
				}
			}

			if (y + MIN_ASTEROID_RADIUS < WINDOW_HEIGHT && y - MIN_ASTEROID_RADIUS > 0 && x + MIN_ASTEROID_RADIUS < WINDOW_WIDTH && x - MIN_ASTEROID_RADIUS > 0)
			{
				asteroids[i].hasEnteredWindow = 1;
			}

			//printf("\n [%i] = X : %.2f - Y : %.2f", i, x, y);
			asteroids[i].shape.setPosition(Vector2f(x, y));
		}
	}

}

void drawAsteroids(RenderWindow *fenetre, Asteroid *asteroids)
{
	int i;

	//fenetre->clear();

	for (i = 0; i < ASTEROIDS_TABLE_LENGTH; i++)
	{
		if (asteroids[i].exists)
		{
			//printf("\nANGLE : %.2f rad / %.2f deg", asteroids[i].angle, (asteroids[i].angle / (2 * M_PI)) * 360);
			fenetre->draw(asteroids[i].shape);
		}
	}

	//fenetre->display();
}

void noAsteroidExist(Asteroid *asteroids)
{
	for (int i = 0; i < ASTEROIDS_TABLE_LENGTH; i++)
	{
		asteroids[i].exists = false;
	}
}
