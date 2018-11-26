#include <SFML/Graphics.hpp>

#include "Structures.h"
#include "Spaceship.h"

void initTargetMissile(TargetMissile &targetMissile)//initialise the features of the target missile (called only once before each game)
{
	targetMissile.texture = Texture();
	targetMissile.texture.loadFromFile("res/targetMissile.png");
	//TODO: HANDLE ERROR

	targetMissile.sprite = Sprite();
	targetMissile.sprite.setTexture(targetMissile.texture);
	targetMissile.exists=0;
	targetMissile.sprite.setOrigin(HEART_SIZE / 2, HEART_SIZE / 2);
}

void collidesWithTargetMissile(Spaceship &spaceship, TargetMissile &targetMissile) // handle collisions between spaceship and target missile, if there is a collision modificate the speed and life of spaceship
{
	if(spaceship.sprite.getGlobalBounds().intersects(targetMissile.sprite.getGlobalBounds()))
	{
        spaceship.life-=TARGET_MISSILE_DAMAGE;
        spaceship.speed.x+=targetMissile.speed.x*SPACESHIP_BOUNCING_COEFFICIENT*3;
        spaceship.speed.y+=targetMissile.speed.y*SPACESHIP_BOUNCING_COEFFICIENT*3;
        targetMissile.exists=0;
	}

}

void collidesWithTargetMissile(Missile &missile, TargetMissile &targetMissile) // if a player destroy a missile, the target missile doesn't exist anymore
{
	if(missile.shape.getGlobalBounds().intersects(targetMissile.sprite.getGlobalBounds()))
	    targetMissile.exists=0;

}

void updateTargetMissile(RenderWindow &game, Spaceship &spaceship, TargetMissile &targetMissile)// calculate and set the position of targetMissile, same for its rotation, then draw it 
{

    float rotation = ( atan2( targetMissile.sprite.getPosition().y - spaceship.sprite.getPosition().y, targetMissile.sprite.getPosition().x - spaceship.sprite.getPosition().x ) ) * 180 / PI;//1 line to avoid using 2 more variables each frames

	targetMissile.sprite.setRotation(rotation-90);

	targetMissile.speed.x = cos(converterDegreeRadian(targetMissile.sprite.getRotation() + 90 * 3))*TARGET_MISSILE_SPEED;
    targetMissile.speed.y = sin(converterDegreeRadian(targetMissile.sprite.getRotation() + 90 * 3))*TARGET_MISSILE_SPEED;
    targetMissile.sprite.setPosition(Vector2f(targetMissile.sprite.getPosition().x + targetMissile.speed.x, targetMissile.sprite.getPosition().y + targetMissile.speed.y));

	game.draw(targetMissile.sprite);

}

