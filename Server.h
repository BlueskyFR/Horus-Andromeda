#include <SFML/Network.hpp>

using namespace sf;

DataType DataTypeOfIndex(int i);

int indexOfDataType(DataType dataType);

void startListener(IpAddress ipAddress, unsigned short p, Asteroid *a, Missile *m, Spaceship &s1, Spaceship &s2);

void listener();

void processPacket(Packet &packet);

void _sendPacket(Packet packet);

void _convexShapeToPacket(ConvexShape convexShape, Packet &packet);

void sendConnectionRequest();

void sendData(Asteroid asteroid, int id);

void sendData(MissileType missileType);

void sendData(Missile missile);

void sendData(Spaceship spaceship);