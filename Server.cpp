#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "Structures.h"
#include "Server.h"
#include "Missile.h"

using namespace sf;
using namespace std;

DataType DataTypeOfIndex(int i) {
	return static_cast<DataType>(i);
}

int indexOfDataType(DataType dataType) {
	return static_cast<int>(dataType);
}

IpAddress ipAddress;
unsigned short port;

Asteroid *asteroids;
Missile *missiles;
Spaceship *spaceship1;
Spaceship *spaceship2;

Thread thread(listener);

void startListener(IpAddress ip, unsigned short p, Asteroid *a, Missile *m, Spaceship &s1, Spaceship &s2) {
	ipAddress = ip;
	port = p;

	asteroids = a;
	missiles = m;
	spaceship1 = &s1;
	spaceship2 = &s2;

	thread.launch();
}

UdpSocket socket;

void listener() {
	Packet packet;

	IpAddress senderIp;
	unsigned short senderPort;

	while (spaceship1->isAlive || spaceship2->isAlive) {
		socket.receive(packet, senderIp, senderPort);
		/*cout << "Packet received from " << senderIp << ":" << senderPort << "! " <<
			(packet.endOfPacket() ? "This packet is empty" : "There is content to read.") << endl;*/
		if (!packet.endOfPacket())
			processPacket(packet);
		/*cout << "Current ally position : X = " << spaceship2.sprite.getPosition().x << ", Y = " <<
			spaceship2.sprite.getPosition().y << endl;*/
	}
	thread.terminate();
}

void processPacket(Packet &packet) {
	Uint32 data;
	packet >> data;
	DataType dataType = DataTypeOfIndex(data);

	if (dataType == DataType::Connection) {
		cout << "Partner found : launch callback received! Launching game..." << endl;
		asteroids[0].exists = 1;
		printf("%i\n", asteroids[0].exists);
	}
	else if (dataType == DataType::Asteroid) {
		Asteroid asteroid;

		Uint32 nb;
		packet >> nb;
		int id = nb;


		packet >> asteroid.speed >> asteroid.angle >> asteroid.angularVelocity >>
			asteroid.exists >> asteroid.hasEnteredWindow;

		// ConvexShape

		Uint32 type;
		packet >> type;
		asteroid.type = type;

		Uint32 count;
		packet >> count;

		ConvexShape convexShape;
		convexShape.setPointCount(count);

		// Points
		/// Float
		float x, y;
		for (int i = 0; i < count; i++) {
			packet >> x >> y;
			convexShape.setPoint(i, Vector2f(x, y));
		}

		// Color
		/// R, G, B = Uint8
		Uint8 r, g, b;
		packet >> r >> g >> b;
		convexShape.setFillColor(Color::Color(r, g, b));

		// Position
		/// Float
		packet >> x >> y;
		convexShape.setPosition(x, y);

		asteroid.shape = convexShape;
		asteroid.shape.setOutlineColor(Color::White);
		asteroid.shape.setOutlineThickness(1.0);

		// id + asteroid
		float save = asteroids[id].shape.getRotation();
		asteroids[id] = asteroid;
		asteroids[id].shape.setRotation(save);
	}
	else if (dataType == DataType::MissileType) {
		MissileType missileType;

		Uint8 type;
		packet >> type;
		missileType.type = type;

		(*spaceship2).missile = missileType;
	}
	else if (dataType == DataType::Missile) {
		Missile missile;

		float speed, angle;
		packet >> speed >> angle;
		missile.speed = speed;
		missile.angle = angle;

		bool exists;
		packet >> exists;
		missile.exists = exists;

		Uint32 damage, originSpaceship;
		packet >> damage >> originSpaceship;
		missile.damage = damage;
		missile.originSpaceship = originSpaceship;

		// ConvexShape

		Uint8 type;
		packet >> type;
		missile.type.type = type;

		missile.shape = missileShapeGenerator2000(type, missile.angle);

		float x, y;
		packet >> x >> y;
		missile.shape.setPosition(x, y);

		for (int i = 0; i < MISSILE_TABLE_LENGTH; i++) {
			if (!missiles[i].exists) {
				missiles[i] = missile;
				break;
			}
		}
	}
	else if (dataType == DataType::Spaceship) {
		Spaceship spaceship;

		// Id
		Uint32 id;
		packet >> id;
		spaceship.id = id;

		// Missile (MissileType)
		Uint8 type;
		packet >> type;
		spaceship.missile.type = type;

		// Speed
		float speedX, speedY;
		packet >> speedX >> speedY;
		spaceship.speed.x = speedX;
		spaceship.speed.y = speedY;

		bool isAlive;
		packet >> isAlive;
		spaceship.isAlive = isAlive;

		Uint32 shootDelay;
		packet >> shootDelay;
		spaceship.shootDelay = shootDelay;

		float x, y, r;

		packet >> x >> y >> r;
		spaceship.sprite.setPosition(x, y);
		spaceship.sprite.setRotation(r);

		(*spaceship2).id = spaceship.id;
		(*spaceship2).isAlive = spaceship.isAlive;
		(*spaceship2).life = spaceship.life;
		(*spaceship2).missile = spaceship.missile;
		(*spaceship2).shootDelay = spaceship.shootDelay;
		(*spaceship2).shootDelay = spaceship.shootDelay;
		(*spaceship2).speed = spaceship.speed;
		(*spaceship2).sprite.setPosition(spaceship.sprite.getPosition());
		(*spaceship2).sprite.setRotation(spaceship.sprite.getRotation());
	}
	else {
		cout << "UNHANDLED DATATYPE ERROR!" << endl;
	}
}

