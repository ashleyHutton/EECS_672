// Floor.h

#ifndef Floor_H
#define Floor_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "ModelView.h"
#include "ShaderIF.h"

class Floor : public ModelView
{
public:
	// As before: you will likely want to add parameters to the constructor
	Floor(ShaderIF* sIF, float _xmin, float _xmax, float _ymin, float _ymax);
	virtual ~Floor();

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

	GLuint vao[1];
	GLuint vbo[1];

	void defineInitialGeometry();
};

#endif
