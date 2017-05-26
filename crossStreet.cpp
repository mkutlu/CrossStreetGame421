#include<glut.h>
#include<iostream>//for strlen
#include<stdlib.h>
#include <random>
#include <math.h>
 
int i,q;
int score = 0;//for score counting
int screen = 0;
bool collide = false;//check if car collide to make game over
char buffer[10];
int coin_number = 0;

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
	int coinSizex = 5 + (rand() % (int)(20 - 5 + 1));
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
 
 
void ovpos()
{
    glClearColor(0,0,1,0);
for(i = 0; i < 4; i++)
{
    if(rand() % 2 == 0)
    {
        ovehicleX[i] = 200;
    }
    else
    {
        ovehicleX[i] = 300;
    }  
    ovehicleY[i] = 1000 - i * 160;
}
}
 /*Draw update */
 
void drawRoad()
{
    glBegin(GL_LINES); 
        glColor3f(0.5,0.5,0.5);
		glVertex2f(-1.0, 1.0);
        glVertex2f(-0.8, 1.0);
        glVertex2f(1.0, 1.0);
		glVertex2f(1.0 , 0.8);
    glEnd();
}
 
 
void drawDivider()//black patch drawn in middle of road
{
    glLoadIdentity();
    glTranslatef(0, movd, 0);
    for(i = 1; i <= 10; i++)
    {
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
        glVertex2f(divx  - 5, divy * 15 * i + 18);
        glVertex2f(divx  - 5, divy * 15 * i - 18);
        glVertex2f(divx  + 5, divy * 15 * i - 18);
        glVertex2f(divx  + 5, divy * 15 * i + 18);
    glEnd();
    }
    glLoadIdentity();
}
     
 
void drawVehicle()//car for racing
{
    glPointSize(10.0);
    glBegin(GL_POINTS);//tire
        glColor3f(0,0,0);                     
        glVertex2f(vehicleX - 25, vehicleY + 16); 
        glVertex2f(vehicleX + 25, vehicleY + 16); 
        glVertex2f(vehicleX - 25, vehicleY - 16); 
        glVertex2f(vehicleX + 25, vehicleY - 16);
    glEnd();
     
    glBegin(GL_QUADS);  
        glColor3f(1,0,0);//middle body
        glVertex2f(vehicleX - 25, vehicleY + 20);
        glVertex2f(vehicleX - 25, vehicleY - 20);
        glVertex2f(vehicleX + 25, vehicleY - 20);
        glVertex2f(vehicleX + 25, vehicleY + 20);
    glEnd();
 
    glBegin(GL_QUADS);//up body
        glColor3f(0,0,1);
        glVertex2f(vehicleX - 23, vehicleY + 20);
        glVertex2f(vehicleX - 19, vehicleY + 40);
        glVertex2f(vehicleX + 19, vehicleY + 40);
        glVertex2f(vehicleX + 23, vehicleY + 20);
    glEnd();
 
    glBegin(GL_QUADS);//down body
        glColor3f(0,0,1);
        glVertex2f(vehicleX - 23, vehicleY - 20);
        glVertex2f(vehicleX - 19, vehicleY - 35);
        glVertex2f(vehicleX + 19, vehicleY - 35);
        glVertex2f(vehicleX + 23, vehicleY - 20);
    glEnd();
 } 
  
