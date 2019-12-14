#include "bmpfuncs.h"
#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <fstream>
#include "ObjParser.h"
#include "make_Lego.h"
#define M_pia 3.14159265358979323846
using namespace std;

//--------------회전 위치-----------//
int x_up = 0;
int y_up = 1;
int z_up = 0;
double cha = 5 * (M_PI / 180);
double pi = 50 * (M_PI / 180);
double the = 50 * (M_PI / 180);
double eyx = r * sin(the)*cos(pi);
double eyy = r * sin(the)*sin(pi);
double eyz = r * cos(the);

struct Gamecondition {
	int lego;
	double change_x;
	double change_y;
	double change_z;
	double changeangle;
	int lego_color_index;
	int text_index;
	int text_button;
	double min_x;
	double max_x;
	double min_y;
	double max_y;
	double min_z;
	double max_z;
};

Gamecondition gm;
GLuint texBackground[6]; vector<Gamecondition> Game1; vector<Gamecondition> Game2;
void cubeTextureMapping();
//char picture[][50];
//color paint[50];

void init(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0f, 500.0f, 500.0f, 0.0f);
	cubeTextureMapping();
	GLfloat ambientLight[] = { 0.2f,0.2f,0.2f,1.0f };
	GLfloat diffuseLight[] = { 0.7f,0.7f,0.7f,1.0f };
	GLfloat specularLight[] = { 0.9f,0.9f,0.9f,1.0f };
	GLfloat specularMaterial[] = { 1.0f,1.0f,1.0f,1.0f };
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMateriali(GL_FRONT, GL_SHININESS, 20);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	setTextureMapping();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void Gameresize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)width / (double)height, 1, 500);
	glMatrixMode(GL_MODELVIEW);
}

void cubeTextureMapping() {
	glGenTextures(6, texBackground);
	int imgWidth, imgHeight, channels;
	for (int i = 0; i < 6; i++) {
		glBindTexture(GL_TEXTURE_2D, texBackground[i]);
		char buf[100];
		sprintf(buf, "Tex/background%d.bmp", i);
		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgWidth, &imgHeight, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, /*INPUT CHANNEL*/3, imgWidth, imgHeight, 0, /*TEXEL CHANNEL*/GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

void draw_textureCube() {
   float xwidth = 300.0f; float ywidth = 100.0f; float zwidth = 300.0f;
   glPushMatrix();
   glTranslatef(0, ywidth-10, 0);
   glColor3f(1.0, 1.0, 1.0); 
   glBindTexture(GL_TEXTURE_2D, texBackground[0]);
   glBegin(GL_QUADS);
   glTexCoord2f(0, 0); glVertex3f(-xwidth, -ywidth, zwidth);
   glTexCoord2f(1, 0); glVertex3f(xwidth, -ywidth, zwidth);
   glTexCoord2f(1, 1); glVertex3f(xwidth, -ywidth, -zwidth);
   glTexCoord2f(0, 1); glVertex3f(-xwidth, -ywidth, -zwidth);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, texBackground[4]);
   glBegin(GL_QUADS);
   glTexCoord2f(0, 0); glVertex3f(-xwidth, -ywidth, zwidth);
   glTexCoord2f(1, 0); glVertex3f(xwidth, -ywidth, zwidth);
   glTexCoord2f(1, 1); glVertex3f(xwidth, ywidth, zwidth);
   glTexCoord2f(0, 1); glVertex3f(-xwidth, ywidth, zwidth);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, texBackground[3]);
   glBegin(GL_QUADS);
   glTexCoord2f(0, 0); glVertex3f(xwidth, -ywidth, zwidth);
   glTexCoord2f(1, 0); glVertex3f(xwidth, -ywidth, -zwidth);
   glTexCoord2f(1, 1); glVertex3f(xwidth, ywidth, -zwidth);
   glTexCoord2f(0, 1); glVertex3f(xwidth, ywidth, zwidth);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, texBackground[2]);
   glBegin(GL_QUADS);
   glTexCoord2f(0, 0); glVertex3f(xwidth, -ywidth, -zwidth);
   glTexCoord2f(1, 0); glVertex3f(-xwidth, -ywidth, -zwidth);
   glTexCoord2f(1, 1); glVertex3f(-xwidth, ywidth, -zwidth);
   glTexCoord2f(0, 1); glVertex3f(xwidth, ywidth, -zwidth);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, texBackground[1]);
   glBegin(GL_QUADS);
   glTexCoord2f(0, 0); glVertex3f(-xwidth, -ywidth, -zwidth);
   glTexCoord2f(1, 0); glVertex3f(-xwidth, -ywidth, zwidth);
   glTexCoord2f(1, 1); glVertex3f(-xwidth, ywidth, zwidth);
   glTexCoord2f(0, 1); glVertex3f(-xwidth, ywidth, -zwidth);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, texBackground[5]);
   glBegin(GL_QUADS);
   glTexCoord2f(0, 0); glVertex3f(-xwidth, ywidth, zwidth);
   glTexCoord2f(1, 0); glVertex3f(xwidth, ywidth, zwidth);
   glTexCoord2f(1, 1); glVertex3f(xwidth, ywidth, -zwidth);
   glTexCoord2f(0, 1); glVertex3f(-xwidth, ywidth, -zwidth);
   glEnd();
   glPopMatrix();
}

