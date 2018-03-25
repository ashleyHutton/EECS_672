// Lamp.h

#ifndef Lamp_H
#define Lamp_H

#include "SceneElement.h"
#include "ShaderIF.h"
#include "BasicShapeRenderer.h"


class Lamp : public SceneElement
{
public:
	Lamp(ShaderIF* sIF, PhongMaterial& matl, float topHeight, float legHeight, float topRadius, float zmin,
		float cx, float cy);
	virtual ~Lamp();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:

	float m_radius; float m_height; float m_cx; float m_cy; float m_zmin;

	GLuint vao[5]; // 0: top, 1: leg, 2: base
	GLuint vboLeg[1];
	GLuint vboBase[1];
	GLuint ebo[3];

	BasicShape* piece;
	BasicShapeRenderer* pieceR;

	static GLuint indexList[3][4];

	void defineLeg(float h, float r, float cx, float cy);
	void defineTop(float cx, float cy, float cz, float r, float h);
	void defineBase(float cx, float cy, float r);

	void renderPiece(int vao_index);
};

#endif