void _sendPacket(Packet packet) {
	socket.send(packet, ipAddress, port);
}

void _convexShapeToPacket(ConvexShape convexShape, Packet &packet) {
	// Points Count
	int count = convexShape.getPointCount();
	packet << Uint32(count);

	// Points
	/// Float
	for (int i = 0; i < count; i++) {
		packet << convexShape.getPoint(i).x << convexShape.getPoint(i).y;
	}

	// Color
	/// R, G, B = Uint8
	packet << convexShape.getFillColor().r << convexShape.getFillColor().g <<
		convexShape.getFillColor().b;

	// Position
	/// Float
	packet << convexShape.getPosition().x << convexShape.getPosition().y;
}

void sendConnectionRequest() {
	cout << "Sending connection request... OF ID = ";
	Packet packet;
	DataType dataType = DataType::Connection;
	packet << Uint32(indexOfDataType(dataType));
	cout << indexOfDataType(dataType) << endl;

	_sendPacket(packet);
}

void sendData(Asteroid asteroid, int id) {
	cout << "Sending asteroid... OF ID = ";
	Packet packet;
	DataType dataType = DataType::Asteroid;
	packet << Uint32(indexOfDataType(dataType));
	cout << indexOfDataType(dataType) << endl;

	packet << Uint32(id);

	// Native properties
	packet << asteroid.speed << asteroid.angle << asteroid.angularVelocity <<
		asteroid.exists << asteroid.hasEnteredWindow << Uint32(asteroid.type);

	_convexShapeToPacket(asteroid.shape, packet);

	_sendPacket(packet);
}

void sendData(MissileType missileType) {
	cout << "Sending missileType... OF ID = ";
	Packet packet;
	DataType dataType = DataType::MissileType;
	packet << Uint32(indexOfDataType(dataType));
	cout << indexOfDataType(dataType) << endl;

	packet << Uint8(missileType.type);

	_sendPacket(packet);
}

void sendData(Missile missile) {
	cout << "Sending missile... OF ID = ";
	Packet packet;
	DataType dataType = DataType::Missile;
	packet << Uint32(indexOfDataType(dataType));
	cout << indexOfDataType(dataType) << endl;

	packet << missile.speed << missile.angle << missile.damage;
	packet << Uint32(missile.damage) << Uint32(missile.originSpaceship);

	packet << Uint8(missile.type.type);

	// Position
	/// Float
	packet << missile.shape.getPosition().x << missile.shape.getPosition().y;

	_sendPacket(packet);
}

void sendData(Spaceship spaceship) {
	//cout << "Sending position... OF ID = ";
	Packet packet;
	DataType dataType = DataType::Spaceship;
	packet << Uint32(indexOfDataType(dataType));
	//cout << indexOfDataType(dataType) << endl;

	// Id
	packet << Uint32(spaceship.id);

	// Missile (MissileType)
	packet << Uint8(spaceship.missile.type);

	// Speed
	packet << spaceship.speed.x << spaceship.speed.y;

	packet << spaceship.isAlive << Uint32(spaceship.shootDelay);

	packet << spaceship.sprite.getPosition().x << spaceship.sprite.getPosition().y <<
		spaceship.sprite.getRotation();

	_sendPacket(packet);
}