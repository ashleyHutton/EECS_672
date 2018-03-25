// Floor.c++

#include "Floor.h"

Floor::Floor(ShaderIF* sIF, PhongMaterial& matl, float _xmin, float _xmax, float _ymin, float _ymax) :
 SceneElement(sIF, matl)
{
	xmin = _xmin; xmax = _xmax;
	ymin = _ymin; ymax = _ymax;
	zmin = 0.0; zmax = 0.0;

	defineInitialGeometry();
}

Floor::~Floor()
{
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Floor::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin; // xmin  
	xyzLimits[1] = xmax; // xmax         
	xyzLimits[2] = ymin; // ymin         
	xyzLimits[3] = ymax; // ymax        
	xyzLimits[4] = zmin; // zmin         
	xyzLimits[5] = zmax; // zmax        
}

void Floor::defineInitialGeometry(){

	float mcPosition[4][3] = {
		{xmin, ymin, 0.0},
		{xmin, ymax, 0.0},
		{xmax, ymin, 0.0},
		{xmax, ymax, 0.0}
	};

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(float), mcPosition, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	glDisableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

}	

void Floor::render()
{
	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	glUseProgram(shaderIF->getShaderPgmID());

	establishLightingEnvironment();
	establishView();
	establishMaterial();

	glBindVertexArray(vao[0]);

	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 0.0, 1.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0 , 4);

	glUseProgram(program);
}
