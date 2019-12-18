#ifndef  MAKE_LEGO_H
#define  MAKE_LEGO_H
#pragma comment(lib, "winmm.lib")
#include "bmpfuncs.h"
#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <fstream>
#include <Windows.h>
#include <Mmsystem.h>
#include "mapping.h"
#include "ObjParser.h"
#include "GL/glext.h"
#define M_PI 3.14159265358979323846
using namespace std;
//-------------Game mode-----------//
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
Gamecondition gm; int map_toggle;
vector<Gamecondition> Game1; 
vector<Gamecondition> Game2;
extern void Game_draw();
extern void cubeTextureMapping();
extern void sub_Game_Loadtank1();
extern void sub_Game_Loadtank2();
extern void skyboxMapping();
extern void draw_canon();
//--------------Player1회전 위치-----------//
int x_up1 = 0;
int y_up1 = 1;
int z_up1 = 0;
double half1 = 20;
double cha1 = 5 * (M_PI / 180);
double pi1 = (M_PI / 180);
double the1 = (M_PI / 180);
double eyx1 = half1 * sin(the1)*cos(pi1);
double eyy1 = half1 * sin(pi1);
double eyz1 = half1 * cos(the1)*cos(pi1);
//--------------Player2회전 위치-----------//
int x_up2 = 0;
int y_up2 = 1;
int z_up2 = 0;
double half2 = 25;
double cha2 = 5 * (M_PI / 180);
double pi2 = (M_PI / 180);
double the2 = (M_PI / 180);
double eyx2 = half2 * sin(the2)*cos(pi2);
double eyy2 = half2 * sin(the2)*sin(pi2);
double eyz2 = half2 * cos(the2);
//--------------회전 위치-----------//
int xup = 0;
int yup = 1;
int zup = 0;
double change = 5 * (M_PI / 180);
double r = 10;
double pian = 50 * (M_PI / 180);
double thean = 50 * (M_PI / 180);
double eyex = r * sin(thean)*cos(pian);
double eyey = r * sin(thean)*sin(pian);
double eyez = r * cos(thean);


//-------------drag변수-------------------//
int drag_x;
int drag_y;
int dragging = 0;
double camera_angle_h = 0;
double camera_angle_v = 0;

//--------------location 위치-----------//
int changeflag = 0;
float location_x, location_y, location_z;
double changeangle;
//--------------color 위치-----------//
int picture_index, color_index, merge_index;

struct condition {
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
struct color {
	float R;
	float G;
	float B;
};
struct collision {
	double min_x;
	double max_x;
	double min_y;
	double max_y;
	double min_z;
	double max_z;
};
vector<condition> Lego; condition cond; float angel1 = 0; float angel2; float angel3; ObjParser object; int text_index; int Gamemode; int situation; double move_theta; double move_theta2;
void setTextureMapping(); double value1; double value2; int canon_toggle; ObjParser can; int player_mode;
condition canon1; condition canon2; double canon_angle; int canon_count1; int canon_count2; int vs;
GLuint texture[6]; GLfloat light_position[] = { eyex,eyey,eyez,1.0 };
collision box[50] = { {1.4,2.5,0.5,0.5,1.5,1.5}, {1.4,2.5,0.5,0.5,1.5,1.5}, {0.35,0.35,0.5,0.5,1,1},{0.6,0.6,0.6,0.6,0.25,0.25}, {2.5,2.5,0.75,0.75,0.75,0.75}, {0.12,0.12,1.2,1.2,1.2,1.2},{0.9,1,0.1,0.1,1,1},{0.9,1,0.1,0.1,1,1},{1,1,0,0.05,1,1},{1.5,1.5,0,1,0.3,0.3},{0,2.6,0,1,0.5,0.5},{0.5,0.5,0.75,0.75,0.75,0.75} };
char picture[][50] = { "image/body2-1.obj","image/body2-2.obj","image/body2-3.obj","image/Leg1.obj","image/Leg2.obj","image/Leg3.obj","image/body1-1.obj","image/body1-2.obj","image/body1-3.obj","image/head1-1.obj","image/head1-2.obj","image/head1-3.obj","image/canon.obj" };
color paint[50] = { {1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{ 0.0f,0.0f,1.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,1.0f},{0.5f,0.5f,0.5f},{0.5f,0.0f,0.5f},{1.0f,0.0f,1.0f},{0.0f,0.5f,0.5f} };//red, green, blue, yellow, aqua, gray, purple ,fuchsia, teal;
void draw_obj(ObjParser *object);

void init_makeLego(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0f, 500.0f, 500.0f, 0.0f);
	GLfloat ambientLight[] = { 0.2f,0.2f,0.2f,1.0f };
	GLfloat diffuseLight[] = { 1.0f,1.0f,1.0f,1.0f };
	GLfloat specularLight[] = { 1.0f,1.0f,1.0f,1.0f };

	GLfloat diffuseMaterial[] = { 0.5,0.5,0.5,1.0 };
	GLfloat ambientMaterial[] = { 0.2,0.2,0.2,1.0 };
	GLfloat specularMaterial[] = { 1.0f,1.0f,1.0f,1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseLight);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);
	cubeTextureMapping();
	setTextureMapping();
	skyboxMapping();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void idle(void) {
	angel1 = angel1 + 0.05;
	if (angel1 > 360) { angel1 -= 360; }
	if (situation == 1) {
		angel2 = angel2 - 10;
		if (angel2 != 0 && (int)angel2 % 10 == 0) {
			situation = 0;
		}
		if (angel2 < 0) { angel2 += 360; }
	}
	if (situation == 2) {
		angel3 = angel3 + 10;
		if (angel3 != 0 && (int)angel3 % 10 == 0) {
			situation = 0;
		}
	}
	if (canon_toggle == 1) {
		canon_angle = canon_angle + 1;
		if (canon_angle > 180) {
			canon_angle -= 180;
			if (player_mode == 2) {
				for (int i = 0; i < Game1.size(); i++) {
					if ((int)Game1[i].change_x*(-1) -1 >= canon.change_x && (int)Game1[i].change_x*(-1) + 1 <= canon.change_x)
						vs = 2;
				}
			}
			else if (player_mode == 1) {
				for (int i = 0; i < Game2.size(); i++) {
					if ((int)Game2[i].change_x*(-1) - 2 <= canon.change_x && (int)Game2[i].change_x*(-1) + 2 >= canon.change_x)
						vs = 1;
				}
			}
			canon_toggle = 0;

			if (player_mode == 1)
				player_mode = 2;
			else if (player_mode == 2)
				player_mode = 1;

		}
	}
}

void resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)width / (double)height, 1, 500);
	glMatrixMode(GL_MODELVIEW);
}

