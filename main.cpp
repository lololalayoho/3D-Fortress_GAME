#include "bmpfuncs.h"
#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <fstream>
#include "make_Lego.h"
#include "ObjParser.h"
using namespace std;

void cubeTextureMapping();
void Game2_draw_block();
GLfloat light_position1[] = { eyx1,eyy1,eyz1,1.0 };
GLfloat light_position2[] = { eyx1,eyy1,eyz1,1.0 };
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
	glTranslatef(0, ywidth - 10, 0);
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
	glViewport(0, 0, 600, 700);
	glLoadIdentity();
	gluLookAt(eyx1, eyz1, eyy1, 0, 0, 0, x_up1, y_up1, z_up1); //회전하기
	glRotatef(move_theta, 0, 1, 0);
	glTranslatef(0, -9, 0);
	glRotated(180, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glPushMatrix();
	for (int i = 0; i < Game1.size(); i++) {
		glPushMatrix();
		glTranslatef(Game1[i].change_x, Game1[i].change_y, Game1[i].change_z);
		glRotated(Game1[i].changeangle, 0.0, 1.0, 0.0);
		object = picture[Game1[i].lego];
		if (Game1[i].lego == 5){
			if (situation == 1)
				glRotatef(angel2, 1, 0, 0);
			else if(situation == 2)
				glRotatef(angel3, 1, 0, 0);
		}
		else if (Game1[i].lego == 3) {
			if (situation == 1)
				glRotatef(angel2, 0, 0, 1);
			else if (situation == 2)
				glRotatef(angel3, 0, 0, 1);
		}
		if (Game1[i].text_button == 0) {
			glDisable(GL_TEXTURE_2D);
			glColor4f(paint[Game1[i].lego_color_index].R, paint[Game1[i].lego_color_index].G, paint[Game1[i].lego_color_index].B, 1.0f);	 //색깔바꾸기
			draw_obj(&object);
			glEnable(GL_TEXTURE_2D);
		}
		else if (Game1[i].text_button == 1) { //object 그리기
			draw_obj_with_texture(&object, Game1[i].text_index);
		}
		draw_axies();
		glPopMatrix();
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glFlush();
	glutPostRedisplay();
}

void Game2_draw_block() {
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, 600, 700);
	glLoadIdentity();
	gluLookAt(eyx2, eyz2, eyy2, 0, 0, 0, x_up2, y_up2, z_up2); //회전하기
	glRotatef(move_theta, 0, 2, 0);
	glTranslatef(0, -9, 0);
	glRotated(180, 0.0, 1.0, 0.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position2);
	glPushMatrix();
	for (int i = 0; i < Game2.size(); i++) {
		glPushMatrix();
		glTranslatef(Game2[i].change_x, Game2[i].change_y, Game2[i].change_z);
		glRotated(Game2[i].changeangle, 0.0, 2.0, 0.0);
		object = picture[Game2[i].lego];
		if (Game2[i].lego == 5 || Game2[i].lego == 3) {
			if (situation == 2)
				glRotatef(angel2, 1, 0, 0);
			else if (situation == 2)
				glRotatef(angel3, 1, 0, 0);
		}
		if (Game2[i].text_button == 0) {
			glDisable(GL_TEXTURE_2D);
			glColor4f(paint[Game2[i].lego_color_index].R, paint[Game2[i].lego_color_index].G, paint[Game2[i].lego_color_index].B, 1.0f);	 //색깔바꾸기
			draw_obj(&object);
			glEnable(GL_TEXTURE_2D);
		}
		else if (Game2[i].text_button == 1) { //object 그리기
			draw_obj_with_texture(&object, Game2[i].text_index);
		}
		draw_axies();
		glPopMatrix();
	}
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glFlush();
	glutPostRedisplay();
}
void Game3_draw_block() {
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glViewport(600, 0, 600, 700);
	glLoadIdentity();
	gluLookAt(eyx1, eyz1, eyy1, 0, 0, 0, x_up1, y_up1, z_up1); //회전하기
	glTranslatef(0, -10, 0);
	glPushMatrix();
	for (int i = 0; i < Game1.size(); i++) {
		glPushMatrix();
		glTranslatef(Game1[i].change_x, Game1[i].change_y, Game1[i].change_z);
		glRotated(Game1[i].changeangle, 0.0, 1.0, 0.0);
		object = picture[Game1[i].lego];
		if (Game1[i].text_button == 0) {
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_LIGHTING);
			glDisable(GL_LIGHT0);
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
void Game4_draw_block() {
	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, 600, 700);
	gluLookAt(eyx2, eyz2, eyy2, 0, 0, 0, x_up2, y_up2, z_up2); //회전하기
	glTranslatef(50, -10, 0);
	for (int i = 0; i < Game2.size(); i++) {
		glPushMatrix();
		glTranslatef(Game2[i].change_x, Game2[i].change_y, Game2[i].change_z);
		glRotated(Game2[i].changeangle, 0.0, 1.0, 0.0);
		object = picture[Game2[i].lego];
		if (Game2[i].text_button == 0) {
			glDisable(GL_TEXTURE_2D);
			glColor4f(paint[Game2[i].lego_color_index].R, paint[Game2[i].lego_color_index].G, paint[Game2[i].lego_color_index].B, 1.0f);	 //색깔바꾸기
			draw_obj(&object);
			glEnable(GL_TEXTURE_2D);
		}
		else if (Game2[i].text_button == 1) { //object 그리기
			draw_obj_with_texture(&object, Game2[i].text_index);
		}
		glPopMatrix();
	}
	glEnable(GL_TEXTURE_2D);
	glFlush();
	glutPostRedisplay();
}

void Player1(){
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, 600, 700);
	glLoadIdentity();
	gluLookAt(eyx1, eyz1, eyy1, 0, 0, 0, x_up1, y_up1, z_up1);
	draw_textureCube();
	Game1_draw_block();
	draw_textureCube();
	Game4_draw_block();
	glFlush();
	glutPostRedisplay();
}

