// Floor.h

#ifndef Floor_H
#define Floor_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "SceneElement.h"
#include "ShaderIF.h"

class Floor : public SceneElement
{
public:
	// As before: you will likely want to add parameters to the constructor
	Floor(ShaderIF* sIF, PhongMaterial& matl, float _xmin, float _xmax, float _ymin, float _ymax);
	virtual ~Floor();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:

	float xmin, ymin, zmin;
	float xmax, ymax, zmax;

	GLuint vao[1];
	GLuint vbo[1];

	void defineInitialGeometry();
};

#endif
