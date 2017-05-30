#include <gl/glut.h>
#include <iostream>//for strlen
#include <stdlib.h>
#include <GL/freeglut.h>
#include <random>
#include <math.h>
#include <string>
#include <sstream>
#include <ctype.h>
#include <vector>  
#include <string>
using namespace std;
 
int i,q;
int score = 0;//for score counting
int screen = 0; // 0 home screen, 1 game screen, 2 game over
bool collide = false;//check if car collide to make game over
char buffer[10];
int coin_number = 0;
int counter = 0;
vector< string > names(1);
bool roadway[18] { true,true,false,false,true,false,false,true,true,false,false,true,false,true,false,true,false,true }; //true>right false>left 
int roads[18] = { 26,51,76,126,151,176,201,251,276,301,326,376,401,426,451,501,526,551 };
int speeds[18] = { 2,4,5,10,4,3,2,7,2,7,10,9,5,3,6,4,1,2 };
bool isdraw = false;
std::vector<int> allCarsx;
std::vector<int> allCarsy;
std::vector<int> allTrucksx;
std::vector<int> allTrucksy;


int vehicleX = 200, vehicleY = 70;   
int ovehicleX[4], ovehicleY[4];
int divx = 250, divy = 4, movd;

float agentX = 250;
float agentY = 0;
bool agentBack = false;
class coin {
public:
	int coinx;
	int coiny;
	int coinSizex = 10 + (rand() % (int)(10 - 5 + 1));
	void setCoinx(int x) {
		coinx = x;
	}
	void setCoiny(int y) {
		coiny = y;
	}
	int getCoiny() {
		return coiny;
	}
	int getCoinx() {
		return coinx;
	}
	int getCoinSize() {
		return coinSizex;
	}
};
coin* coin_list;

class car {
	public:
		int carx;
		int cary;
};
car* car_list;

