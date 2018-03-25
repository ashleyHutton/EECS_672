// Table.h

#ifndef Table_H
#define Table_H

#include "SceneElement.h"
#include "ShaderIF.h"

class Table : public SceneElement
{
public:
	Table(ShaderIF* sIF, PhongMaterial& matl, float topHeight, float legHeight, float topRadius, 
		float cx, float cy);
	virtual ~Table();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:

	float m_radius; float m_height; float m_cx; float m_cy;

	GLuint vao[6]; // 0: top, 1: leg #1, 2: leg #2, 3: leg #3, 4: leg #4, 5: table top
	GLuint vboTop[1];
	GLuint vboTableTop[1];
	GLuint vboLeg1[1];
	GLuint vboLeg2[1];
	GLuint vboLeg3[1];
	GLuint vboLeg4[1];
	GLuint ebo[3];

	static GLuint indexList[3][4];

	void defineLeg1(float h, float r, float cx, float cy);
	void defineLeg2(float h, float r, float cx, float cy);
	void defineLeg3(float h, float r, float cx, float cy);
	void defineLeg4(float h, float r, float cx, float cy);
	void defineTableTop();
	void defineTop(float cx, float cy, float cz, float r, float h);

	void renderLegs();
	void renderTableTop();
	void renderTop();
};

#endif
