using namespace sf;

void initMissiles(Missile *missiles);

void drawMissiles(RenderWindow *fenetre, Missile *missiles);

ConvexShape missileShapeGenerator2000(char type, float angle);

bool shoot(Spaceship spaceshipWow, Missile *missiles, int *timeElapsedSinceLastShoot, bool firstCall, bool multiplayer);

void missilesNextFrame(Missile *missiles);