void Game1_draw_block() {
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyx, eyz, eyy, 0, 0, 0, x_up, y_up, z_up); //회전하기
	glPushMatrix();
	for (int i = 0; i < Game1.size(); i++) {
		glPushMatrix();
		glTranslatef(Game1[i].change_x, Game1[i].change_y, Game1[i].change_z);
		glRotated(Game1[i].changeangle, 0.0, 1.0, 0.0);
		object = picture[Game1[i].lego];
		if (Game1[i].text_button == 0) {
			glDisable(GL_TEXTURE_2D);
			glColor4f(paint[Game1[i].lego_color_index].R, paint[Game1[i].lego_color_index].G, paint[Game1[i].lego_color_index].B, 1.0f);	 //색깔바꾸기
			draw_obj(&object);
			glEnable(GL_TEXTURE_2D);
		}
		else if (Game1[i].text_button == 1) { //object 그리기
			draw_obj_with_texture(&object, Game1[i].text_index);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glFlush();
	glutPostRedisplay();
}

void Game_draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat emission[] = { 1.0f,1.0f,1.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	emission[0] = 0.0f;
	draw_textureCube();
	Game1_draw_block();
	glFlush();
	glutSwapBuffers();
}

void Gamekeyboard(unsigned char key, int x, int y) {
	if (key == 'a') {
		pi = pi - cha;
		eyx = r * sin(the)*cos(pi);
		eyy = r * sin(the)*sin(pi);
		eyz = r * cos(the);
	}
	else if (key == 'd') {
		pi = pi + cha;
		eyx = r * sin(the)*cos(pi);
		eyy = r * sin(the)*sin(pi);
		eyz = r * cos(the);
	}
	else if (key == 'w') {
		the = the + cha;
		if (the > 2 * M_PI)
			the -= 2 * M_PI;

		if (the > M_PI)
		{
			x_up = 0;
			y_up = -1;
			z_up = 0;
		}
		else if (the <= M_PI) {
			x_up = 0;
			y_up = 1;
			z_up = 0;
		}
		eyx = r * sin(the)*cos(pi);
		eyy = r * sin(the)*sin(pi);
		eyz = r * cos(the);

	}
	else if (key == 's') {
		the = the - cha;
		if (the < 0)
			the += 2 * M_PI;

		if (the > M_PI)
		{
			x_up = 0;
			y_up = -1;
			z_up = 0;
		}
		else if (the <= M_PI) {
			x_up = 0;
			y_up = 1;
			z_up = 0;
		}
		eyx = r * sin(the)*cos(pi);
		eyy = r * sin(the)*sin(pi);
		eyz = r * cos(the);

	}
	glutPostRedisplay();
}

void sub_Game_Loadtank1(int option) {
	fstream in("data2.txt");
	Game1.clear();
	if (in.is_open()) {
		for (int j = 0;; j++) {
			if (in.eof()) break;
			else if (j % 14 == 0)
				in >> gm.lego;
			else if (j % 14 == 1)
				in >> gm.change_x;
			else if (j % 14 == 2)
				in >> gm.change_y;
			else if (j % 14 == 3)
				in >> gm.change_z;
			else if (j % 14 == 4)
				in >> gm.changeangle;
			else if (j % 14 == 5)
				in >> gm.lego_color_index;
			else if (j % 14 == 6)
				in >> gm.text_index;
			else if (j % 14 == 7) {
				in >> gm.text_button;
			}
			else if (j % 14 == 8) {
				in >> gm.max_x;
			}
			else if (j % 14 == 9) {
				in >> gm.min_x;
			}
			else if (j % 14 == 10) {
				in >> gm.max_y;
			}
			else if (j % 14 == 11) {
				in >> gm.min_y;
			}
			else if (j % 14 == 12) {
				in >> gm.max_z;
			}
			else if (j % 14 == 13) {
				in >> gm.min_z;
				Game1.push_back(gm);
			}
		}
		printf("data1 open\n");
		Game_draw();
	}
	else {
		printf("파일이 없습니다.\n");
	}
	in.close();
}
void choose_mode(int option) {
	printf("Main menu %d \n", option);
}

int main(int argc, char **argv) {
	int Gamesubmenual1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 700);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Mini_project");
	//sub_Game_Loadtank1();
	//MakeLego_main();
	
	init();
	//sub_Game_Loadtank1();
	//sub_Game_Loadtank2();
	
	glutDisplayFunc(Game_draw);
	glutReshapeFunc(Gameresize);
	glutKeyboardFunc(Gamekeyboard);

	glutCreateMenu(sub_Game_Loadtank1);
	glutAddMenuEntry("Game Start", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutPostRedisplay();
	glutMainLoop();
	
	return 0;
}