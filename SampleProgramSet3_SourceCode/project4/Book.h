// Book.h

#ifndef Book_H
#define Book_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "SceneElement.h"
#include "ShaderIF.h"

class Book : public SceneElement
{
public:
	// As before: you will likely want to add parameters to the constructor
	Book(ShaderIF* sIF, PhongMaterial& matl, float cx, float cy, float cz, float bookHeight,
	float bookWidth, float bookLength);
	virtual ~Book();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:

	float xmin, ymin, zmin;
	float xmax, ymax, zmax;

	static GLuint indexList[3][4];

	GLuint vao[1];
	GLuint ebo[3];
	GLuint vbo[1];

	void defineBook();
	void renderBook();
};

#endif
