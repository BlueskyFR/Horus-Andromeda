#include <SFML/Graphics.hpp>

#include "Constants.h"

using namespace sf;

enum struct DataType {
	Connection,

	// Native
	Int, // Uint32
	Float,
	Double,
	Bool,
	String,

	// Converted
	Asteroid,
	MissileType,
	Missile,
	Spaceship
};

typedef struct {
	float speed;
	float angle;
	float angularVelocity;
	bool exists;
	bool hasEnteredWindow;
	int type;
	ConvexShape shape;
} Asteroid;

typedef struct {
	int damage;
	int radius;
	char type;
} MissileType;

typedef struct {
	float speed;
	float angle;
	bool exists;
	int damage;
	int originSpaceship;
	MissileType type;
	ConvexShape shape;
} Missile;

typedef struct {
	int id;
	MissileType missile;
	Sprite sprite;
	Texture texture;
	Vector2f speed;
	bool isAlive;
	int shootDelay;
	int life;

} Spaceship;

typedef struct {//ADD
	Sprite sprite;
	Texture texture;
	Vector2f speed;
	bool exists;

} Heart;

typedef struct {//ADD
	Sprite sprite;
	Texture texture;
	Vector2f speed;
	bool exists;

} TargetMissile;