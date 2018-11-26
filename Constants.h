// Global
#define PI 3.141593

// Hugo
#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1200
#define SPAWN_MARGIN 50 // Margin to spawn the asteroid outside the window with
#define MAX_SPEED 3 // Maximum asteroid speed
#define MAX_ANGULAR_VELOCITY 1
#define FLOAT_PRECISION 100.0 // 100.0 = Precision at 10^-2 : 1.01 - Used for all computed floats to generate the asteroid
#define NB_TYPES 3 // Number of types
#define NB_POINTS 6 // Number of points used to generate the asteroid
#define MIN_ASTEROID_RADIUS 30 // In pixels
#define MIN_ASTEROID_SPECIAL_RADIUS 5 // Type 3 radius
#define ASTEROID_RANDOMNESS_RANGE 20 // Fluctuation of the asteroid's radius when generating (max range)
#define ASTEROID_SPECIAL_RANDOMNESS_RANGE 2 // Type 3 fluctuation
#define INITIAL_ASTEROID_COUNT 4
#define INITIAL_SPAWN_INTERVAL 5.0 // In seconds
#define MIN_SPAWN_INTEVAL 1.0 // In seconds
#define SPAWN_MULTIPLICATOR_FACTOR 0.95 // (Spawn_Interval * Factor) each second
const int PROBABILITIES[NB_TYPES] = { 12, 8, 1 }; // Asteroids types probabilities

 // Rémi

#define ASTEROIDS_TABLE_LENGTH 50
#define LOST_HEALTH_WHEN_COLLIDES 25

// Léo
	//Constant spaceship
#define SPACESHIP_ROTATION_STRENGTH_MAX 4
#define SPACESHIP_SIZE 64 //a side of a spaceship sprite
#define SPACESHIP_ACCELERATION 0.1
#define SPACESHIP_DECELERATION 0.98 //To decelerate it when it's idle
#define SPACESHIP_LIFE 100
#define SPACESHIP_MAX_SPEED 4
#define NOKEYPRESSED P
#define SPACESHIP_BOUNCING_COEFFICIENT 3 //How much a spaceship bounce against everything
#define FRAME_RATE 60
#define MISSILE_TABLE_LENGTH 50
#define SPACESHIP_SHOOT_DELAY 40

	//Constant boss
#define BOSS_SPEED 1.2
#define BOSS_STOP_MOVE_ZONE SPACESHIP_SIZE/4
#define BOSS_SHOOT_DELAY 100 //delay between each shot
#define BOSS_SPAWN_TIME 60 //60 seconds
#define BOSS_SPEED_MISSILE 3
#define SCORE_BOSS 20
#define BOSS_LIFE 100

	//Constant heart
#define HEART_SIZE 32
#define HEART_SPEED 2
#define HEART_HEALTH_BONUS 15

	//Constant targetMissile
#define TARGET_MISSILE_SPEED 3
#define TARGET_MISSILE_DAMAGE 25

//Lilian


#define WINDOW_WIDTH 1200
#define WINDOW_HEIGH 800
#define MENU_BOX_HEIGHT 100
#define MENU_BOX_WIDTH_SPECIAL 390
#define MENU_BOX_WIDTH 800
#define MENU_OUTLINE 2
#define MENU_FONT_SIZE 70
#define SETTINGS_BOX_HEIGHT 100 
#define SETTINGS_BOX_WIDTH 300 
#define OUTLINE_SETTINGS_BOX 2
#define SETTINGS_BOX_GAP_WIDTH 200
#define SETTINGS_BOX_GAP_HEIGHT 80
#define SETTINGS_FONT_SIZE 50
#define ASK_KEY 100
#define BOOSTER_GAP_TOP 200
#define TASKBAR_OUTLINE_SIZE 10
#define PRICE 300