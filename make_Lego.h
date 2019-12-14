#ifndef  MAKE_LEGO_H
#define  MAKE_LEGO_H

#include "bmpfuncs.h"
#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <fstream>
#include "ObjParser.h"
#include "GL/glext.h"
#define M_PI 3.14159265358979323846
using namespace std;

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
	float change_x;
	float change_y;
	float change_z;
	double changeangle;
	int lego_color_index;
	int text_index;
	int text_button;
};
struct color {
	float R;
	float G;
	float B;
};
vector<condition> Lego; condition cond; float angel1 = 0; ObjParser object; ObjParser obj;int text_index;
void setTextureMapping();
GLuint texture[6];
char picture[][50] = { "image/body2-1.obj","image/body2-2.obj","image/body2-3.obj","image/Leg1.obj","image/Leg2.obj","image/Leg3.obj","image/body1-1.obj","image/body1-2.obj","image/body1-3.obj","image/head1-1.obj","image/head1-2.obj","image/head1-3.obj" };
color paint[50] = { {1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{ 0.0f,0.0f,1.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,1.0f},{0.5f,0.5f,0.5f},{0.5f,0.0f,0.5f},{1.0f,0.0f,1.0f},{0.0f,0.5f,0.5f} };//red, green, blue, yellow, aqua, gray, purple ,fuchsia, teal;

int value = 12345678943;
void print() {
	printf("%d\n",value);
}
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
	setTextureMapping();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void idle(void) {
	angel1 = angel1 + 0.05;
	if (angel1 > 360) { angel1 -= 360; }
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

void draw_obj_with_texture(ObjParser *objParser,int text_index)
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
	glViewport(0, 50, 200, 700);
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
	glViewport(300, 0, 800, 500);
	glLoadIdentity();
	gluLookAt(eyex, eyez, eyey, 0, 0, 0, xup, yup, zup); //회전하기
	glPushMatrix();
	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	glTranslatef(3.0f, 0.0f, 0.0f);
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
			draw_obj_with_texture(&object, Lego[i].text_index);
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
	draw_preview();
	draw_text();
	draw_merge_block();
	draw_axies();
	glutSwapBuffers();
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
		eyex = r * sin(thean)*cos(pian);
		eyey = r * sin(thean)*sin(pian);
		eyez = r * cos(thean);
	}
	else if (button == 3) {
		r = r - 1;
		if (r < 5) r = 5;
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
		int c_x = 0, c_y = 0, c_z = 0, c_an = 0;
		merge_index = picture_index;
		cond.lego = merge_index;
		Lego.push_back(cond);
	}
	else if (key == 't') {
		Lego[Lego.size() - 1].text_button = 1;
		text_index = text_index + 1;
		if (text_index== 6) text_index = 0;
		Lego[Lego.size() - 1].text_index = text_index;
	}
	else if (key == 'l') {
		Lego[Lego.size() - 1].change_z = Lego[Lego.size() - 1].change_z - 0.1;
	}
	else if (key == 'j') {
		Lego[Lego.size() - 1].change_z = Lego[Lego.size() - 1].change_z + 0.1;
	}
	else if (key == 'k') {
		Lego[Lego.size() - 1].change_x = Lego[Lego.size() - 1].change_x + 0.1;
	}
	else if (key == 'i') {
		Lego[Lego.size() - 1].change_x = Lego[Lego.size() - 1].change_x - 0.1;
	}
	else if (key == ',') {
		Lego[Lego.size() - 1].change_y = Lego[Lego.size() - 1].change_y + 0.1;
	}
	else if (key == '.') {
		Lego[Lego.size() - 1].change_y = Lego[Lego.size() - 1].change_y - 0.1;
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
		if(Lego.size()>0)
			Lego.pop_back();
	}
	glutPostRedisplay();
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
				else if (j % 8 == 0)
					in >> cond.lego;
				else if (j % 8 == 1)
					in >> cond.change_x;
				else if (j % 8 == 2)
					in >> cond.change_y;
				else if (j % 8 == 3)
					in >> cond.change_z;
				else if (j % 8 == 4)
					in >> cond.changeangle;
				else if (j % 8 == 5)
					in >> cond.lego_color_index;
				else if (j % 8 == 6)
					in >> cond.text_index;
				else if (j % 8 == 7) {
					in >> cond.text_button;
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
				else if (j % 8 == 0)
					in >> cond.lego;
				else if (j % 8 == 1)
					in >> cond.change_x;
				else if (j % 8 == 2)
					in >> cond.change_y;
				else if (j % 8 == 3)
					in >> cond.change_z;
				else if (j % 8 == 4)
					in >> cond.changeangle;
				else if (j % 8 == 5)
					in >> cond.lego_color_index;
				else if (j % 8 == 6)
					in >> cond.text_index;
				else if (j % 8 == 7) {
					in >> cond.text_button;
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
}

void MakeLego_main() {
	int submenual1, submenual2, submenual3;
	init_makeLego();
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_move);
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutPostRedisplay();
	glutReshapeFunc(resize);

	submenual1 = glutCreateMenu(sub_menu_savetank);
	glutAddMenuEntry("Save Tank1", 1);
	glutAddMenuEntry("Save Tank2", 2);

	submenual2 = glutCreateMenu(sub_menu_Loadtank);
	glutAddMenuEntry("Load Tank1", 3);
	glutAddMenuEntry("Load Tank2", 4);

	submenual3 = glutCreateMenu(main_menu_function);
	glutAddSubMenu("Save Tank", submenual1);
	glutAddSubMenu("Load Tank", submenual2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

#endif // ! MAKE_LEGO_H

