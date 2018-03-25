// Table.c++

#include "Table.h"

#include <math.h>

GLuint Table::indexList[3][4] = {
	{ 6, 7, 0, 1 }, // xmin face
	{ 6, 0, 4, 2 }, // ymin face
	{ 1, 7, 3, 5 }  // ymax face
};

typedef float vec3[3];

Table::Table(ShaderIF* sIF, PhongMaterial& matl, float topHeight, float legHeight, float topRadius, 
	float cx, float cy) : SceneElement(sIF, matl)
{

	m_radius = topRadius;
	m_height = legHeight + topHeight;
	m_cx = cx; m_cy = cy;

	glGenVertexArrays(6, vao);

	defineLeg1(legHeight, topRadius, cx, cy);
	defineLeg2(legHeight, topRadius, cx, cy);
	defineLeg3(legHeight, topRadius, cx, cy);
	defineLeg4(legHeight, topRadius, cx, cy);

	defineTableTop();

	defineTop(cx, cy, legHeight, topRadius, topHeight);
}

Table::~Table()
{
	glDeleteBuffers(3, ebo);
	glDeleteBuffers(1, vboTop);
	glDeleteBuffers(1, vboTableTop);
	glDeleteBuffers(1, vboLeg1);
	glDeleteBuffers(1, vboLeg2);
	glDeleteBuffers(1, vboLeg3);
	glDeleteBuffers(1, vboLeg4);
	glDeleteVertexArrays(6, vao);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Table::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = m_cx - m_radius; // xmin  
	xyzLimits[1] = m_cx + m_radius; // xmax        
	xyzLimits[2] = m_cy - m_radius; // ymin        
	xyzLimits[3] = m_cy + m_radius; // ymax        
	xyzLimits[4] = 0.0; 			// zmin        
	xyzLimits[5] = m_height; 		// zmax       
}

const int N_VERTICES = 100;
void Table::defineTableTop(){

	vec3* coords = new vec3[N_VERTICES+1];

	coords[0][0] = m_cx;
	coords[0][1] = m_cy;
	coords[0][2] = m_height;

	double theta = 0.0;
	float dTheta = 2.0 * M_PI / (N_VERTICES-1);

	for (int i=1 ; i<N_VERTICES ; i++)
	{
		coords[i][0] = m_cx + m_radius * cos(theta);
		coords[i][1] = m_cy + m_radius * sin(theta);
		coords[i][2] = m_height;

		theta += dTheta;
	}
	// last point has same coordinates as first
	for (int i=0 ; i<3 ; i++)
	{
		coords[N_VERTICES][i] = coords[1][i];
	}

	glBindVertexArray(vao[5]);
	glGenBuffers(1, vboTableTop);
	glBindBuffer(GL_ARRAY_BUFFER, vboTableTop[0]);
	glBufferData(GL_ARRAY_BUFFER, (N_VERTICES+1)*sizeof(vec3), coords, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	delete [] coords;
}

void Table::renderTableTop(){

	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 0.0, 1.0);

	glBindVertexArray(vao[5]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, N_VERTICES+1);

}

void Table::defineLeg1(float h, float r, float cx, float cy){

	float xmin, xmax, ymin, ymax;
	float w = r / 5; // leg width = radius / 5
	float zmin = 0.0; 
	float zmax = h;

	// LEG 1
	xmin = cx - (w / 2); xmax = cx + (w / 2);
	ymin = cy + r - w; ymax = cy + r;

	vec3 leg1[] = {
		{xmin ,ymin, zmax}, {xmin, ymax, zmax},
		{xmax, ymin, zmax}, {xmax, ymax, zmax},
		{xmax, ymin, zmin}, {xmax, ymax, zmin},
		{xmin, ymin, zmin}, {xmin, ymax, zmin}
	};

	glBindVertexArray(vao[1]);
	glGenBuffers(1, vboLeg1);
	glBindBuffer(GL_ARRAY_BUFFER, vboLeg1[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), leg1, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));
}

