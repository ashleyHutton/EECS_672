// Bookshelf.h

#ifndef Bookshelf_H
#define Bookshelf_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "ModelView.h"
#include "ShaderIF.h"

class Bookshelf : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	Bookshelf(ShaderIF* sIF, float cx, float cy, float cz, float bookshelfHeight,
	float bookshelfWidth, float bookshelfDepth, float R, float G, float B);
	virtual ~Bookshelf();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	ShaderIF* shaderIF;
	float kd[3];
	float ka[3];
	float la[3];

	float xmin, ymin, zmin;
	float xmax, ymax, zmax;

	static GLuint indexList[3][4];

	GLuint vao[4]; // 0: Case edges, 1: shelf 1, 2: shelf 2, 3: shelf 3
	GLuint ebo[3];
	GLuint vbo[1];
	GLuint vboShelf1[1];
	GLuint vboShelf2[1];
	GLuint vboShelf3[1];

	void defineCase();
	void defineShelf1();
	void defineShelf2();
	void defineShelf3();

	void renderCase();
	void renderShelves();
};

#endif