void draw_string(void * font, const char *str, int x, int y) {
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-5, 15, -5, 15);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos3f(x, y, 0);
	for (unsigned int i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}

void draw_axies() {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(4, 0, 0);
	glColor3f(1, 1, 1);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);
	glColor3f(1, 1, 1);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);
	glColor3f(1, 1, 1);

	glEnd();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void draw_obj(ObjParser *object) {
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < object->getFaceSize(); n += 3) {
		glNormal3f(object->normal[object->normalIdx[n] - 1].x, object->normal[object->normalIdx[n] - 1].y
			, object->normal[object->normalIdx[n] - 1].z);
		glVertex3f(object->vertices[object->vertexIdx[n] - 1].x, object->vertices[object->vertexIdx[n] - 1].y
			, object->vertices[object->vertexIdx[n] - 1].z);


		glNormal3f(object->normal[object->normalIdx[n + 1] - 1].x, object->normal[object->normalIdx[n + 1] - 1].y
			, object->normal[object->normalIdx[n + 1] - 1].z);
		glVertex3f(object->vertices[object->vertexIdx[n + 1] - 1].x, object->vertices[object->vertexIdx[n + 1] - 1].y
			, object->vertices[object->vertexIdx[n + 1] - 1].z);


		glNormal3f(object->normal[object->normalIdx[n + 2] - 1].x, object->normal[object->normalIdx[n + 2] - 1].y
			, object->normal[object->normalIdx[n + 2] - 1].z);
		glVertex3f(object->vertices[object->vertexIdx[n + 2] - 1].x, object->vertices[object->vertexIdx[n + 2] - 1].y
			, object->vertices[object->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glutPostRedisplay();
}

void setTextureMapping() {
	int texNum = 6;
	glGenTextures(texNum, texture);
	int imgWidth, imgHeight, channels;
	for (int i = 0; i < 6; i++) {
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		char buf[100];
		sprintf(buf, "Tex/Tex%d.bmp", i);
		buf[strlen(buf)] = 0;
		uchar* img = readImageData(buf, &imgWidth, &imgHeight, &channels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	//GL_REPEAT 둘중 하나 선택
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

void draw_obj_with_texture(ObjParser *objParser, int text_index)
{
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);	// texture 색 보존을 위한 enable
	glBindTexture(GL_TEXTURE_2D, texture[text_index]);
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glTexCoord2f(objParser->textures[objParser->textureIdx[n] - 1].x,
			objParser->textures[objParser->textureIdx[n] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 1] - 1].x,
			objParser->textures[objParser->textureIdx[n + 1] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);

		glTexCoord2f(objParser->textures[objParser->textureIdx[n + 2] - 1].x,
			objParser->textures[objParser->textureIdx[n + 2] - 1].y);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
	glEnable(GL_BLEND);
}


void draw_text() {
	glDisable(GL_TEXTURE_2D);
	glViewport(0, 30, 200, 700);
	glLoadIdentity();
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "l : GO Forward", 0, 0);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "j : GO backward", 0, 1);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "k : GO to Left", 0, 2);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "L : Go to Right", 0, 3);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, ", : Go to Top", 0, 4);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, ". : Go to Down", 0, 5);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "u : Remove Lego", 0, 6);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "c : Change color", 0, 7);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "t : Change Texture", 0, 8);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "space bar : Choose Lego ", 0, 9);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "- : Spin to Top", 0, 10);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "= : Spin to Down", 0, 11);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "9 : Spin 90 angle for Left ", 0, 12);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "0 : Spin 90 angle for Right ", 0, 13);
	glEnable(GL_TEXTURE_2D);
	glFlush();
}
void draw_vs() {
	glDisable(GL_TEXTURE_2D);
	glViewport(0, 300, 600, 300);
	glLoadIdentity();
	if(vs == 2)
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "PLAYER 1 WIN ", 0, 1);
	else if(vs ==1)
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "PLAYER 2 WIN ", 0, 1);
	glEnable(GL_TEXTURE_2D);
	glFlush();
}

