#include <random>
class car {
public:
	int carHeight;
	int carWidth;
	float truckX;
	float truckY;
	int speed;
	int line = 0 + (rand() % (int)(17 - 0 + 1));
};