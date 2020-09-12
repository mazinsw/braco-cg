#ifndef _BRACO_H_
#define _BRACO_H_
#define MAX_ANTE_ANGLE 115.0f

class Braco
{
private:
	float x;
	float w;
	float atb_angle;
	float pun_angle;
	float dedo1_angle;
	float dedo2_angle;
	float dedo3_angle;
	void renderBraco();
	void renderCotovelo();
	void renderAnteBraco();
	void renderPunho();
	void renderGarras();
protected:

public:
	Braco();
	void render();

	inline float getWidth()
	{
		return w;
	}
	
	inline float getX()
	{
		return x;
	}

	inline void setX(float x)
	{
		this->x = x;
	}
	
	/**
	 * Obtem o ângulo de rotação do antebraço
	 * 
	 */
	inline float getAnteAngle()
	{
		return atb_angle;
	}

	/**
	 * Atualiza o ângulo de rotação do antebraço
	 */
	inline void setAnteAngle(float angle)
	{
		if(angle < -MAX_ANTE_ANGLE || angle > MAX_ANTE_ANGLE)
			return;
		this->atb_angle = angle;
	}
	
	/**
	 * Obtem o ângulo de rotação do punho
	 * 
	 */
	inline float getPunhoAngle()
	{
		return pun_angle;
	}

	/**
	 * Atualiza o ângulo de rotação do punho
	 */
	inline void setPunhoAngle(float angle)
	{
		this->pun_angle = angle;
	}
	
	/**
	 * Atualiza o ângulo de rotação do dedo
	 * 
	 * parâmetros
	 *   angle: ângulo para rotacionar o dedo
	 *   dedo: informa qual dedo será rotacionado
	 *     1 para o dedo direito no centro
	 *     2 para o dedo esquerdo mais ao fundo
	 *     3 para o dedo esquerdo mais à frente
	 */
	inline void setDedoAngle(float angle, int dedo)
	{
		if(angle < -90.0f || angle > 90.0f)
			return;
		switch(dedo)
		{
		case 1:
			this->dedo1_angle = angle;
			break;
		case 2:
			this->dedo2_angle = angle;
			break;
		case 3:
			this->dedo3_angle = angle;
			break;
		default:
			// raise exception?
			break;
		}
	}
	
	/**
	 * Junta os dedos ou afasta dependendo do fator de aproximação
	 * 
	 * parâmetros
	 *   fator: fator de aproximação do dedos, fator negativo aproxima e 
	 *     positivo afasta
	 */
	inline void juntarDedos(float fator)
	{
		setDedoAngle(getDedoAngle(1) - fator, 1);
		setDedoAngle(getDedoAngle(2) + fator, 2);
		setDedoAngle(getDedoAngle(3) + fator, 3);
	}
	
	/**
	 * Obtem o ângulo de rotação do dedo informado pelo parâmetro
	 * 
	 * parâmetros
	 *   dedo: informa qual de dedo será obtido o ângulo
	 *     1 para o dedo direito no centro
	 *     2 para o dedo esquerdo mais ao fundo
	 *     3 para o dedo esquerdo mais à frente
	 */
	inline float getDedoAngle(int dedo)
	{
		switch(dedo)
		{
		case 1:
			return dedo1_angle;
		case 2:
			return dedo2_angle;
		case 3:
			return dedo3_angle;
		default:
			// raise exception?
			return 0.0f;
		}
	}
};

#endif /* _BRACO_H_ */