void Table::defineLeg2(float h, float r, float cx, float cy) {
	float xmin, xmax, ymin, ymax;
	float w = r / 5; // leg width = radius / 5
	float zmin = 0.0; 
	float zmax = h;

	xmin = cx + r - w; xmax = cx + r;
	ymin = cy - (w / 2); ymax = cy + (w / 2);

	vec3 leg2[] = {
		{xmin ,ymin, zmax}, {xmin, ymax, zmax},
		{xmax, ymin, zmax}, {xmax, ymax, zmax},
		{xmax, ymin, zmin}, {xmax, ymax, zmin},
		{xmin, ymin, zmin}, {xmin, ymax, zmin}
	};

	glBindVertexArray(vao[2]);
	glGenBuffers(1, vboLeg2);
	glBindBuffer(GL_ARRAY_BUFFER, vboLeg2[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), leg2, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));
}

void Table::defineLeg3(float h, float r, float cx, float cy) {
	
	float xmin, xmax, ymin, ymax;
	float w = r / 5; // leg width = radius / 5
	float zmin = 0.0; 
	float zmax = h;

	xmin = cx - (w / 2); xmax = cx + (w / 2);
	ymin = cy - r; ymax = cy - r + w;

	vec3 leg3[] = {
		{xmin ,ymin, zmax}, {xmin, ymax, zmax},
		{xmax, ymin, zmax}, {xmax, ymax, zmax},
		{xmax, ymin, zmin}, {xmax, ymax, zmin},
		{xmin, ymin, zmin}, {xmin, ymax, zmin}
	};

	glBindVertexArray(vao[3]);
	glGenBuffers(1, vboLeg3);
	glBindBuffer(GL_ARRAY_BUFFER, vboLeg3[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), leg3, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

}

void Table::defineLeg4(float h, float r, float cx, float cy) {

	float xmin, xmax, ymin, ymax;
	float w = r / 5; // leg width = radius / 5
	float zmin = 0.0; 
	float zmax = h;

	xmin = cx - r; xmax = cx - r + w;
	ymin = cy - (w / 2); ymax = cy + (w / 2);

	vec3 leg4[] = {
		{xmin ,ymin, zmax}, {xmin, ymax, zmax},
		{xmax, ymin, zmax}, {xmax, ymax, zmax},
		{xmax, ymin, zmin}, {xmax, ymax, zmin},
		{xmin, ymin, zmin}, {xmin, ymax, zmin}
	};

	glBindVertexArray(vao[4]);
	glGenBuffers(1, vboLeg4);
	glBindBuffer(GL_ARRAY_BUFFER, vboLeg4[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), leg4, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));
}

void Table::renderLegs(){

	glGenBuffers(3, ebo);
	for (int i=0 ; i<3 ; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexList[i], GL_STATIC_DRAW);
	}

	for (int i=1; i<5; i++){

		glBindVertexArray(vao[i]);

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
}

// cylinder creation borrowed and adapted from defineCylinder() of MandM Cylinder class
const int N_POINTS_AROUND_SLICE = 18; // number points around a cross-section 
void Table::defineTop(float cx, float cy, float cz, float r, float h){

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
		coords[j][0] = cx + r*dx; coords[j][1] = cy + r*dy; coords[j][2] = cz;
		normals[j+1][0] = dx; normals[j+1][1] = dy; normals[j+1][2] = 0.0;
		coords[j+1][0] = cx + r*dx; coords[j+1][1] = cy + r*dy; coords[j+1][2] = cz + h;

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

void Table::renderTop(){

	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 2*(N_POINTS_AROUND_SLICE+1));

}

void Table::render()
{
	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	glUseProgram(shaderIF->getShaderPgmID());

	establishLightingEnvironment();
	establishView();
	establishMaterial();

	renderLegs();
	renderTableTop();
	renderTop();

	glUseProgram(program);
}