void draw_preview() {
	glDisable(GL_TEXTURE_2D);
	object = (picture[picture_index]);
	glViewport(900, 400, 300, 300);
	glLoadIdentity();
	glColor3f(0.5f, 0.5f, 0.5f);
	gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
	glRotatef(angel1, 0, 1, 0);
	draw_obj(&object);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "Preview", 0, 10);
	glEnable(GL_TEXTURE_2D);
	glFlush();
	glutPostRedisplay();
}

void draw_merge_block() {
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glViewport(300, 100, 800, 500);
	glLoadIdentity();
	gluLookAt(eyex, eyez, eyey, 0, 0, 0, xup, yup, zup); //회전하기
	glPushMatrix();
	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	for (int i = 0; i < Lego.size(); i++) {
		glPushMatrix();
		glTranslatef(Lego[i].change_x, Lego[i].change_y, Lego[i].change_z);
		glRotated(Lego[i].changeangle, 0.0, 1.0, 0.0);
		object = picture[Lego[i].lego];
		if (Lego[i].text_button == 0) {
			glDisable(GL_TEXTURE_2D);
			glColor4f(paint[Lego[i].lego_color_index].R, paint[Lego[i].lego_color_index].G, paint[Lego[i].lego_color_index].B, 1.0f);	 //색깔바꾸기
			draw_obj(&object);
			glEnable(GL_TEXTURE_2D);
		}
		else if (Lego[i].text_button == 1) { //object 그리기
			glEnable(GL_TEXTURE_2D);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			draw_obj_with_texture(&object, Lego[i].text_index);
			glDisable(GL_TEXTURE_2D);
		}
		glPopMatrix();
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glFlush();
	glutPostRedisplay();
}

void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (Gamemode == 0) {
		glPushMatrix();
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_CUBE_MAP);
		draw_preview();
		draw_text();
		draw_merge_block();
		draw_axies();
		glPopMatrix();

	}
	else if (Gamemode == 1) {
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_CUBE_MAP);
		if (player_mode == 1) {
			glPushMatrix();			
			Game_draw();
			draw_canon();
			if (vs == 1)
				draw_vs();
			glPopMatrix();
		}
		else if (player_mode == 2){
			glPushMatrix();	
			Game_draw();
			draw_canon();
			if (vs == 2)
				draw_vs();
			glPopMatrix();
		}
		glPopMatrix();
	}
	glutSwapBuffers();
}

bool check_collision(condition a, condition b) {

	if (((a.max_y <= b.max_y) && (a.max_y >= b.min_y)) || ((a.max_y >= b.max_y) && (a.min_y <= b.max_y))) {
		if (((a.max_z <= b.max_z) && (a.max_z >= b.min_z)) || ((a.max_z >= b.max_z) && (a.min_z <= b.max_z))) {
			if (((a.max_x <= b.max_x) && (a.max_x >= b.min_x)) || ((a.max_x >= b.max_x) && (a.min_x <= b.max_x))) {
				return false;
			}
		}
	}
	return true;
}

