// Bookshelf.c++

#include "Bookshelf.h"

GLuint Bookshelf::indexList[3][4] = {
	{ 6, 7, 0, 1 }, // xmin face
	{ 6, 0, 4, 2 }, // zmin face
	{ 1, 7, 3, 5 }  // zmax face
};

typedef float vec3[3];

Bookshelf::Bookshelf(ShaderIF* sIF, float cx, float cy, float cz, float bookshelfHeight,
	float bookshelfWidth, float bookshelfDepth, float R, float G, float B) :
 shaderIF(sIF)
{
	// cx, cy, cz = bottom left corner of Bookshelf
	xmin = cx; xmax = cx + bookshelfWidth;
	ymin = cy; ymax = cy + bookshelfDepth;
	zmin = cz; zmax = cz + bookshelfHeight;

	kd[0] = R; kd[1] = G; kd[2] = B;
	ka[0] = R; ka[1] = G; ka[2] = B;
	la[0] = 0.15; la[1] = 0.15; la[2] = 0.15;

	glGenVertexArrays(4, vao);

	defineCase();
	defineShelf1();
	defineShelf2();
	defineShelf3();
}

Bookshelf::~Bookshelf()
{
	glDeleteBuffers(3, ebo);
	glDeleteBuffers(1, vbo);
	glDeleteBuffers(1, vboShelf1);
	glDeleteBuffers(1, vboShelf2);
	glDeleteBuffers(1, vboShelf3);
	glDeleteVertexArrays(4, vao);
}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Bookshelf::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin; // xmin  
	xyzLimits[1] = xmax; // xmax         
	xyzLimits[2] = ymin; // ymin         
	xyzLimits[3] = ymax; // ymax        
	xyzLimits[4] = zmin; // zmin         
	xyzLimits[5] = zmax; // zmax        
}

void Bookshelf::defineCase(){

	vec3 vertices[] = { 
		{xmin ,ymax, zmin}, {xmin, ymax, zmax},
		{xmax, ymax, zmin}, {xmax, ymax, zmax},
		{xmax, ymin, zmin}, {xmax, ymin, zmax},
		{xmin, ymin, zmin}, {xmin, ymin, zmax}
	};
	glBindVertexArray(vao[0]);

	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	glDisableVertexAttribArray(shaderIF->pvaLoc("mcNormal"));

}	

void Bookshelf::renderCase(){

	glBindVertexArray(vao[0]);

	// The three faces that can be drawn with glDrawArrays
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 1.0, 0.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 1.0, 0.0, 0.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 2, 4);

	// The three faces that are drawn with glDrawElements
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), -1.0, 0.0, 0.0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 0.0, -1.0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), 0.0, 0.0, 1.0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[2]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
}

void Bookshelf::defineShelf1(){

	float s_zmin = (zmax / 4);
	float s_zmax = (zmax / 4) + (zmax * 0.02);

	vec3 shelf1[] = {
		{xmin ,ymin, s_zmax}, {xmin, ymax, s_zmax},
		{xmax, ymin, s_zmax}, {xmax, ymax, s_zmax},
		{xmax, ymin, s_zmin}, {xmax, ymax, s_zmin},
		{xmin, ymin, s_zmin}, {xmin, ymax, s_zmin}
	};

	glBindVertexArray(vao[1]);
	glGenBuffers(1, vboShelf1);
	glBindBuffer(GL_ARRAY_BUFFER, vboShelf1[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), shelf1, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));
}

void Bookshelf::defineShelf2(){

	float s_zmin = (zmax / 2);
	float s_zmax = (zmax / 2) + (zmax * 0.02);

	vec3 shelf2[] = {
		{xmin ,ymin, s_zmax}, {xmin, ymax, s_zmax},
		{xmax, ymin, s_zmax}, {xmax, ymax, s_zmax},
		{xmax, ymin, s_zmin}, {xmax, ymax, s_zmin},
		{xmin, ymin, s_zmin}, {xmin, ymax, s_zmin}
	};

	glBindVertexArray(vao[2]);
	glGenBuffers(1, vboShelf2);
	glBindBuffer(GL_ARRAY_BUFFER, vboShelf2[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), shelf2, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));
}

void Bookshelf::defineShelf3(){

	float s_zmin = (zmax * (3.0/4.0));
	float s_zmax = (zmax * (3.0/4.0)) + (zmax * 0.02);

	vec3 shelf3[] = {
		{xmin ,ymin, s_zmax}, {xmin, ymax, s_zmax},
		{xmax, ymin, s_zmax}, {xmax, ymax, s_zmax},
		{xmax, ymin, s_zmin}, {xmax, ymax, s_zmin},
		{xmin, ymin, s_zmin}, {xmin, ymax, s_zmin}
	};

	glBindVertexArray(vao[3]);
	glGenBuffers(1, vboShelf3);
	glBindBuffer(GL_ARRAY_BUFFER, vboShelf3[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), shelf3, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));
}

void Bookshelf::renderShelves(){

	for (int i=1; i<4; i++){

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

void Bookshelf::render()
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

	glUniform3fv(shaderIF->ppuLoc("kd"), 1, kd);
	glUniform3fv(shaderIF->ppuLoc("ka"), 1, ka);
	glUniform3fv(shaderIF->ppuLoc("la"), 1, la);

	glGenBuffers(3, ebo);
	for (int i=0 ; i<3 ; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexList[i], GL_STATIC_DRAW);
	}

	renderCase();
	renderShelves();

	// 5. Reestablish previous shader program
	glUseProgram(program);
}
