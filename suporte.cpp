#include "suporte.h"
#include "util.h"
#include <GL/gl.h>

void Suporte::render()
{
	glPushMatrix();

	glTranslatef(0.0f, 1.1f, 0.0f);
	glScalef(4.0f, 0.2f, 0.5f);
	glColor3f(0.7f, 0.4f, 0.3);
	drawCube();

	glPopMatrix();
}

bool Suporte::outOfArea(float x, float size)
{
	return x - (size / 2) < -2.0f || x + (size / 2) > 2.0f;
}
