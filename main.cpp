#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include "classes/glwindow.h"
#include "suporte.h"
#include "braco.h"
#include "util.h"
#include "keyaction.h"

class RenderWindow: public GLWindowBase
{
private:
	Suporte suporte;
	Braco braco;
	KeyAction actionBarra;
	KeyAction actionBarraO;
	KeyAction actionAnte;
	KeyAction actionPunho;
	KeyAction actionDedo1;
	KeyAction actionDedo2;
	KeyAction actionDedo3;
	KeyAction actionDedos;
	float x_vel;
	float atb_vel;
	float pun_vel;
	float dedo_vel;
	float ax, ay, az;
protected:
	bool onInit(int argc, char** argv)
	{
		// qualidade do anti serrilhado
#ifdef _WIN32
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
#endif
		return GLWindowBase::onInit(argc, argv);
	}
	
	virtual void getWindowInfo(int& width, int& height, int& bpp, bool& fullscreen, bool& resizable)
	{
		GLWindowBase::getWindowInfo(width, height, bpp, fullscreen, resizable);
		resizable = false;
	}
	
	virtual void onResize(int newWidth, int newHeight)
	{
		onCreate();
	}
	
	/**
	 * desenha no plano 3D
	 */
	virtual void onCreate()
	{
		GLfloat col[] = {0.2f, 0.2f, 0.2f, 1.0f};
		GLfloat pos[] = { -4.0f, 0.0f, 4.0f, 1.0f};

		resize3DScene();

		glClearColor( 0.5f, 0.5f, 0.5f, 0.0f );
		// Habilita teste de profundidade
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		// Habilita luz
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		// Habilita cor nor objetos
		glEnable(GL_COLOR_MATERIAL);
		glClearDepth(1.0f);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
		
		//Add ambient light
	    GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color(0.2, 0.2, 0.2)
	    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
		// move todos os desenhos para o fundo
		glTranslatef(0.0f, 0.0f, -5.0f);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
	}

	/**
	 * trata os eventos do teclado
	 */
	virtual void onKeyDown(int key, int state)
	{
		actionBarra.update(key, true);
		actionBarraO.update(translateKey(key, state), true);
		actionAnte.update(translateKey(key, state), true);
		actionPunho.update(translateKey(key, state), true);
		actionDedo1.update(translateKey(key, state), true);
		actionDedo2.update(translateKey(key, state), true);
		actionDedo3.update(translateKey(key, state), true);
		actionDedos.update(translateKey(key, state), true);
		switch(key)
		{
		case '0':
		case SDLK_KP0:
			ay = 30.0f;
			ax = az = 0.0f;
			break;
		case '5':
		case SDLK_KP5:
			ax = ay = az = 0.0f;
			break;
		case '4':
		case SDLK_KP4:
			ay = 90.0f;
			ax = az = 0.0f;
			break;
		case '2':
		case SDLK_KP2:
			ax = -90.0f;
			ay = az = 0.0f;
			break;
		case '6':
		case SDLK_KP6:
			ay = -90.0f;
			ax = az = 0.0f;
			break;
		case '8':
		case SDLK_KP8:
			ax = 90.0f;
			ay = az = 0.0f;
			break;
		default:
			break;
		}
		GLWindowBase::onKeyDown(key, state);
	}


	/**
	 * trata os eventos do teclado
	 */
	virtual void onKeyUp(int key, int state)
	{
		actionBarra.update(key, false);
		actionBarraO.update(translateKey(key, state), false);
		actionAnte.update(translateKey(key, state), false);
		actionPunho.update(translateKey(key, state), false);
		actionDedo1.update(translateKey(key, state), false);
		actionDedo2.update(translateKey(key, state), false);
		actionDedo3.update(translateKey(key, state), false);
		actionDedos.update(translateKey(key, state), false);
		GLWindowBase::onKeyUp(key, state);
	}

	/**
	 * desenha o braço e o suporte
	 */
	virtual void render()
	{
		// limpa o buffer
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glPushMatrix();

		// visualiza em um âlgulo especial
		glRotatef(ax, 1.0f, 0.0f, 0.0f);
		glRotatef(ay, 0.0f, 1.0f, 0.0f);
		glRotatef(az, 0.0f, 0.0f, 1.0f);
		//drawAxis();
		suporte.render();
		braco.render();

		glPopMatrix();
		// mostra os desenhos
		swapBuffers();

		// atualiza os movimentos
		updateAction();
	}
	
	/**
	 * Atualiza os ângulos e posições
	 */
	inline void updateAction()
	{
		if(actionBarra.inAction())
		{
			if(!suporte.outOfArea(braco.getX() + actionBarra.getSide() * x_vel, braco.getWidth()))
				braco.setX(braco.getX()  + actionBarra.getSide() * x_vel);
		}
		else if(actionBarraO.inAction())
		{
			if(!suporte.outOfArea(braco.getX() + actionBarraO.getSide() * x_vel, braco.getWidth()))
				braco.setX(braco.getX()  + actionBarraO.getSide() * x_vel);
		}
		if(actionAnte.inAction())
			braco.setAnteAngle(braco.getAnteAngle() + actionAnte.getSide() * atb_vel);
		if(actionPunho.inAction())
			braco.setPunhoAngle(braco.getPunhoAngle() + actionPunho.getSide() * atb_vel);
		// rotação dos dedos
		if(actionDedos.inAction())
		{
			braco.juntarDedos( actionDedos.getSide() * dedo_vel);
		}
		else
		{
			if(actionDedo1.inAction())
				braco.setDedoAngle(braco.getDedoAngle(1)  - actionDedo1.getSide() * dedo_vel, 1);
			if(actionDedo2.inAction())
				braco.setDedoAngle(braco.getDedoAngle(2)  + actionDedo2.getSide() * dedo_vel, 2);
			if(actionDedo3.inAction())
				braco.setDedoAngle(braco.getDedoAngle(3)  + actionDedo3.getSide() * dedo_vel, 3);
		}
	}

public:
	RenderWindow()
	{
		actionBarra.setKeys(SDLK_LEFT, SDLK_RIGHT);
		actionBarraO.setKeys('O', 'o');
		actionAnte.setKeys('c', 'C');
		actionPunho.setKeys('P', 'p');
		actionDedo1.setKeys('L', 'l');
		actionDedo3.setKeys('M', 'm');
		actionDedo2.setKeys('I', 'i');
		actionDedos.setKeys('U', 'u');
		x_vel = 0.02f;
		atb_vel = 1.0f;
		pun_vel = 1.0f;
		dedo_vel = 1.0f;
		ax = az = 0.0f;
		ay = 30.0f;
	}
	~RenderWindow() {}
};

int main(int argc, char *argv[])
{
	RenderWindow lp;

	lp.setTitle("Braco");
	return lp.start(argc, argv);
}

