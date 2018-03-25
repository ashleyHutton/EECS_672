// Lamp.c++

#include "Lamp.h"

#include <math.h>

GLuint Lamp::indexList[3][4] = {
	{ 6, 7, 0, 1 }, // xmin face
	{ 6, 0, 4, 2 }, // ymin face
	{ 1, 7, 3, 5 }  // ymax face
};

typedef float vec3[3];

Lamp::Lamp(ShaderIF* sIF, float topHeight, float legHeight, float topRadius, float zmin,
	float cx, float cy, float R, float G, float B) : shaderIF(sIF)
{
	kd[0] = R; kd[1] = G; kd[2] = B;
	ka[0] = R; ka[1] = G; ka[2] = B;
	la[0] = 0.15; la[1] = 0.15; la[2] = 0.15;

	m_radius = topRadius;
	m_height = legHeight;
	m_cx = cx; m_cy = cy;
	m_zmin = zmin;

	glGenVertexArrays(3, vao);

	defineLeg(legHeight, topRadius, cx, cy);
	defineBase(cx, cy, topRadius);
	defineTop(cx, cy, legHeight, topRadius, topHeight);
}

Lamp::~Lamp()
{
	glDeleteBuffers(3, ebo);
	glDeleteBuffers(1, vboTop);
	glDeleteBuffers(1, vboLeg);
	glDeleteBuffers(1, vboBase);
	glDeleteVertexArrays(3, vao);
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

// cylinder creation borrowed and adapted from defineCylinder() of MandM Cylinder class
const int N_POINTS_AROUND_SLICE = 18; // number points around a cross-section 
void Lamp::defineTop(float cx, float cy, float cz, float r, float h){

	int nPoints = 2 * (N_POINTS_AROUND_SLICE + 1);
	vec3* coords = new vec3[nPoints];
	vec3* normals = new vec3[nPoints];
	double theta = 0.0;
	double dTheta = 2.0 * M_PI / N_POINTS_AROUND_SLICE;

	for (int i=0; i<=N_POINTS_AROUND_SLICE; i++){

		int j = 2 * i;
		double dx = cos(theta);
		double dy = sin(theta);

		normals[j][0] = dx; normals[j][1] = dy; normals[j][2] = 0.0;
		coords[j][0] = cx + r*dx; coords[j][1] = cy + r*dy; coords[j][2] = cz - (h / 2);
		normals[j+1][0] = dx; normals[j+1][1] = dy; normals[j+1][2] = 0.0;
		coords[j+1][0] = cx + r*dx; coords[j+1][1] = cy + r*dy; coords[j+1][2] = cz + (h / 2);

		theta += dTheta;
	}

	glBindVertexArray(vao[0]);
	glGenBuffers(1, vboTop);
	glBindBuffer(GL_ARRAY_BUFFER, vboTop[0]);
	glBufferData(GL_ARRAY_BUFFER, nPoints*sizeof(vec3), coords, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	delete[] coords;
	delete[] normals;
}

void Lamp::renderTop(){

	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2*(N_POINTS_AROUND_SLICE+1));

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
	// 1. Save current and establish new current shader program
	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	glUseProgram(shaderIF->getShaderPgmID());

	// 2. Establish "mc_ec" and "ec_lds" matrices
	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float mat[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(mat));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, ec_lds.extractColMajor(mat));

	// 3. Set GLSL's "kd" variable using this object's "kd" instance variable
	glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
	glUniform3fv(shaderIF->ppuLoc("ka"), 1, ka);
	glUniform3fv(shaderIF->ppuLoc("la"), 1, la);

	glGenBuffers(3, ebo);
	for (int i=0 ; i<3 ; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexList[i], GL_STATIC_DRAW);
	}

	// 4. Establish any other attributes and make one or more calls to
	//    glDrawArrays and/or glDrawElements
	renderPiece(1); // leg
	renderPiece(2); // base
	renderTop();

	// 5. Reestablish previous shader program
	glUseProgram(program);
}
