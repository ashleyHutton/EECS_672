// Wall.h

#ifndef Wall_H
#define Wall_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "ModelView.h"
#include "ShaderIF.h"

class Wall : public ModelView
{
public:
	Wall(ShaderIF* sIF, float _xmin, float _xmax, float _ymin, float _ymax, float _zmin, float _zmax,
		float R, float G, float B);
	virtual ~Wall();

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
