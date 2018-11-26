using namespace sf;
void bossInit(int id, Spaceship &boss);
void bossUpdate(RenderWindow &game, Spaceship &boss, Spaceship &spaceship);
void bossMove(RenderWindow &game, Spaceship &boss, Spaceship &spaceship);
bool bossShoot(Spaceship spaceshipWow, Missile *missiles, int *timeElapsedSinceLastShoot, bool firstCall);
bool collidesWithSpaceshipMissile(Spaceship spaceship, Missile missile);
void bossLoosesLife(Spaceship *spaceship, int damage);
void collidesWithSpaceshipBoss(Spaceship &spaceship, Spaceship &boss);
void bossLifeBar(RenderWindow *window, Spaceship boss);
