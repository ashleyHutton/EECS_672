// Lamp.h

#ifndef Lamp_H
#define Lamp_H

#include "ModelView.h"
#include "ShaderIF.h"

class Lamp : public ModelView
{
public:
	Lamp(ShaderIF* sIF, float topHeight, float legHeight, float topRadius, float zmin,
		float cx, float cy, float R, float G, float B);
	virtual ~Lamp();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	ShaderIF* shaderIF;
	float kd[3];
	float ka[3];
	float la[3];

	float m_radius; float m_height; float m_cx; float m_cy; float m_zmin;

	GLuint vao[5]; // 0: top, 1: leg, 2: base
	GLuint vboTop[1];
	GLuint vboLeg[1];
	GLuint vboBase[1];
	GLuint ebo[3];

	static GLuint indexList[3][4];

	void defineLeg(float h, float r, float cx, float cy);
	void defineTop(float cx, float cy, float cz, float r, float h);
	void defineBase(float cx, float cy, float r);

	void renderPiece(int vao_index);
	void renderTop();
};

#endif
