#include "bmpfuncs.h"
#include <iostream>
#include <GL/freeglut.h>
#
#include "ObjParser.h"
#define M_PI 3.14159265358979323846
using namespace std;


//--------------회전 위치-----------//
int xup = 0;
int yup = 1;
int zup = 0;
double change = 5 * (M_PI / 180);
double r = 10;
double pian =  50 *(M_PI / 180) ;
double thean = 50 *(M_PI / 180);
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
int picture_index,color_index,merge_index;

struct condition {
	ObjParser lego;
	float change_x;
	float change_y;
	float change_z;
	double changeangle;
	int lego_color_index;
};
struct color {
	float R;
	float G;
	float B;
};
vector<condition> Lego; condition cond; float angel1 = 0;ObjParser object;ObjParser obj;

char picture[][50] = { "body2-1.obj","body2-2.obj","body2-3.obj","Leg1.obj","Leg2.obj","Leg3.obj","body1-1.obj","body1-2.obj","body1-3.obj","head1-1.obj","head1-3.obj" };
color paint[50] = { {1.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{ 0.0f,0.0f,1.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,1.0f},{0.5f,0.5f,0.5f},{0.5f,0.0f,0.5f},{1.0f,0.0f,1.0f},{0.0f,0.5f,0.5f} };//red, green, blue, yellow, aqua, gray, purple ,fuchsia, teal;

void init(void) {
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

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 4);

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

void draw_text() {
	glViewport(0,50,200,700);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "l : GO Forward", 0, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "j : GO backward", 0, 1);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "k : GO to Left", 0, 2);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "L : Go to Right", 0, 3);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, ", : Go to Top", 0, 4);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, ". : Go to Down", 0, 5);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "u : Remove Lego", 0, 6);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "c : Change color", 0, 7);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "space bar : Choose Lego ", 0, 8);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "- : Spin to Top", 0, 9);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "= : Spin to Down", 0, 10);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "9 : Spin 90 angle for Left ", 0,11);
	glColor3f(1.0f, 1.0f, 1.0f);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "0 : Spin 90 angle for Right ", 0, 12);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glFlush();
}

void draw_preview() {
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	object = (picture[picture_index]);
	glViewport(900,400,300,300);
	glLoadIdentity();
	draw_axies();
	glColor3f(0.5f, 0.5f, 0.5f);
	gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);
	glRotatef(angel1, 0, 1, 0);
	draw_obj(&object);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glFlush();
	glutPostRedisplay();
}

void draw_merge_block() {
	glMatrixMode(GL_MODELVIEW);
	glViewport(300, 0,800, 500);
	glLoadIdentity();
	gluLookAt(eyex, eyez, eyey, 0, 0, 0, xup, yup, zup); //회전하기
	glPushMatrix();
	glRotated(camera_angle_v, 1.0, 0.0, 0.0);
	glRotated(camera_angle_h, 0.0, 1.0, 0.0);
	for (int i = 0; i < Lego.size(); i++) {
		glColor4f(paint[Lego[i].lego_color_index].R, paint[Lego[i].lego_color_index].G, paint[Lego[i].lego_color_index].B, 1.0f); //색깔바꾸기
		glTranslatef(Lego[i].change_x, Lego[i].change_y, Lego[i].change_z);
		glRotated(Lego[i].changeangle,0.0, 1.0, 0.0);
		draw_obj(&Lego[i].lego); //object 그리기
	}
	glPopMatrix();
	glFlush();
	glutPostRedisplay();
}

void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	draw_preview();
	glPopMatrix();
	glPushMatrix();
	draw_text();
	glPopMatrix();
	glPushMatrix();
	draw_merge_block();
	draw_axies();
	glPopMatrix();
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
		color_index = color_index + 1;
		if (color_index == 9) color_index = 0;
		Lego[Lego.size() - 1].lego_color_index = color_index;
	}
	else if (key == VK_SPACE) {
		merge_index = picture_index;
		obj = (picture[merge_index]);
		cond.lego = obj;
		Lego.push_back(cond);
	}
	else if (key == 'l') {
		changeflag = 1;
		Lego[Lego.size() - 1].change_z = Lego[Lego.size() - 1].change_z - 0.1;
	}
	else if (key == 'j') {
		changeflag = 1;
		Lego[Lego.size() - 1].change_z = Lego[Lego.size() - 1].change_z + 0.1;
	}
	else if (key == 'k') {
		changeflag = 1;
		Lego[Lego.size() - 1].change_x = Lego[Lego.size() - 1].change_x + 0.1;
	}
	else if (key == 'i') {
		changeflag = 1;
		Lego[Lego.size() - 1].change_x = Lego[Lego.size() - 1].change_x - 0.1;
	}
	else if (key == ',') {
		changeflag = 1;
		Lego[Lego.size() - 1].change_y = Lego[Lego.size() - 1].change_y + 0.1;
	}
	else if (key == '.') {
		changeflag = 1;
		Lego[Lego.size() - 1].change_y = Lego[Lego.size() - 1].change_y - 0.1;
	}
	else if (key == '9') {
		changeflag = 1;
		Lego[Lego.size() - 1].changeangle = Lego[Lego.size() - 1].changeangle + 90;
	}
	else if (key == '0') {
		changeflag = 1;
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
		Lego.pop_back();
	}
	glutPostRedisplay();
}

void main_menu_function(int option) {
	printf("Main menu %d \n", option);
}


int main(int argc, char **argv) {

	int submenual;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 700);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Mini_project");

	init();
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_move);
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutPostRedisplay();
	glutReshapeFunc(resize);

	glutCreateMenu(main_menu_function);
	glutAddMenuEntry("Save Tank", 1);
	glutAddMenuEntry("Load Tank", 2);
	glutAddMenuEntry("Go to Game Mode", 3);
	glutAddMenuEntry("Quit",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}