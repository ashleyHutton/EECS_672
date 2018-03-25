// Wall.h

#ifndef Wall_H
#define Wall_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "SceneElement.h"
#include "ShaderIF.h"

class Wall : public SceneElement
{
public:
	Wall(ShaderIF* sIF, PhongMaterial& matl, float _xmin, float _xmax, float _ymin, float _ymax, float _zmin, float _zmax,
		float _xnorm, float _ynorm);
	virtual ~Wall();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:

	float xmin, ymin, zmin;
	float xmax, ymax, zmax;

	float xnorm, ynorm;

	GLuint vao[1];
	GLuint vbo[1];

	void defineInitialGeometry();
};

#endif