void Player2() {
	glMatrixMode(GL_MODELVIEW);
	glViewport(600, 0, 600, 700);
	glLoadIdentity();
	gluLookAt(eyx2, eyz2, eyy2, 0, 0, 0, x_up2, y_up2, z_up2);
	draw_textureCube();
	Game2_draw_block();
	draw_textureCube();
	Game3_draw_block();
	glFlush();
	glutPostRedisplay();
}

void Game_draw() {
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*
	GLfloat emission[] = { 1.0f,1.0f,1.0f,1.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	emission[0] = 0.0f;
	*/
	glPushMatrix();
	Player1();
	glPopMatrix();
	glPushMatrix();
	//Player2();
	glPopMatrix();
	glFlush();
	glutPostRedisplay();
	glPopMatrix();
}

void changeView1() {
	eyx1 = half1 * sin(the1*M_PI / 180)*cos(pi1* M_PI / 180) + Game1[Game1.size() - 1].change_x;
	eyz1 = half1 * sin(pi1*M_PI / 180) + Game1[Game1.size() - 1].change_z;
	eyy1 = half1 * sin(the1*M_PI / 180)*cos(pi1* M_PI / 180) + Game1[Game1.size() - 1].change_y;
	
	y_up1 = cos(pi1 * M_PI / 180);
	gluLookAt(eyx1, eyz1, eyy1, Game1[Game1.size() - 1].change_x , Game1[Game1.size() - 1].change_z, Game1[Game1.size() - 1].change_y, 0, y_up1, 0);
}
void changeView2() {
	eyx2 = half2 * sin(the2*M_PI / 280)*cos(pi2* M_PI / 280) + Game2[Game2.size() - 2].change_x;
	eyz2 = half2 * sin(pi2*M_PI / 280) + Game2[Game2.size() - 2].change_z;
	eyy2 = half2 * sin(the2*M_PI / 280)*cos(pi2* M_PI / 280) + Game2[Game2.size() - 2].change_y;

	y_up2 = cos(pi2 * M_PI / 280);
	gluLookAt(eyx2, eyz2, eyy2, Game2[Game2.size() - 2].change_x, Game2[Game2.size() - 2].change_z, Game2[Game2.size() - 2].change_y, 0, y_up2, 0);
}

void sub_Game_Loadtank1(){
	fstream in("data1.txt");
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
	}
	else {
		printf("파일이 없습니다.\n");
	}
	in.close();
}

void sub_Game_Loadtank2() {
	fstream in("data2.txt");
	Game2.clear();
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
				Game2.push_back(gm);
			}
		}
		printf("data2 open\n");
	}
	else {
		printf("파일이 없습니다.\n");
	}
	in.close();
}

int main(int argc, char **argv) {
	int submenual1, submenual2, submenual3;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 700);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Mini_project");

	init_makeLego();

	glutMouseFunc(mouse);
	glutMotionFunc(mouse_move);
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
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
	glutAddMenuEntry("Game Start", 999);
	glutAddMenuEntry("Make Start", 888);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutPostRedisplay();
	glutMainLoop();
	
	return 0;
}