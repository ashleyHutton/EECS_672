// Wall.c++

#include "Wall.h"

Wall::Wall(ShaderIF* sIF, PhongMaterial& matl, float _xmin, float _xmax, float _ymin, float _ymax, float _zmin, float _zmax,
	float _xnorm, float _ynorm) :
 SceneElement(sIF, matl)
{
	xmin = _xmin; xmax = _xmax;
	ymin = _ymin; ymax = _ymax;
	zmin = _zmin; zmax = _zmax;

	xnorm = _xnorm;
	ynorm = _ynorm;

	defineInitialGeometry();
}

Wall::~Wall()
{
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Wall::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin; // xmin  
	xyzLimits[1] = xmax; // xmax         
	xyzLimits[2] = ymin; // ymin         
	xyzLimits[3] = ymax; // ymax        
	xyzLimits[4] = zmin; // zmin         
	xyzLimits[5] = zmax; // zmax        
}

void Wall::defineInitialGeometry(){

	float mcPosition[4][3] = {
		{xmin, ymin, zmin},
		{xmin, ymin, zmax},
		{xmax, ymax, zmin},
		{xmax, ymax, zmax}
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

void Wall::render()
{
	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);
	glUseProgram(shaderIF->getShaderPgmID());

	establishLightingEnvironment();
	establishView();
	establishMaterial();

	glBindVertexArray(vao[0]);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), xnorm, ynorm, 0.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0 , 4);

	glUseProgram(program);
}
