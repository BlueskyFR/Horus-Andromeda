#include <SFML/Graphics.hpp>
#include "Structures.h"
#include "Missile.h"

#include <iostream>//A ENLEVER


void bossMove(RenderWindow &game, Spaceship &boss, Spaceship &spaceship);
bool bossShoot(Spaceship spaceshipWow, Missile *missiles, int *timeElapsedSinceLastShoot, bool firstCall);

void bossInit(int id, Spaceship &boss)//set every feature of the structure boss, executed once at the beginning of one game
{
	boss.texture = Texture();
	boss.texture.loadFromFile(std::string("res/spaceshipBoss.png"));
	//TODO: HANDLE ERROR
	boss.id = id;
	boss.sprite = Sprite();
	boss.sprite.setTexture(boss.texture);
	boss.sprite.setOrigin(SPACESHIP_SIZE / 2, SPACESHIP_SIZE / 2);
	boss.sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - SPACESHIP_SIZE);
	boss.speed = Vector2f(0, 0);
	boss.missile.type = 15;
	//boss.weapon = 0;

	boss.isAlive = false;
	boss.shootDelay = BOSS_SHOOT_DELAY;
	boss.life = BOSS_LIFE;
}

void bossUpdate(RenderWindow &game, Spaceship &boss, Spaceship &spaceship)//call the bossMove function
{
	bossMove(game, boss, spaceship);
}

void bossMove(RenderWindow &game, Spaceship &boss, Spaceship &spaceship)//move and draw boss
{
	if (boss.sprite.getPosition().x < spaceship.sprite.getPosition().x - BOSS_STOP_MOVE_ZONE)
		boss.speed.x = BOSS_SPEED;
	else if (boss.sprite.getPosition().x > spaceship.sprite.getPosition().x + BOSS_STOP_MOVE_ZONE)
		boss.speed.x = -BOSS_SPEED;

	//If the spaceship is far
	if (boss.sprite.getPosition().x < spaceship.sprite.getPosition().x - BOSS_STOP_MOVE_ZONE * 2)
		boss.speed.x += BOSS_SPEED;
	else if (boss.sprite.getPosition().x > spaceship.sprite.getPosition().x + BOSS_STOP_MOVE_ZONE * 2)
		boss.speed.x += -BOSS_SPEED;

	if (boss.sprite.getPosition().x <= spaceship.sprite.getPosition().x + BOSS_STOP_MOVE_ZONE && boss.sprite.getPosition().x >= spaceship.sprite.getPosition().x - BOSS_STOP_MOVE_ZONE)
		boss.speed.x = 0;

	boss.sprite.setPosition(Vector2f(boss.sprite.getPosition().x + boss.speed.x, boss.sprite.getPosition().y));

	game.draw(boss.sprite);
}

bool bossShoot(Spaceship spaceshipWow, Missile *missiles, int *timeElapsedSinceLastShoot, bool firstCall)//Handle the normale missiles of the boss
{

	bool hasShooted = 0;
	static bool wasShootKeyPressedLastLoop;

	if (firstCall == 1)
	{
		return 0;
	}

	if (*timeElapsedSinceLastShoot > spaceshipWow.shootDelay || (!wasShootKeyPressedLastLoop && *timeElapsedSinceLastShoot > 20))
	{
		if (spaceshipWow.id == 3)
		{
			int i = 0;

			while (missiles[i].exists)
			{
				i++;
			}

			missiles[i].exists = 1;
			missiles[i].shape = missileShapeGenerator2000(spaceshipWow.missile.type, spaceshipWow.sprite.getRotation());
			missiles[i].angle = (spaceshipWow.sprite.getRotation() - 90) / 360 * 2 * PI;
			missiles[i].speed = BOSS_SPEED_MISSILE;
			missiles[i].damage = 1;
			missiles[i].shape.setPosition(Vector2f(spaceshipWow.sprite.getPosition().x, spaceshipWow.sprite.getPosition().y));
			missiles[i].originSpaceship = spaceshipWow.id;

			hasShooted = 1;
			*timeElapsedSinceLastShoot = 0;
		}
	}

	if (spaceshipWow.id == 3)
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

bool collidesWithSpaceshipMissile(Spaceship spaceship, Missile missile) // Damages boss-player and player-boss
{
	return missile.shape.getGlobalBounds().intersects(spaceship.sprite.getGlobalBounds());
}

void collidesWithSpaceshipBoss(Spaceship &spaceship, Spaceship &boss) // Damages if player bump into the boss
{
	if (spaceship.sprite.getGlobalBounds().intersects(boss.sprite.getGlobalBounds()))
	{
		spaceship.speed.x *= -1 * SPACESHIP_BOUNCING_COEFFICIENT * 2;
		spaceship.speed.y *= -1 * SPACESHIP_BOUNCING_COEFFICIENT * 2;
		spaceship.life -= 20;
		boss.life -= 20;
	}
}

void bossLoosesLife(Spaceship *spaceship, int damage)//damages from boss to spaceship
{
	spaceship->life = spaceship->life - 20;
}

void bossLifeBar(RenderWindow *window, Spaceship boss)//set and draw the health bar above the boss
{
	RectangleShape bar(Vector2f(boss.life, 8));
	bar.setOrigin(boss.life / 2, 8);
	bar.setPosition(boss.sprite.getPosition().x, boss.sprite.getPosition().y - SPACESHIP_SIZE / 2 - 15);
	bar.setFillColor(Color::Blue);

	window->draw(bar);
}
