#pragma once

using namespace sf;

void initMissiles(Missile *missiles);

void drawMissiles(RenderWindow *fenetre, Missile *missiles);

ConvexShape missileShapeGenerator2000(char type);

bool shoot(Spaceship spaceshipWow, Missile *missiles, int *timeElapsedSinceLastShoot);

void missilesNextFrame(Missile *missiles);