void drawText(char ch[],int xpos, int ypos)//draw the text for score and game over
{
    int numofchar = strlen(ch);
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <= numofchar - 1; i++)
    {
     
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);//font used here, may use other font also
    }
} 
void drawTextNum(char ch[],int numtext,int xpos, int ypos)//counting the score
{
    int len;
    int k;
    k = 0;
    len = numtext - strlen (ch);
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <=numtext - 1; i++)
    {
    if ( i < len )
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
    else
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
        k++;
    }
     
    }
}
void updateAgent(int x, int y) {
	if (x >= 0 && y >= 0) {
		if (agentX > 460) {

		}
		else if(agentX<=460)
			agentX = agentX + x;
	}
	else if (x < 0 && y >= 0) {
		if (agentX < 12) {

		}
		else if (agentX >= 12) {
			agentX = agentX + x;
		}
	}
	if (x >= 0 && y >= 0) {
		if (agentY > 600) {

		}
		else if (agentY <= 600)
			agentY = agentY + y;
	}
	if (agentY > 575)
		agentBack = true;
}
void updateAgentBack(int x, int y) {
	if (x >= 0 && y >= 0) {
		if (agentX > 460) {

		}
		else if (agentX <= 460)
			agentX = agentX + x;
	}
	else if (x < 0 && y >= 0) {
		if (agentX < 12) {

		}
		else if (agentX >= 12) {
			agentX = agentX + x;
		}
	}
	if (y < 0) {
		if (agentY < 0) {

		}
		else if (agentY >=0)
			agentY = agentY + y;
	}
	if (agentY < 25)
		agentBack = false;
}
void OnMouseClick(int button, int state, int x, int y) {
	if (screen == 0) {
		y = 600 - y;
		cout << x;
		cout << " ";
		cout << y;
		if (button == GLUT_LEFT_BUTTON & x > 200 & x < 300 & y>400 & y < 440) {
			screen = 1;
		}
	}
}
void keyboard(unsigned char key,int x, int y) {
	if (key == 13)
	{
		// enter key
		return;
	}
	else if (key == 8)
	{
		if(names[0].size()!=0)
			names.back().pop_back();
	}
	else
	{
		// regular text
		if(names[0].size()<=20)
			names.back().push_back(key);
	}

	glutPostRedisplay();
}
void Specialkey(int key, int x, int y)//allow to use navigation key for movement of car
{
	if (screen == 1) {
		switch (key) {
		case GLUT_KEY_LEFT:
			if (agentBack == false)
				updateAgent(-20, 0);
			else
				updateAgentBack(-20, 0);
			break;
		case GLUT_KEY_RIGHT:
			if (agentBack == false)
				updateAgent(20, 0);
			else
				updateAgentBack(20, 0);
			break;
		case GLUT_KEY_UP:
			if (agentBack == false)
				updateAgent(0, 25);
			break;
		case GLUT_KEY_DOWN:
			if (agentBack == true)
				updateAgentBack(0, -25);
			break;
		}
		glutPostRedisplay();
	}
	if (screen == 0) {
		cout << "loll";
		glutPostRedisplay();
	}
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    score = score + 1;
    glColor3f(1,1,1);
    drawText("Score:", 360,455);
    itoa (score, buffer, 10);
    drawTextNum(buffer, 6, 420,455);
    glutSwapBuffers(); 
    for(q = 0; q<= 10000000; q++){;}
    if(collide == true)
    {
        glColor3f(0,0,0);
        drawText("Game Over", 200,250);
        glutSwapBuffers();
        getchar();   
 }

}
void drawSafePoint(int x, int y, int z, int w) {
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x, z);
		glVertex2f(w, z);
		glVertex2f(w, y);
	glEnd();
}
void drawRoadSpecs(int x) {
	int m = 0;
	while (m < 500) {
		glBegin(GL_LINES);
			glVertex2f(m, x);
			glVertex2f(m+20, x);
		glEnd();
		m += 40;
	}
}
void drawCoin(coin liste[]) {
	for (int m = 0; m < 10; m++) {
		int i;
		int triangleAmount = 20; //# of triangles used to draw circle

								 //GLfloat radius = 0.8f; //radius
		GLfloat twicePi = 2.0f * 3.1415;

		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(coin_list[m].getCoinx(), coin_list[m].getCoiny()); // center of circle
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				liste[m].coinx + (coin_list[m].getCoinSize() * cos(i *  twicePi / triangleAmount)),
				coin_list[m].coiny + (coin_list[m].getCoinSize() * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
	}
}
void drawAgent() {
	if (agentBack == false) {
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_TRIANGLES);
			glVertex2f(agentX, agentY);
			glVertex2f(agentX + 12.5, agentY + 25);
			glVertex2f(agentX + 25, agentY);
		glEnd();
	}
	else {
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(agentX, agentY);
		glVertex2f(agentX + 12.5, agentY - 25);
		glVertex2f(agentX + 25, agentY);
		glEnd();
	}
}
coin* updateCoin() {
	if (collide) {

	}
	else {
		coin_list = new coin[10];
		for (int i = 0; i <= 10; i++) {

		}
		for (int m = 0; m < 10; m++) {
			int roads[18] = { 26,51,76,126,151,176,201,251,276,301,326,376,401,426,451,501,526,551 };
			coin yeni;
			yeni.setCoinx(0 + (rand() % (int)(500 - 0 + 1)));
			yeni.setCoiny(roads[0 + (rand() % (int)(17 - 0 + 1))] + 12.5);
			cout << yeni.coinx;


			coin_list[m] = yeni;
		}
		return coin_list;
	}
}
void drawCoin() {
	for (int m = 0; m < 10; m++) {
		int i;
		int triangleAmount = 20;
		GLfloat twicePi = 2.0f * 3.1415;
		glColor3f(0.85, 0.85, 0.10);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(coin_list[m].coinx, coin_list[m].coiny); // center of circle
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				coin_list[m].coinx + (coin_list[m].getCoinSize() * cos(i *  twicePi / triangleAmount)),
				coin_list[m].coiny + (coin_list[m].getCoinSize() * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
	}
}
void drawVehicle() {
	float carx ;
	float cary ;
	int num = allCarsy.size();

	for (int m = 0; m< num; m++) {
		carx = allCarsx[m];
		cary = allCarsy[m];
		
		
		glColor3f(0.75, 0.75, 0.75);

		glBegin(GL_QUADS);
		glVertex2f(carx, cary);
		glVertex2f(carx, cary + 9);
		glVertex2f(carx + 12, cary + 12);
		glVertex2f(carx + 12, cary);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(carx + 12, cary);
		glVertex2f(carx + 12, cary + 12);
		glVertex2f(carx + 30, cary + 12);
		glVertex2f(carx + 30, cary);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(carx + 30, cary);
		glVertex2f(carx + 30, cary + 12);
		glVertex2f(carx + 42, cary + 9);
		glVertex2f(carx + 42, cary);
		glEnd();
		glBegin(GL_QUADS);

		glVertex2f(carx + 12, cary + 9);
		glVertex2f(carx + 12, cary + 20);
		glVertex2f(carx + 30, cary + 20);
		glVertex2f(carx + 30, cary + 9);

		glEnd();
		glBegin(GL_LINES);
		glVertex2f(carx + 9, cary + 9);
		glVertex2f(carx + 12, cary + 18);
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(carx + 33, cary + 9);
		glVertex2f(carx + 30, cary + 18);
		glEnd();

		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);

		glVertex2f(carx + 14, cary + 11);
		glVertex2f(carx + 14, cary + 18);
		glVertex2f(carx + 28, cary + 18);
		glVertex2f(carx + 28, cary + 11);

		glEnd();
		int i;
		int triangleAmount = 20;
		GLfloat twicePi = 2.0f * 3.1415;
		glColor3f(0, 0, 0);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(carx + 12, cary); // center of circle
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				carx + 12 + (3 * cos(i *  twicePi / triangleAmount)),
				cary + (3 * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(carx + 30, cary); // center of circle
		glVertex2f(carx + 12, cary); // center of circle
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				carx + 30 + (3 * cos(i *  twicePi / triangleAmount)),
				cary + (3 * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
	}

	
}
void drawTruck() {
	float truckx;
	float trucky;
	int num = allTrucksy.size();

	for (int m = 0; m < num; m++) {
		truckx = allTrucksx[m];
		trucky = allTrucksy[m];
		glColor3f(0.545, 0.271, 0.075);
		glBegin(GL_QUADS);
		glVertex2f(truckx, trucky);
		glVertex2f(truckx, trucky + 20);
		glVertex2f(truckx + 44, trucky + 20);
		glVertex2f(truckx + 44, trucky);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(truckx + 45, trucky);
		glVertex2f(truckx + 45, trucky + 17);
		glVertex2f(truckx + 62, trucky + 17);
		glVertex2f(truckx + 62, trucky);
		glEnd();
		int i;
		int triangleAmount = 20;
		GLfloat twicePi = 2.0f * 3.1415;
		glColor3f(0, 0, 0);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(truckx + 8, trucky); // center of circle
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				truckx + 8 + (3 * cos(i *  twicePi / triangleAmount)),
				trucky + (3 * sin(i * twicePi / triangleAmount))
			);
		}
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(truckx + 15, trucky); // center of circle
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				truckx + 15 + (3 * cos(i *  twicePi / triangleAmount)),
				trucky + (3 * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(truckx + 45, trucky); // center of circle
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				truckx + 45 + (3 * cos(i *  twicePi / triangleAmount)),
				trucky + (3 * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
	}
}
void createCar(int x, int y) {
	allCarsy.push_back(y);
	allCarsx.push_back(x);
}
void createTruck(int x, int y) {
	allTrucksy.push_back(y);
	allTrucksx.push_back(x);
}
void updateVehicles(int i) {
	if (collide == true) {

	}
	else {
		int carNum = 0;
		bool busy = false;
		bool busyright = false;
		for (int i = 0; i < 18; i++) {
			//cout << allCarsx.size();
			//cout << " m ";
			int length = allCarsy.size();
			allCarsy.resize(length);
			for (int i = 0; i < length; i++) {
				if (roadway[i] & allCarsx[i] <= 40 & allCarsx[i] >= -20)
					busy = true;
				else if (roadway[i] != true & allCarsx[i] >= 470 & allCarsx[i] <= 520)
					busyright = true;
			}
			for (int m = 0; m < length; m++) {
				if (roadway[m]) {
					if (allCarsx[m] >= 500 & !busy)
						allCarsx[m] = -20;
				}
				else
					if (allCarsx[m] <= 0 & !busyright)
						allCarsx[m] = 520;
				if (allCarsy[m] == roads[i])
					carNum++;
			}
			if (carNum <= 2) {
				int rando = 0 + (rand() % (int)(3 - 0 + 1));
				if (rando == 1 || rando == 2) {
					if (roadway[i]) {
						createCar(-20, roads[i]);
					}
					else
						createCar(520, roads[i]);
				}
				else {
					if (roadway[i]) {
						createTruck(-20, roads[i]);
					}
					else
						createTruck(520, roads[i]);
				}
			}
		}
		int num = allCarsy.size();
		for (int i = 0; i < num; i++) {
			if (roadway[i])
				allCarsx[i] = allCarsx[i] + speeds[i];
			else
				allCarsx[i] = allCarsx[i] - speeds[i];
			if (agentX + 12.5 >= allCarsx[i] & agentX + 12.5 <= allCarsx[i] + 42 & agentY + 12.5 >= allCarsy[i] & agentY + 12.5 <= allCarsy[i] + 20)
				collide = true;

		}
		int num2 = allTrucksy.size();
		for (int i = 0; i < num2; i++) {
			if (roadway[i])
				allTrucksx[i] = allTrucksx[i] + speeds[i];
			else
				allTrucksx[i] = allTrucksx[i] - speeds[i];
			if (agentX + 12.5 >= allTrucksx[i] & agentX + 12.5 <= allTrucksx[i] + 62 & agentY + 12.5 >= allTrucksy[i] & agentY + 12.5 <= allTrucksy[i] + 20)
				collide = true;
		}
		glutTimerFunc(100, updateVehicles, 1);
	}
}
void myTimer(int value) {
	updateCoin();
	cout << "lol";
	glutTimerFunc(20000, myTimer, 1);
}
void coinInit() {
	if (counter != 0) {

	}
	else {
		updateCoin();
		counter++;
	}
}
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	drawSafePoint(0, 0, 25, 500);
	drawSafePoint(0, 100, 125, 500);
	drawSafePoint(0, 225, 250, 500);
	drawSafePoint(0, 350, 375, 500);
	drawSafePoint(0, 475, 500, 500);
	drawSafePoint(0, 575, 600, 500);
	glColor3f(0.0, 0.0, 0.0);
	drawRoadSpecs(50);
	drawRoadSpecs(75);
	drawRoadSpecs(150);
	drawRoadSpecs(175);
	drawRoadSpecs(200);
	drawRoadSpecs(275);
	drawRoadSpecs(300);
	drawRoadSpecs(325);
	drawRoadSpecs(400);
	drawRoadSpecs(425);
	drawRoadSpecs(450);
	drawRoadSpecs(525);
	drawRoadSpecs(550);
	drawAgent();
	drawCoin();
	drawVehicle();
	drawTruck();
	glColor3f(1, 0, 1);
	if (collide == true) {
		drawText("Game over! Score:", 250, 250);
		itoa(score, buffer, 10);
		drawTextNum(buffer, 6, 250, 220);
	}
	drawText("Score:", 360, 575);
	itoa(score, buffer, 10);
	drawTextNum(buffer, 6, 420, 575);
	glutSwapBuffers();
	glFlush();
}
void homeScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0, 0, 0);
		char* ch = "Legend of Street";
		int numofchar = strlen(ch);
		glLoadIdentity();
		glRasterPos2f(150, 480);
		for (i = 0; i <= numofchar - 1; i++)
		{

			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ch[i]);//font used here, may use other font also
		}
		//drawText("Legend of Street", 200, 480);
		glColor3f(0.75, 0.75, 0.75);
		glBegin(GL_QUADS);
		glVertex2f(200, 400);
		glVertex2f(200, 440);
		glVertex2f(300, 440);
		glVertex2f(300, 400);
		glEnd();
		glBegin(GL_QUADS);
		glVertex2f(200, 350);
		glVertex2f(200, 390);
		glVertex2f(300, 390);
		glVertex2f(300, 350);
		glEnd();
		glColor3f(0, 0, 0);
		drawText("EASY", 225, 412);
		drawText("A bit Hard", 208, 362);
		drawText("Enter your nickname for High Scores:", 100, 280);
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glVertex2f(140, 240);
		glVertex2f(140, 270);
		glVertex2f(370,	270);
		glVertex2f(370, 240);
		glEnd();
		glColor3f(0, 0, 0);
		for (size_t i = 0; i < names.size(); ++i)
		{
			ostringstream oss;
			oss << (i + 1) << ": " << names[i];

			void* font = GLUT_BITMAP_9_BY_15;
			const int fontHeight = glutBitmapHeight(font);
			glRasterPos2i(160, 260 - (fontHeight * (i + 1)));
			glutBitmapString(font, (const unsigned char*)(oss.str().c_str()));
		}
		if (screen == 1) {
			glClearColor(1.0, 1.0, 1.0, 1.0);
			coinInit();
			glutTimerFunc(20000, myTimer, 1);
			glutTimerFunc(100, updateVehicles, 0);
			glutDisplayFunc(myDisplay);
			glutSpecialFunc(Specialkey);
			glutIdleFunc(myDisplay);
		}
	glutSwapBuffers();
	glFlush();
}
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 600);
	glMatrixMode(GL_MODELVIEW);
}

void main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,600);
    glutCreateWindow("Lol");
	init();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	if (screen == 0) {
		glClearColor(0.5, 1.0, 0.5, 1);
		glutDisplayFunc(homeScreen);
		glutKeyboardFunc(keyboard);
		glutMouseFunc(OnMouseClick);
	}
	else if (screen == 1) {
		coinInit();
		glutTimerFunc(20000, myTimer, 1);
		glutTimerFunc(100, updateVehicles, 0);
		glutDisplayFunc(myDisplay);
		glutSpecialFunc(Specialkey);
		glutIdleFunc(myDisplay);
	}
	cout << "lol";

	
    glutMainLoop();
}