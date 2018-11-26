#include <SFML/Graphics.hpp>

#include "Structures.h"


void initHeart(Heart &heart)//set the features of the heart (executed once)
{
	heart.texture = Texture();
	heart.texture.loadFromFile("res/heart.png");
	//TODO: HANDLE ERROR

	heart.sprite = Sprite();
	heart.sprite.setTexture(heart.texture);
	heart.exists=0;
	heart.sprite.setOrigin(HEART_SIZE / 2, HEART_SIZE / 2);
}

void collidesWithHeart(Spaceship &spaceship, Heart &heart) // return 1 if spaceship touch the heart, add some health to the player
{
	if(spaceship.sprite.getGlobalBounds().intersects(heart.sprite.getGlobalBounds()))
	{
	    heart.exists=0;
        spaceship.life+=HEART_HEALTH_BONUS;
	}

}

void updateHeart(RenderWindow &game, Spaceship &spaceship, Heart &heart)//calculate and set the new position of the heart (executed each frame)
{
    if (heart.sprite.getPosition().x < spaceship.sprite.getPosition().x - BOSS_STOP_MOVE_ZONE)
		heart.speed.x = BOSS_SPEED;
	else if(heart.sprite.getPosition().x > spaceship.sprite.getPosition().x + BOSS_STOP_MOVE_ZONE)
		heart.speed.x = -BOSS_SPEED;

	if (heart.sprite.getPosition().x < spaceship.sprite.getPosition().x - BOSS_STOP_MOVE_ZONE*2)
		heart.speed.x += BOSS_SPEED;
	else if (heart.sprite.getPosition().x > spaceship.sprite.getPosition().x + BOSS_STOP_MOVE_ZONE*2)
		heart.speed.x += -BOSS_SPEED;

	if (heart.sprite.getPosition().x <= spaceship.sprite.getPosition().x + BOSS_STOP_MOVE_ZONE && heart.sprite.getPosition().x >= spaceship.sprite.getPosition().x - BOSS_STOP_MOVE_ZONE)
		heart.speed.x = 0;


	if (heart.sprite.getPosition().y < spaceship.sprite.getPosition().y - BOSS_STOP_MOVE_ZONE)
		heart.speed.y = BOSS_SPEED;
	else if(heart.sprite.getPosition().y > spaceship.sprite.getPosition().y + BOSS_STOP_MOVE_ZONE)
		heart.speed.y = -BOSS_SPEED;

	if (heart.sprite.getPosition().y < spaceship.sprite.getPosition().y - BOSS_STOP_MOVE_ZONE*2)
		heart.speed.y += BOSS_SPEED;
	else if (heart.sprite.getPosition().y > spaceship.sprite.getPosition().y + BOSS_STOP_MOVE_ZONE*2)
		heart.speed.y += -BOSS_SPEED;

	if (heart.sprite.getPosition().y <= spaceship.sprite.getPosition().y + BOSS_STOP_MOVE_ZONE && heart.sprite.getPosition().y >= spaceship.sprite.getPosition().y - BOSS_STOP_MOVE_ZONE)
		heart.speed.y = 0;

	heart.sprite.setPosition(Vector2f(heart.sprite.getPosition().x + heart.speed.x, heart.sprite.getPosition().y + heart.speed.y));
}

