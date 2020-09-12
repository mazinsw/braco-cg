#include "braco.h"
#include "util.h"
#include <GL/gl.h>

Braco::Braco()
{
	x = 0.0f;
	w = 0.2f;
	atb_angle = 0.0f;
	pun_angle = 0.0f;
	dedo1_angle = dedo2_angle = dedo3_angle = 0.0f;
}

void Braco::renderBraco()
{
	glPushMatrix();
	
	glTranslatef(0.0f, 0.5f, 0.0f);
	glScalef(0.2f, 1.0f, 0.2f);
	glColor3f(0.3f, 0.5f, 0.7f);
	drawCube();
	
	glPopMatrix();
}

void Braco::renderCotovelo()
{
	glPushMatrix();
	
	
	glPopMatrix();
}

void Braco::renderAnteBraco()
{
	glPushMatrix();
	
	glTranslatef(0.0f, -0.5f, 0.0f);
	glScalef(0.2f, 1.0f, 0.2f);
	glColor3f(0.5f, 0.7f, 0.3f);
	drawCube();
	
	glPopMatrix();
}

void Braco::renderPunho()
{
	glPushMatrix();
	
	glTranslatef(0.0f, -1.2f, 0.0f);
	glScalef(0.4, 0.4, 0.4);
	glColor3f(1.0f, 0.8f, 0.1f);
	drawCube();
	
	glPopMatrix();
}

void Braco::renderGarras()
{
	glPushMatrix();
	
	// dedo direito no centro
	glPushMatrix();
	glTranslatef(0.158f, -1.575f, 0.0f);
	glTranslatef(0.0f, 0.175f, 0.0f);
	glRotatef(dedo1_angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -0.175f, 0.0f);
	glScalef(0.05f, 0.35f, 0.05f);
	glColor3f(0.88f, 0.85f, 0.77f);
	drawCube();
	glPopMatrix();
	
	// dedo esquerdo mais ao fundo
	glPushMatrix();
	glTranslatef(-0.158f, -1.575f, -0.158f);
	glTranslatef(0.0f, 0.175f, 0.0f);
	glRotatef(dedo2_angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -0.175f, 0.0f);
	glScalef(0.05f, 0.35f, 0.05f);
	glColor3f(0.88f, 0.85f, 0.77f);
	drawCube();
	glPopMatrix();
	
	// dedo esquerdo mais à frente
	glPushMatrix();
	glTranslatef(-0.158f, -1.575f, 0.158f);
	glTranslatef(0.0f, 0.175f, 0.0f);
	glRotatef(dedo3_angle, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f, -0.175f, 0.0f);
	glScalef(0.05f, 0.35f, 0.05f);
	glColor3f(0.88f, 0.85f, 0.77f);
	drawCube();
	glPopMatrix();
	
	glPopMatrix();
}

void Braco::render()
{
	glPushMatrix();
	// move todos os objetos
	glTranslatef(x, 0.0f, 0.0f);
	renderBraco();
	renderCotovelo();
	
	glPushMatrix();
	// rotaciona somente o antebraço e o punho
	glRotatef(atb_angle, 0.0f, 0.0f, 1.0f);
	renderAnteBraco();
	
	glPushMatrix();
	// gira somente o punho
	glRotatef(pun_angle, 0.0f, 1.0f, 0.0f);
	renderPunho();
	renderGarras();

	glPopMatrix(); // punho
	glPopMatrix(); // antebraço
	glPopMatrix(); // move todos
}