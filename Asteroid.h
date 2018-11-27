using namespace sf;

void initRandom();

void asteroidManager(Asteroid *asteroids, int &frames, float &secsInterval, bool &initGame, bool &reduce);

bool collidesWith(Asteroid asteroid, Missile missile);

bool collidesWith(Asteroid asteroid, Spaceship player);

Asteroid generateAsteroid(const int typeProbabilities[NB_TYPES]);

void asteroidsNextFrame(Asteroid *asteroids);

void drawAsteroids(RenderWindow *fenetre, Asteroid *asteroids);

void noAsteroidExist(Asteroid *asteroids);

//ceci est un commentaire utile