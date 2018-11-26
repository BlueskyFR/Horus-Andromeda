#ifndef DEPLACERSFML_H_INCLUDED
#define DEPLACERSFML_H_INCLUDED

const double SPACESHIP_RADIUS_DIAG = sqrt(pow(SPACESHIP_SIZE / 2, 2) * 2); //diagonale of the spaceship, from center

void initSpaceship(int id, Spaceship &spaceship);

void destroySpaceship(Spaceship &spaceship);

void updateSpaceship(RenderWindow &game, Spaceship &spaceship, bool firstCall, bool multiplayer);

void moveSpaceshipLeft(Spaceship &spaceship);
void moveSpaceshipRight(Spaceship &spaceship);
void moveSpaceshipDown(Spaceship &spaceship);
void moveSpaceshipUp(Spaceship &spaceship);
void moveSpaceship(Spaceship &spaceship);

void handleVirtualPlayer(Spaceship &spaceship);

void rotateSpaceshipLeft(Spaceship &spaceship, float spaceship_rotation_strength);
void rotateSpaceshipRight(Spaceship &spaceship, float spaceship_rotation_strength);

float converterDegreeRadian(float number);
void speedSpaceship(Spaceship &spaceship, Keyboard::Key KeyPressed, bool firstCall);
Keyboard::Key handleKeyBoard(Keyboard::Key keyInput, short keyNumber, char whatToDo);


void loosesLife(Spaceship *spaceship);
void lifeBar(RenderWindow *window, Font *font, int pvSpaceship);


#endif // DEPLACERSFML_H_INCLUDED

//REMETTRE COLLISIONS