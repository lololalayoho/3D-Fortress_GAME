#include "bmpfuncs.h"
#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include <stdlib.h>Fc
#include <fstream>
#include "make_Lego.h"
#include "ObjParser.h"
using namespace std;

GLfloat light_position1[] = { eyx1,eyy1,eyz1,1.0 };
GLfloat light_position2[] = { eyx2,eyy2,eyz1,1.0 };
void canon_check();
void Game1_draw_block() {
	glDisable(GL_TEXTURE_2D);
	glViewport(0, 0, 1200, 700);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glPushMatrix();
	for (int i = 0; i < Game1.size(); i++) {
		glPushMatrix();
		glTranslatef(Game1[i].change_x, Game1[i].change_y, Game1[i].change_z);
		if (Game1[i].lego == 9 || Game1[i].lego == 10 || Game1[i].lego == 11) {
			glRotated(Game1[i].changeangle, 0.0, 0.0, 1.0);
		}
		else {
			glRotated(Game1[i].changeangle, 0.0, 1.0, 0.0);
		}
		object = picture[Game1[i].lego];
		if (Game1[i].lego == 5) {
			if (situation == 1)
				glRotatef(angel2, 1, 0, 0);
			else if (situation == 2)
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
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glFlush();
	glutPostRedisplay();
	
}
void Game2_draw_block(){
	glDisable(GL_TEXTURE_2D);
	glViewport(0, 0, 1200, 700);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glPushMatrix();
	for (int i = 0; i < Game2.size(); i++) {
		glPushMatrix();
		glTranslatef(Game2[i].change_x, Game2[i].change_y, Game2[i].change_z);
		if (Game2[i].lego == 9 || Game2[i].lego == 10 || Game2[i].lego == 11) {
			glRotated(Game2[i].changeangle, 0.0, 0.0, 1.0);
		}
		else {
			glRotated(Game2[i].changeangle, 0.0, 1.0, 0.0);
		}
		object = picture[Game2[i].lego];
		if (Game2[i].lego == 5) {
			if (situation == 1)
				glRotatef(angel2, 1, 0, 0);
			else if (situation == 2)
				glRotatef(angel3, 1, 0, 0);
		}
		else if (Game2[i].lego == 3) {
			if (situation == 1)
				glRotatef(angel2, 0, 0, 1);
			else if (situation == 2)
				glRotatef(angel3, 0, 0, 1);
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
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glFlush();
	glutPostRedisplay();
}
void draw_canon1() {
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	if (canon_toggle == 1) {
		glColor3f(0.5f, 0.5f, 0.5f);
		if (canon_angle >= 0 && canon_angle < 45) {
			canon1.change_x = canon1.change_x + canon1.changeangle*0.08 + 0.15;
			canon1.change_y = canon1.change_y + canon1.changeangle * 0.1;
				glRotatef(move_theta, 0, 1, 0);
			glTranslatef(canon1.change_x, canon1.change_y, canon1.change_z);
			draw_obj(&can1);
			canon_check();
		}
		else if (canon_angle >= 45 && canon_angle < 60) {
			canon1.change_x = canon1.change_x + canon1.changeangle*0.08 + 0.15;
			canon1.change_y = canon1.change_y + canon1.changeangle * 0.05;
				glRotatef(move_theta, 0, 1, 0);
			glTranslatef(canon1.change_x, canon1.change_y, canon1.change_z);
			draw_obj(&can1);
			canon_check();
		}
		else if (canon_angle >= 60 && canon_angle < 90) {
			canon1.change_x = canon1.change_x + canon1.changeangle*0.08 + 0.15;
			canon1.change_y = canon1.change_y + canon1.change_y*0.0025;
			if (canon1.change_y < -9)canon1.change_y = -9;
				glRotatef(move_theta, 0, 1, 0);
			glTranslatef(canon1.change_x, canon1.change_y, canon1.change_z);
			draw_obj(&can1);
			canon_check();
		}
		else if (canon_angle >= 90 && canon_angle < 135) {
			canon1.change_x = canon1.change_x + canon1.changeangle*0.08 + 0.15;
			canon1.change_y = canon1.change_y - canon1.changeangle*0.05;
			if (canon1.change_y < -9)canon1.change_y = -9;
				glRotatef(move_theta, 0, 1, 0);
			glTranslatef(canon1.change_x, canon1.change_y, canon1.change_z);
			draw_obj(&can1);
			canon_check();
		}
		else if (canon_angle >= 135 && canon_angle < 180) {
			canon1.change_x = canon1.change_x + canon1.changeangle*0.08 + 0.15;
			canon1.change_y = canon1.change_y - canon1.changeangle * 0.1;
			if (canon1.change_y < -9)canon1.change_y = -9;
				glRotatef(move_theta, 0, 1, 0);
			glTranslatef(canon1.change_x, canon1.change_y, canon1.change_z);
			draw_obj(&can1);
			canon_check();
		}
	}
}
void draw_canon2() {
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	//PlaySound(TEXT("sound/Fire1-1.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
	if (canon_toggle == 1) {
		glColor3f(0.5f, 0.5f, 0.5f);
		if (canon_angle >= 0 && canon_angle < 45) {
			canon2.change_x = canon2.change_x + canon2.changeangle*0.08 + 0.15;
			canon2.change_y = canon2.change_y + canon2.changeangle * 0.1;
			if (player_mode == 2)
				glRotatef(move_theta2, 0, 1, 0);
			glTranslatef(canon2.change_x, canon2.change_y, canon2.change_z);
			draw_obj(&can1);
			canon_check();
		}
		else if (canon_angle >= 45 && canon_angle < 60) {
			canon2.change_x = canon2.change_x + canon2.changeangle*0.08 + 0.15;
			canon2.change_y = canon2.change_y + canon2.changeangle * 0.05;
			if (player_mode == 2)
				glRotatef(move_theta2, 0, 1, 0);
			glTranslatef(canon2.change_x, canon2.change_y, canon2.change_z);
			draw_obj(&can1);
			canon_check();
		}
		else if (canon_angle >= 60 && canon_angle < 90) {
			canon2.change_x = canon2.change_x + canon2.changeangle*0.08 + 0.15;
			canon2.change_y = canon2.change_y + canon2.change_y*0.0025;
			if (canon2.change_y < -9)canon2.change_y = -9;
			else if (player_mode == 2)
				glRotatef(move_theta2, 0, 1, 0);
			glTranslatef(canon2.change_x, canon2.change_y, canon2.change_z);
			draw_obj(&can1);
			canon_check();
		}
		else if (canon_angle >= 90 && canon_angle < 135) {
			canon2.change_x = canon2.change_x + canon2.changeangle*0.08 + 0.15;
			canon2.change_y = canon2.change_y - canon2.changeangle*0.05;
			if (canon2.change_y < -9)canon2.change_y = -9;
			if (player_mode == 2)
				glRotatef(move_theta2, 0, 1, 0);
			glTranslatef(canon2.change_x, canon2.change_y, canon2.change_z);
			draw_obj(&can1);
			canon_check();
		}
		else if (canon_angle >= 135 && canon_angle < 180) {
			canon2.change_x = canon2.change_x + canon2.changeangle*0.08 + 0.15;
			canon2.change_y = canon2.change_y - canon2.changeangle * 0.1;
			if (canon2.change_y < -9)canon2.change_y = -9;
			if (player_mode == 2)
				glRotatef(move_theta2, 0, 1, 0);
			glTranslatef(canon2.change_x, canon2.change_y, canon2.change_z);
			draw_obj(&can1);
			canon_check();
		}
	}
}
void canon_check() {
	if (player_mode == 2) {
		for (int i = 0; i < Game1.size(); i++) {
			if ((int)Game1[i].change_x + 1 >= (int)canon2.change_x && (int)Game1[i].change_x - 1 <= (int)canon2.change_x) {
				if ((int)Game1[i].change_y + 2 >= (int)canon2.change_y && (int)Game1[i].change_y - 2 <= (int)canon2.change_y)
					vs = 1;
			}
		}
	}
	else if (player_mode == 1) {
		for (int i = 0; i < Game2.size(); i++) {
			if ((int)Game2[i].change_x*(-1) + 1 >= (int)canon1.change_x && (int)Game2[i].change_x*(-1) - 1 <= (int)canon1.change_x) {
				if ((int)Game2[i].change_y + 2 >= (int)canon1.change_y && (int)Game2[i].change_y - 2 <= (int)canon1.change_y)
					vs = 2;
			}
		}
	}
}

void Game_draw() {
	glViewport(0, 0, 1200, 700);
	glLoadIdentity();
	if (player_mode == 1) {
		gluLookAt(Game1[0].change_x - 20, Game1[0].change_y + 5, Game1[0].change_z, Game1[0].change_x, Game1[0].change_y, Game1[0].change_z, 0, y_up1, 0);
	}
	else if (player_mode == 2) {
		gluLookAt(Game2[0].change_x -20, Game2[0].change_y + 5, Game2[0].change_z, Game2[0].change_x, Game2[0].change_y, Game2[0].change_z, 0, y_up2, 0);
	}
	if (player_mode == 1)
		glRotatef(-move_theta, 0, 1, 0);
	else if (player_mode == 2)
		glRotatef(-move_theta2, 0, 1, 0);
	if (map_toggle == 0) {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		draw_skybox();
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_CUBE_MAP);
		glPopMatrix();
	}
	else if (map_toggle == 1) {
		glPushMatrix();
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		glDisable(GL_TEXTURE_GEN_R);
		glDisable(GL_TEXTURE_CUBE_MAP);
		glEnable(GL_TEXTURE_2D);
		draw_textureCube();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glPushMatrix();
	glRotatef(move_theta, 0, 1, 0);
	Game1_draw_block();
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glPopMatrix();
	glPushMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glRotatef(move_theta2, 0, 1, 0);
	Game2_draw_block();
	glPopMatrix();
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glFlush();
	glutPostRedisplay();
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
void sub_Game_Loadtank1() {
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
