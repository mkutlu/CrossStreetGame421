#include <random>
class coin {
public:
	int coinx;
	int coiny;
	int coinSizex =  5 + (rand() % (int)(20 - 5 + 1));
	void setCoinx(int x);
	int getCoinx();
	void setCoiny(int x);
	int getCoiny();
	void setCoinx(int x) {
		coinx = x;
	}
	void setCoiny(int x) {
		coiny = x;
	}
	int getCoinx() {
		return coinx;
	}
	int getCoiny() {
		return coiny;
	}
};
