// Book.h

#ifndef Book_H
#define Book_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "ModelView.h"
#include "ShaderIF.h"

class Book : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	Book(ShaderIF* sIF, float cx, float cy, float cz, float bookHeight,
	float bookWidth, float bookLength, float R, float G, float B);
	virtual ~Book();

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

	GLuint vao[1];
	GLuint ebo[3];
	GLuint vbo[1];

	void defineBook();
	void renderBook();
};

#endif