void mouse_move(int x, int y) {
	if (dragging) {
		camera_angle_v = camera_angle_v + (y - drag_y)*0.4;
		camera_angle_h = camera_angle_h + (x - drag_x)*0.4;
		drag_x = x;
		drag_y = y;
	}
}

void mouse(int button, int state, int x, int y) {
	if (button == 4) {
		r = r + 1;
		half1 = half1 + 1;
		half2 = half2 + 1;
		eyex = r * sin(thean)*cos(pian);
		eyey = r * sin(thean)*sin(pian);
		eyez = r * cos(thean);
	}
	else if (button == 3) {
		r = r - 1;
		half1 = half1 - 1;
		half2 = half2 - 1;
		if (r < 5) r = 5;
		if (half1 < 5) half1 = 5;
		if (half2 < 5) half2 = 5;
		eyex = r * sin(thean)*cos(pian);
		eyey = r * sin(thean)*sin(pian);
		eyez = r * cos(thean);
	}
	else if ((state == GLUT_DOWN) && (button == GLUT_LEFT_BUTTON)) {
		dragging = 1;
		drag_x = x;
		drag_y = y;
	}
	else
		dragging = 0;
}

void keyboard(unsigned char key, int x, int y) {
	if (Gamemode == 0) {
		if (key == 'f') {
			picture_index = picture_index + 1;
			if (picture_index == 12) picture_index = 0;
		}
		else if (key == 'c') {
			Lego[Lego.size() - 1].text_button = 0;
			color_index = color_index + 1;
			if (color_index == 9) color_index = 0;
			Lego[Lego.size() - 1].lego_color_index = color_index;
		}
		else if (key == VK_SPACE) {
			merge_index = picture_index;
			cond.lego = merge_index;
			cond.max_x = 3 + box[merge_index].max_x;
			cond.min_x = 3 - box[merge_index].min_x;
			cond.max_y = +box[merge_index].max_y;
			cond.min_y = -box[merge_index].min_y;
			cond.max_z = +box[merge_index].max_z;
			cond.min_z = -box[merge_index].min_z;
			cond.change_x = 3;
			Lego.push_back(cond);
		}
		else if (key == 't') {
			Lego[Lego.size() - 1].text_button = 1;
			text_index = text_index + 1;
			if (text_index == 6) text_index = 0;
			Lego[Lego.size() - 1].text_index = text_index;
		}
		else if (key == 'l') {
			bool flag;
			Lego[Lego.size() - 1].change_z = Lego[Lego.size() - 1].change_z - 0.1;
			Lego[Lego.size() - 1].min_z = Lego[Lego.size() - 1].min_z - 0.1;
			Lego[Lego.size() - 1].max_z = Lego[Lego.size() - 1].max_z - 0.1;
			for (int i = 0; i < Lego.size() - 1; i++) { //모든 도형에 대해 체크
				flag = check_collision(Lego[Lego.size() - 1], Lego[i]);
				if (flag == false) {
					if ((Lego[Lego.size() - 1].changeangle) == 0 || (Lego[Lego.size() - 1].changeangle == 180)) {
						Lego[Lego.size() - 1].change_z = Lego[i].change_z + (box[Lego[Lego.size() - 1].lego].max_z + box[Lego[i].lego].min_z);
					}
					else if ((Lego[Lego.size() - 1].changeangle) == 90 || (Lego[Lego.size() - 1].changeangle == 270)) {
						Lego[Lego.size() - 1].change_z = Lego[i].change_z + (box[Lego[Lego.size() - 1].lego].max_x + box[Lego[i].lego].max_z);
					}
					Lego[Lego.size() - 1].min_z = Lego[Lego.size() - 1].min_z + 0.1;
					Lego[Lego.size() - 1].max_z = Lego[Lego.size() - 1].max_z + 0.1;
				}
			}
		}
		else if (key == 'j') {
			bool flag;
			Lego[Lego.size() - 1].change_z = Lego[Lego.size() - 1].change_z + 0.1;
			Lego[Lego.size() - 1].min_z = Lego[Lego.size() - 1].min_z + 0.1;
			Lego[Lego.size() - 1].max_z = Lego[Lego.size() - 1].max_z + 0.1;
			for (int i = 0; i < Lego.size() - 1; i++) { //모든 도형에 대해 체크
				flag = check_collision(Lego[Lego.size() - 1], Lego[i]);
				if (flag == false) {
					if ((Lego[Lego.size() - 1].changeangle) == 0 || (Lego[Lego.size() - 1].changeangle == 180)) {
						Lego[Lego.size() - 1].change_z = Lego[i].change_z - (box[Lego[Lego.size() - 1].lego].min_z + box[Lego[i].lego].max_z);
					}
					else if ((Lego[Lego.size() - 1].changeangle) == 90 || (Lego[Lego.size() - 1].changeangle == 270)) {
						Lego[Lego.size() - 1].change_z = Lego[i].change_z - (box[Lego[Lego.size() - 1].lego].min_x + box[Lego[i].lego].max_z);
					}
					Lego[Lego.size() - 1].min_z = Lego[Lego.size() - 1].min_z - 0.1;
					Lego[Lego.size() - 1].max_z = Lego[Lego.size() - 1].max_z - 0.1;
				}
			}
		}
		else if (key == 'k') {
			bool flag;
			Lego[Lego.size() - 1].change_x = Lego[Lego.size() - 1].change_x + 0.1;
			Lego[Lego.size() - 1].min_x = Lego[Lego.size() - 1].min_x + 0.1;
			Lego[Lego.size() - 1].max_x = Lego[Lego.size() - 1].max_x + 0.1;
			for (int i = 0; i < Lego.size() - 1; i++) { //모든 도형에 대해 체크
				flag = check_collision(Lego[Lego.size() - 1], Lego[i]);
				if (flag == false) {
					if ((Lego[Lego.size() - 1].changeangle) == 0 || (Lego[Lego.size() - 1].changeangle == 180)) {
						Lego[Lego.size() - 1].change_x = Lego[i].change_x - (box[Lego[Lego.size() - 1].lego].max_x + box[Lego[i].lego].min_x);
					}
					else if ((Lego[Lego.size() - 1].changeangle) == 90 || (Lego[Lego.size() - 1].changeangle == 270)) {
						Lego[Lego.size() - 1].change_z = Lego[i].change_z - (box[Lego[Lego.size() - 1].lego].max_x + box[Lego[i].lego].max_z);
					}
					Lego[Lego.size() - 1].min_x = Lego[Lego.size() - 1].min_x - 0.1;
					Lego[Lego.size() - 1].max_x = Lego[Lego.size() - 1].max_x - 0.1;
				}
			}
		}
		else if (key == 'i') {
			bool flag;
			Lego[Lego.size() - 1].change_x = Lego[Lego.size() - 1].change_x - 0.1;
			Lego[Lego.size() - 1].min_x = Lego[Lego.size() - 1].min_x - 0.1;
			Lego[Lego.size() - 1].max_x = Lego[Lego.size() - 1].max_x - 0.1;
			for (int i = 0; i < Lego.size() - 1; i++) { //모든 도형에 대해 체크
				flag = check_collision(Lego[Lego.size() - 1], Lego[i]);
				if (flag == false) {
					if ((Lego[Lego.size() - 1].changeangle) == 0 || (Lego[Lego.size() - 1].changeangle == 180)) {
						Lego[Lego.size() - 1].change_x = Lego[i].change_x + (box[Lego[Lego.size() - 1].lego].min_x + box[Lego[i].lego].max_x);
					}
					else if ((Lego[Lego.size() - 1].changeangle) == 90 || (Lego[Lego.size() - 1].changeangle == 270)) {
						Lego[Lego.size() - 1].change_z = Lego[i].change_z + (box[Lego[Lego.size() - 1].lego].max_x + box[Lego[i].lego].max_z);
					}
					Lego[Lego.size() - 1].min_x = Lego[Lego.size() - 1].min_x + 0.1;
					Lego[Lego.size() - 1].max_x = Lego[Lego.size() - 1].max_x + 0.1;
				}
			}
		}
		else if (key == ',') {
			bool flag;
			Lego[Lego.size() - 1].change_y = Lego[Lego.size() - 1].change_y + 0.1;
			Lego[Lego.size() - 1].min_y = Lego[Lego.size() - 1].min_y + 0.1;
			Lego[Lego.size() - 1].max_y = Lego[Lego.size() - 1].max_y + 0.1;
			for (int i = 0; i < Lego.size() - 1; i++) { //모든 도형에 대해 체크
				flag = check_collision(Lego[Lego.size() - 1], Lego[i]);
				if (flag == false) {
					Lego[Lego.size() - 1].change_y = Lego[i].change_y - (box[Lego[Lego.size() - 1].lego].max_y + box[Lego[i].lego].max_y);
					Lego[Lego.size() - 1].min_y = Lego[Lego.size() - 1].min_y - 0.1;
					Lego[Lego.size() - 1].max_y = Lego[Lego.size() - 1].max_y - 0.1;
				}
			}
		}
		else if (key == '.') {
			bool flag;
			Lego[Lego.size() - 1].change_y = Lego[Lego.size() - 1].change_y - 0.1;
			Lego[Lego.size() - 1].min_y = Lego[Lego.size() - 1].min_y - 0.1;
			Lego[Lego.size() - 1].max_y = Lego[Lego.size() - 1].max_y - 0.1;
			for (int i = 0; i < Lego.size() - 1; i++) { //모든 도형에 대해 체크
				flag = check_collision(Lego[Lego.size() - 1], Lego[i]);
				if (flag == false) {
					Lego[Lego.size() - 1].change_y = Lego[i].change_y + (box[Lego[Lego.size() - 1].lego].max_y + box[Lego[i].lego].max_y);
					Lego[Lego.size() - 1].min_y = Lego[Lego.size() - 1].min_y + 0.1;
					Lego[Lego.size() - 1].max_y = Lego[Lego.size() - 1].max_y + 0.1;
				}
			}
		}
		else if (key == '9') {
			Lego[Lego.size() - 1].changeangle = Lego[Lego.size() - 1].changeangle + 90;
		}
		else if (key == '0') {
			Lego[Lego.size() - 1].changeangle = Lego[Lego.size() - 1].changeangle - 90;
		}
		else if (key == '-') {
			thean = thean + change;
			if (thean > 2 * M_PI)
				thean -= 2 * M_PI;

			if (thean > M_PI)
			{
				xup = 0;
				yup = -1;
				zup = 0;
			}
			else if (thean <= M_PI) {
				xup = 0;
				yup = 1;
				zup = 0;
			}
			eyex = r * sin(thean)*cos(pian);
			eyey = r * sin(thean)*sin(pian);
			eyez = r * cos(thean);

		}
		else if (key == '=') {
			thean = thean - change;
			if (thean < 0)
				thean += 2 * M_PI;
			if (thean > M_PI)
			{
				xup = 0;
				yup = -1;
				zup = 0;
			}
			else if (thean <= M_PI) {
				xup = 0;
				yup = 1;
				zup = 0;
			}
			eyex = r * sin(thean)*cos(pian);
			eyey = r * sin(thean)*sin(pian);
			eyez = r * cos(thean);

		}
		else if (key == 'u') {
			if (Lego.size() > 0)
				Lego.pop_back();
		}
	}
	else if (Gamemode == 1) {
		if (key == '1') {
			pi1 = pi1 - cha1;
			eyx1 = half1 * sin(the1)*cos(pi1);
			eyy1 = half1 * sin(the1)*sin(pi1);
			eyz1 = half1 * cos(the1);
		}
		else if (key == '2') {
			pi1 = pi1 + cha1;
			eyx1 = half1 * sin(the1)*cos(pi1);
			eyy1 = half1 * sin(the1)*sin(pi1);
			eyz1 = half1 * cos(the1);
		}
		else if (key == '3') {
			the1 = the1 + cha1;
			if (the1 > 2 * M_PI)
				the1 -= 2 * M_PI;

			if (the1 > M_PI)
			{
				x_up1 = 0;
				y_up1 = -1;
				z_up1 = 0;
			}
			else if (the1 <= M_PI) {
				x_up1 = 0;
				y_up1 = 1;
				z_up1 = 0;
			}
			eyx1 = half1 * sin(the1)*cos(pi1);
			eyy1 = half1 * sin(the1)*sin(pi1);
			eyz1 = half1 * cos(the1);

		}
		else if (key == '4') {
			the1 = the1 - cha1;
			if (the1 < 0)
				the1 += 2 * M_PI;

			if (the1 > M_PI)
			{
				x_up1 = 0;
				y_up1 = -1;
				z_up1 = 0;
			}
			else if (the1 <= M_PI) {
				x_up1 = 0;
				y_up1 = 1;
				z_up1 = 0;
			}
			eyx1 = half1 * sin(the1)*cos(pi1);
			eyy1 = half1 * sin(the1)*sin(pi1);
			eyz1 = half1 * cos(the1);
		}
		else if (key == 's') {
			if (player_mode == 1) {
				situation = 1;
				for (int i = 0; i < Game1.size(); i++) {
					Game1[i].change_x = Game1[i].change_x - 1;
				}
			}
		}
		else if (key == 'w') {
			if (player_mode == 1) {
				situation = 2;
				for (int i = 0; i < Game1.size(); i++) {
					Game1[i].change_x = Game1[i].change_x + 1;
				}
			}
		}
		else if (key == 'd') {
			if (player_mode == 1) {
				move_theta = move_theta - 1;
				if (move_theta < 0)
					move_theta = move_theta + 360;
			}
		}
		else if (key == 'a') {
			if (player_mode == 1) {
				move_theta = move_theta + 1;
				if (move_theta >= 360)
					move_theta = move_theta - 360;
			}
		}
		else if (key == 'k') {
			if (player_mode == 2) {
				situation = 1;
				for (int i = 0; i < Game1.size(); i++) {
					Game2[i].change_x = Game2[i].change_x - 1;
				}
			}
		}
		else if (key == 'i') {
			if (player_mode == 2) {
				situation = 2;
				for (int i = 0; i < Game1.size(); i++) {
					Game2[i].change_x = Game2[i].change_x + 1;
				}
			}
		}
		else if (key == 'j') {
			if (player_mode == 2) {
				move_theta2 = move_theta2 + 1;
				if (move_theta2 >= 360)
					move_theta2 = move_theta2 - 360;
			}
		}
		else if (key == 'l') {
			if (player_mode == 2) {
				move_theta2 = move_theta2 - 1;
				if (move_theta2 <= 0)
					move_theta2 = move_theta2 + 360;
			}
		}
		else if (key == 'm') {
			if (map_toggle == 0)
				map_toggle = 1;
			else if (map_toggle == 1)
				map_toggle = 0;
		}
		else if (key == 'f') {
			if (player_mode == 1) {
				canon_toggle = 1;
				canon.change_x = Game1[2].change_x + Game1[2].max_x;
				canon.change_y = Game1[2].change_y;
				canon.change_z = Game1[2].change_z;
			}
			else if (player_mode == 2) {
				canon_toggle = 1;
				canon.change_x = Game2[2].change_x + Game1[2].max_x;
				canon.change_y = Game2[2].change_y;
				canon.change_z = Game2[2].change_z;
			}
		}
		else if (key == 'b') {
			if (player_mode == 1) {
				for (int i = 0; i < Game1.size(); i++) {
					if (Game1[i].lego == 9 || Game1[i].lego == 10 || Game1[i].lego == 11) {
						if (canon_count1 < 5) {
							canon.changeangle = canon.changeangle - 1;
							canon_count1 = canon_count1 + 1;
							Game1[i].changeangle = Game1[i].changeangle - 5;
						}
					}
				}
			}
		}
		else if (key == 'n') {
			if (player_mode == 1) {
				for (int i = 0; i < Game1.size(); i++) {
					if (Game1[i].lego == 9 || Game1[i].lego == 10 || Game1[i].lego == 11) {
						if (canon_count1 > -5) {
							canon.changeangle = canon.changeangle + 1;
							canon_count1 = canon_count1 - 1;
							Game1[i].changeangle = Game1[i].changeangle + 5;
						}
					}
				}
			}
		}
		else if (key == 'c') {
			if (player_mode == 2) {
				for (int i = 0; i < Game2.size(); i++) {
					if (Game2[i].lego == 9 || Game2[i].lego == 10 || Game2[i].lego == 11) {
						if (canon_count2 < 5) {
							canon.changeangle = canon.changeangle - 1;
							canon_count2 = canon_count2 + 1;
							Game2[i].changeangle = Game2[i].changeangle - 5;
						}
					}
				}
			}
		}
		else if (key == 'v') {
			if (player_mode == 2) {
				for (int i = 0; i < Game2.size(); i++) {
					if (Game2[i].lego == 9 || Game2[i].lego == 10 || Game2[i].lego == 11) {
						if (canon_count2 > -5) {
							canon.changeangle = canon.changeangle + 1;
							canon_count2 = canon_count2 - 1;
							Game2[i].changeangle = Game2[i].changeangle + 5;
						}
					}
				}
			}
		}
		glutPostRedisplay();
	}
}
void sub_menu_savetank(int option) {
	if (option == 1) {
		ofstream out("data1.txt", ios::trunc);
		if (out.is_open()) {
			for (int i = 0; i < Lego.size(); i++) {
				out << Lego[i].lego << endl;
				out << Lego[i].change_x << endl;
				out << Lego[i].change_y << endl;
				out << Lego[i].change_z << endl;
				out << Lego[i].changeangle << endl;
				out << Lego[i].lego_color_index << endl;
				out << Lego[i].text_index << endl;
				out << Lego[i].text_button << endl;
				out << Lego[i].max_x << endl;
				out << Lego[i].min_x << endl;
				out << Lego[i].max_y << endl;
				out << Lego[i].min_y << endl;
				out << Lego[i].max_z << endl;
				out << Lego[i].min_z << endl;
			}
			printf("data1 save\n");
		}
		else printf("파일이 없습니다.\n");
		out.close();
	}
	else if (option == 2) {
		ofstream out("data2.txt", ios::trunc);
		if (out.is_open()) {
			for (int i = 0; i < Lego.size(); i++) {
				out << Lego[i].lego << endl;
				out << Lego[i].change_x << endl;
				out << Lego[i].change_y << endl;
				out << Lego[i].change_z << endl;
				out << Lego[i].changeangle << endl;
				out << Lego[i].lego_color_index << endl;
				out << Lego[i].text_index << endl;
				out << Lego[i].text_button << endl;
				out << Lego[i].max_x << endl;
				out << Lego[i].min_x << endl;
				out << Lego[i].max_y << endl;
				out << Lego[i].min_y << endl;
				out << Lego[i].max_z << endl;
				out << Lego[i].min_z << endl;
			}
			printf("data2 save\n");
		}
		else printf("파일이 없습니다.\n");
		out.close();
	}
	glutPostRedisplay();
}

