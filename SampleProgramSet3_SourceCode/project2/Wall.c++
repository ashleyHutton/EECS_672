// Wall.c++

#include "Wall.h"

Wall::Wall(ShaderIF* sIF, float _xmin, float _xmax, float _ymin, float _ymax, float _zmin, float _zmax,
	float R, float G, float B) :
 shaderIF(sIF)
{
	xmin = _xmin; xmax = _xmax;
	ymin = _ymin; ymax = _ymax;
	zmin = _zmin; zmax = _zmax;

	kd[0] = R; kd[1] = G; kd[2] = B;
	ka[0] = R; ka[1] = G; ka[2] = B;
	la[0] = 0.15; la[1] = 0.15; la[2] = 0.15;

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

	// 4. Establish any other attributes and make one or more calls to
	//    glDrawArrays and/or glDrawElements
	glBindVertexArray(vao[0]);

	// glDisableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 1.0, 0.0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0 , 4);

	// 5. Reestablish previous shader program
	glUseProgram(program);
}
