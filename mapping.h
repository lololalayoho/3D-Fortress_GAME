#pragma once
#include "bmpfuncs.h"
#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <fstream>
#include "GL/glext.h"
#include "ObjParser.h"
using namespace std;

GLuint texBackground[6]; GLuint g_mCubeTex;
void skyboxMapping() {
	glGenTextures(1, &g_mCubeTex);
	int width, height, channels;
	uchar * img0 = readImageData("Tex/organic_rt.bmp", &width, &height, &channels);
	uchar * img1 = readImageData("Tex/organic_lf.bmp", &width, &height, &channels);
	uchar * img2 = readImageData("Tex/organic_up.bmp", &width, &height, &channels);
	uchar * img3 = readImageData("Tex/organic_dn.bmp", &width, &height, &channels);
	uchar * img4 = readImageData("Tex/organic_ft.bmp", &width, &height, &channels);
	uchar * img5 = readImageData("Tex/organic_bk.bmp", &width, &height, &channels);

	glBindTexture(GL_TEXTURE_CUBE_MAP, g_mCubeTex);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img4);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img5);

	glBindTexture(GL_TEXTURE_CUBE_MAP, g_mCubeTex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);
}

void draw_skybox() {

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_mCubeTex);
	float g_nskysize = 300.0f;

	glBegin(GL_QUADS);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nskysize, g_nskysize, -g_nskysize);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nskysize, g_nskysize, g_nskysize);

	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nskysize, g_nskysize, -g_nskysize);

	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nskysize, -g_nskysize, g_nskysize);

	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nskysize, g_nskysize, -g_nskysize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nskysize, g_nskysize, -g_nskysize);

	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nskysize, -g_nskysize, g_nskysize);

	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nskysize, g_nskysize, -g_nskysize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nskysize, g_nskysize, -g_nskysize);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nskysize, -g_nskysize, -g_nskysize);

	glEnd();

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
	float xwidth = 100.0f; float ywidth = 100.0f; float zwidth = 100.0f;
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