void sub_menu_Loadtank(int option) {
	if (option == 3) {
		fstream in("data1.txt");
		Lego.clear();
		if (in.is_open()) {
			for (int j = 0;; j++) {
				if (in.eof()) break;
				else if (j % 14 == 0)
					in >> cond.lego;
				else if (j % 14 == 1)
					in >> cond.change_x;
				else if (j % 14 == 2)
					in >> cond.change_y;
				else if (j % 14 == 3)
					in >> cond.change_z;
				else if (j % 14 == 4)
					in >> cond.changeangle;
				else if (j % 14 == 5)
					in >> cond.lego_color_index;
				else if (j % 14 == 6)
					in >> cond.text_index;
				else if (j % 14 == 7) {
					in >> cond.text_button;
				}
				else if (j % 14 == 8) {
					in >> cond.max_x;
				}
				else if (j % 14 == 9) {
					in >> cond.min_x;
				}
				else if (j % 14 == 10) {
					in >> cond.max_y;
				}
				else if (j % 14 == 11) {
					in >> cond.min_y;
				}
				else if (j % 14 == 12) {
					in >> cond.max_z;
				}
				else if (j % 14 == 13) {
					in >> cond.min_z;
					Lego.push_back(cond);
				}
			}
			printf("data1 open\n");
			draw();
		}
		else {
			printf("파일이 없습니다.\n");
		}
		in.close();
	}
	else if (option == 4) {
		fstream in("data2.txt");
		Lego.clear();
		if (in.is_open()) {
			for (int j = 0;; j++) {
				if (in.eof()) break;
				else if (j % 14 == 0)
					in >> cond.lego;
				else if (j % 14 == 1)
					in >> cond.change_x;
				else if (j % 14 == 2)
					in >> cond.change_y;
				else if (j % 14 == 3)
					in >> cond.change_z;
				else if (j % 14 == 4)
					in >> cond.changeangle;
				else if (j % 14 == 5)
					in >> cond.lego_color_index;
				else if (j % 14 == 6)
					in >> cond.text_index;
				else if (j % 14 == 7) {
					in >> cond.text_button;
				}
				else if (j % 14 == 8) {
					in >> cond.max_x;
				}
				else if (j % 14 == 9) {
					in >> cond.min_x;
				}
				else if (j % 14 == 10) {
					in >> cond.max_y;
				}
				else if (j % 14 == 11) {
					in >> cond.min_y;
				}
				else if (j % 14 == 12) {
					in >> cond.max_z;
				}
				else if (j % 14 == 13) {
					in >> cond.min_z;
					Lego.push_back(cond);
				}
			}
			printf("data2 open\n");
			draw();
		}
		else {
			printf("파일이 없습니다.\n");
		}
		in.close();
	}
	glutPostRedisplay();
}

void main_menu_function(int option) {
	printf("Main menu %d \n", option);
	if (option == 999) {
		Gamemode = 1;
		player_mode = 1;
		sub_Game_Loadtank1();
		sub_Game_Loadtank2();
		canon.lego = 12;
		canon.change_x = Game1[2].change_x + Game1[2].max_x;
		canon.change_y = Game1[2].change_y;
		canon.change_z = Game1[21].change_z;
		canon_angle = 0;

		can = (picture[canon.lego]);
		canon.changeangle = 5;
		for (int i = 0; i < Game2.size(); i++) {
			Game2[i].change_x = Game2[i].change_x - 50;
			Game2[i].change_y = Game2[i].change_y - 9;
		}
		for (int i = 0; i<Game1.size(); i++)
			Game1[i].change_y = Game1[i].change_y - 9;
		move_theta2 = 180;
		vs = 0;
	}
	else if (option == 888)
	{
		Lego.clear();
		for (int i = 0; i < Game1.size(); i++) {
			Game1[i].change_x = Game1[i].change_x - 3;
		}
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		Gamemode = 0;
	}
}
#endif // ! MAKE_LEGO_H

