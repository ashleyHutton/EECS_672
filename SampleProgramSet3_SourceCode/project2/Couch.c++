// Couch.c++

#include "Couch.h"

typedef float vec3[3];

// faces that can't be drawn with glDrawArrays
GLuint Couch::indexList[4][4] = {
	{ 4, 7, 13, 12 },  // right front side
	{ 5, 3, 6, 1 },   // top of back
	{ 12, 7, 10, 8 }, // top of front
	{ 1, 0, 6, 9 }    // left back side
};

Couch::Couch(ShaderIF* sIF, cryph::AffPoint vertices[],
	float R, float G, float B) : shaderIF(sIF)
{
	kd[0] = R; kd[1] = G; kd[2] = B;
	ka[0] = R; ka[1] = G; ka[2] = B;
	la[0] = 0.15; la[1] = 0.15; la[2] = 0.15;

	defineInitialGeometry(vertices);

	bounds[0] = bounds[1] = vertices[0].x; // bounds[0] = xmin; bounds[1] = xmax
	bounds[2] = bounds[3] = vertices[0].y; // bounds[2] = ymin; bounds[3] = ymax
	bounds[4] = bounds[5] = vertices[0].z; // bounds[4] = zmin; bounds[5] = zmax
	setBounds(vertices);

}

Couch::~Couch()
{
	glDeleteBuffers(4, ebo);
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}

void Couch::setBounds(cryph::AffPoint vertices[]){

	for (int i=0; i<numVertices; i++){
		if (vertices[i].x < bounds[0]) { bounds[0] = vertices[i].x; }
		if (vertices[i].x > bounds[1]) { bounds[1] = vertices[i].x; }

		if (vertices[i].y < bounds[2]) { bounds[2] = vertices[i].y; }
		if (vertices[i].y > bounds[3]) { bounds[3] = vertices[i].y; }

		if (vertices[i].z < bounds[4]) { bounds[4] = vertices[i].z; }
		if (vertices[i].z > bounds[5]) { bounds[5] = vertices[i].z; }
	}
}

void Couch::setNormal(cryph::AffPoint vertices[], GLuint indicies[], int normalIndex){

	cryph::AffVector v01 = vertices[indicies[1]] - vertices[indicies[0]];
	cryph::AffVector v02 = vertices[indicies[2]] - vertices[indicies[0]];
	normal[normalIndex] = v01.cross(v02);
}

void Couch::defineInitialGeometry(cryph::AffPoint vertices[])
{
	vec3 vertex[numVertices];

	for (int i=0; i<numVertices; i++){
		vertices[i].aCoords(vertex, i);
	}

	// Calculate normals for the 8 faces
	GLuint firstIndex[5] = {0, 2, 5, 8, 10};
	for (int i=0; i<5; i++){
		GLuint j = firstIndex[i];
		GLuint indicies[4] = {j, j+1, j+2, j+3};
		setNormal(vertices, indicies, i);
	}
	for (int i=0; i<4; i++){
		setNormal(vertices, indexList[1], i+5);
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(vec3), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(shaderIF->pvaLoc("mcPosition"), 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(shaderIF->pvaLoc("mcPosition"));

	glGenBuffers(4, ebo);
	for (int i=0 ; i<4; i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4*sizeof(GLuint), indexList[i], GL_STATIC_DRAW);
	}
}

void Couch::renderCouch() {

	glBindVertexArray(vao[0]);

	// 4. Establish any other attributes and make one or more calls to
	//    glDrawArrays and/or glDrawElements

	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), normal[0].dx, normal[0].dy, normal[0].dz);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), normal[1].dx, normal[1].dy, normal[1].dz);
	glDrawArrays(GL_TRIANGLE_STRIP, 2, 4);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), normal[2].dx, normal[2].dy, normal[2].dz);
	glDrawArrays(GL_TRIANGLE_STRIP, 5, 4);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), normal[3].dx, normal[3].dy, normal[3].dz);
	glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), normal[4].dx, normal[4].dy, normal[4].dz);
	glDrawArrays(GL_TRIANGLE_STRIP, 10, 4);

	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), normal[5].dx, normal[5].dy, normal[5].dz);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), normal[6].dx, normal[6].dy, normal[6].dz);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), normal[7].dx, normal[7].dy, normal[7].dz);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[2]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);
	glVertexAttrib3f(shaderIF->pvaLoc("mcNormal"), normal[8].dx, normal[8].dy, normal[8].dz);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[3]);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);

}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Couch::getMCBoundingBox(double* xyzLimits) const
{
	for (int i=0; i<6; i++){
		xyzLimits[i] = bounds[i];
	}
}

void Couch::render()
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

	renderCouch();

	// 5. Reestablish previous shader program
	glUseProgram(program);
}