void drawOVehicle()//other cars
{
     
    for(i = 0; i < 4; i++)
    {
    glPointSize(10.0);
    glBegin(GL_POINTS);//tire
        glColor3f(0,0,0);                     
        glVertex2f(ovehicleX[i] - 25, ovehicleY[i] + 16); 
        glVertex2f(ovehicleX[i] + 25, ovehicleY[i] + 16); 
        glVertex2f(ovehicleX[i] - 25, ovehicleY[i] - 16); 
        glVertex2f(ovehicleX[i] + 25, ovehicleY[i] - 16);
    glEnd();
     
    glBegin(GL_QUADS);  
        glColor3f(0.99609, 0.83984, 0);//middle body
        glVertex2f(ovehicleX[i] - 25, ovehicleY[i] + 20);
        glVertex2f(ovehicleX[i] - 25, ovehicleY[i] - 20);
        glVertex2f(ovehicleX[i] + 25, ovehicleY[i] - 20);
        glVertex2f(ovehicleX[i] + 25, ovehicleY[i] + 20);
    glEnd();
 
    glBegin(GL_QUADS);//up body
        glColor3f(0,1,0);
        glVertex2f(ovehicleX[i] - 23, ovehicleY[i] + 20);
        glVertex2f(ovehicleX[i] - 19, ovehicleY[i] + 40);
        glVertex2f(ovehicleX[i] + 19, ovehicleY[i] + 40);
        glVertex2f(ovehicleX[i] + 23, ovehicleY[i] + 20);
    glEnd();
 
    glBegin(GL_QUADS);//down body
        glColor3f(0,1,0);
        glVertex2f(ovehicleX[i] - 23, ovehicleY[i] - 20);
        glVertex2f(ovehicleX[i] - 19, ovehicleY[i] - 35);
        glVertex2f(ovehicleX[i] + 19, ovehicleY[i] - 35);
        glVertex2f(ovehicleX[i] + 23, ovehicleY[i] - 20);
    glEnd();
     
    ovehicleY[i] = ovehicleY[i] - 8; 
     
    if(ovehicleY[i] > vehicleY - 25 - 25 && ovehicleY[i] < vehicleY + 25 + 25 && ovehicleX[i] == vehicleX)
    {
        collide = true;
    }
     
    if(ovehicleY[i] < -25)
    { 
        if(rand() % 2 == 0)
        {
            ovehicleX[i] = 200;
        }
        else
        {
            ovehicleX[i] = 300;
        }
        ovehicleY[i] = 600; 
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
void Specialkey(int key, int x, int y)//allow to use navigation key for movement of car
{
	switch(key){
		case GLUT_KEY_LEFT:
			if(agentBack==false)
				updateAgent(-20,0);
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

 
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawRoad(); 
    drawDivider();
    drawVehicle();
    drawOVehicle();
    movd = movd - 16;
    if(movd < - 60)
    {
        movd = 0;
    }
     
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
        getchar();    }

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
		glVertex2f(liste[m].getCoinx(), liste[m].getCoiny()); // center of circle
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				liste[m].coinx + (liste[m].getCoinSize() * cos(i *  twicePi / triangleAmount)),
				liste[m].coiny + (liste[m].getCoinSize() * sin(i * twicePi / triangleAmount))
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
	coin coin_list[10];
	int roads[18] = { 26,51,76,126,151,176,201,251,276,301,326,376,401,426,451,501,526,551 };
	glColor3f(0.85, 0.85, 0.10);
	coin yeni;
	yeni.setCoinx(roads[0 + (rand() % (int)(17 - 0 + 1))]);
	yeni.setCoiny(0 + (rand() % (int)(500 - 0 + 1)));
	coin_list[0 + (rand() % (int)(10 - 0 + 1))] = yeni;
	return coin_list;
}
void drawCoin() {
	coin* coin_list;
	 coin_list=updateCoin();
	for (int m = 0; m < 10; m++) {
		int i;
		int triangleAmount = 20;
		GLfloat twicePi = 2.0f * 3.1415;

		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(coin_list[m].getCoinx(), coin_list[m].getCoiny()); // center of circle
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				coin_list[m].coinx + (coin_list[m].getCoinSize() * cos(i *  twicePi / triangleAmount)),
				coin_list[m].coiny + (coin_list[m].getCoinSize() * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
	}
}
void myTimer(int value) {
	drawCoin();
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
	//updateCoin(1);
	glColor3f(1, 1, 1);
	drawText("Score:", 360, 455);
	itoa(score, buffer, 10);
	drawTextNum(buffer, 6, 420, 455);
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
    glutCreateWindow("LOL");
	glClearColor(1.0, 1.0, 1.0, 1.0);
    init();
	glutTimerFunc(5,myTimer,0);
    glutDisplayFunc(myDisplay);
	glutSpecialFunc(Specialkey);
    glutIdleFunc(myDisplay);
    glutMainLoop();
}