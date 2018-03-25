// Lamp.c++

#include "Lamp.h"

#include <math.h>

GLuint Lamp::indexList[3][4] = {
	{ 6, 7, 0, 1 }, // xmin face
	{ 6, 0, 4, 2 }, // ymin face
	{ 1, 7, 3, 5 }  // ymax face
};

typedef float vec3[3];

Lamp::Lamp(ShaderIF* sIF, PhongMaterial& matl, float topHeight, float legHeight, float topRadius, float zmin,
	float cx, float cy) : SceneElement(sIF, matl)
{
	m_radius = topRadius;
	m_height = legHeight;
	m_cx = cx; m_cy = cy;
	m_zmin = zmin;

	glGenVertexArrays(3, vao);

	defineLeg(legHeight, topRadius, cx, cy);
	defineBase(cx, cy, topRadius);
	defineTop(cx, cy, legHeight, topRadius, topHeight);

	if (piece == nullptr) pieceR = nullptr;
	else pieceR = new BasicShapeRenderer(sIF, piece);

}

Lamp::~Lamp()
{
	glDeleteBuffers(3, ebo);
	glDeleteBuffers(1, vboLeg);
	glDeleteBuffers(1, vboBase);
	glDeleteVertexArrays(3, vao);

	if (piece != nullptr) delete piece;
	if (pieceR != nullptr) delete pieceR;
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Lamp::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = m_cx - m_radius; 	// xmin  
	xyzLimits[1] = m_cx + m_radius; 	// xmax        
	xyzLimits[2] = m_cy - m_radius; 	// ymin        
	xyzLimits[3] = m_cy + m_radius; 	// ymax        
	xyzLimits[4] = m_zmin; 				// zmin        
	xyzLimits[5] = m_zmin + m_height; 	// zmax       
}

void Lamp::defineLeg(float h, float r, float cx, float cy){

	float xmin, xmax, ymin, ymax;
	float w = r / 3; // leg width = radius / 3
	float zmin = m_zmin; 
	float zmax = h;

	xmin = cx - (w / 2); xmax = cx + (w / 2);
	ymin = cy - (w / 2); ymax = cy + (w / 2);

	vec3 leg[] = {
		{xmin ,ymin, zmax}, {xmin, ymax, zmax},
		{xmax, ymin, zmax}, {xmax, ymax, zmax},
		{xmax, ymin, zmin}, {xmax, ymax, zmin},
		{xmin, ymin, zmin}, {xmin, ymax, zmin}
	};

	glBindVertexArray(vao[1]);
	glGenBuffers(1, vboLeg);
	glBindBuffer(GL_ARRAY_BUFFER, vboLeg[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), leg, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));
}

void Lamp::defineBase(float cx, float cy, float r){

	float xmin, xmax, ymin, ymax;
	float zmin = m_zmin; 
	float zmax = m_zmin + 0.05;

	xmin = cx - (r / 2); xmax = cx + (r / 2);
	ymin = cy - (r / 2); ymax = cy + (r / 2);

	vec3 Base[] = {
		{xmin ,ymin, zmax}, {xmin, ymax, zmax},
		{xmax, ymin, zmax}, {xmax, ymax, zmax},
		{xmax, ymin, zmin}, {xmax, ymax, zmin},
		{xmin, ymin, zmin}, {xmin, ymax, zmin}
	};

	glBindVertexArray(vao[2]);
	glGenBuffers(1, vboBase);
	glBindBuffer(GL_ARRAY_BUFFER, vboBase[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), Base, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));
}

void Lamp::defineTop(float cx, float cy, float cz, float r, float h){

	cryph::AffPoint bottom(cx, cy, cz);
	cryph::AffVector u(0.0, 0.0, 1.0);

	piece = BasicShape::makeBoundedCylinder(bottom, bottom + (h * u), r, 20, 2, BasicShape::CAP_AT_NEITHER);

}

void Lamp::renderPiece(int vao_index){

	glBindVertexArray(vao[vao_index]);

	// The three faces that can be drawn with glDrawArrays
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 0.0, 1.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 1.0, 0.0, 0.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 2, 4);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 0.0, -1.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

	// The three faces that are drawn with glDrawElements
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), -1.0, 0.0, 0.0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, -1.0, 0.0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 1.0, 0.0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[2]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
}

void Lamp::render()
{
	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	glUseProgram(shaderIF->getShaderPgmID());

	establishLightingEnvironment();
	establishView();
	establishMaterial();

	glGenBuffers(3, ebo);
	for (int i=0 ; i<3 ; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexList[i], GL_STATIC_DRAW);
	}

	renderPiece(1); // leg
	renderPiece(2); // base

	if (pieceR != nullptr)
		pieceR->drawShape();

	glUseProgram(program);
}
