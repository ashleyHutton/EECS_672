// Pillow.h

#ifndef PILLOW_H
#define PILLOW_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "SceneElement.h"
#include "AffPoint.h"
#include "AffVector.h"
#include "BasicShapeRenderer.h"


class Pillow : public SceneElement
{
public:
	Pillow(ShaderIF* sIF, const PhongMaterial& matlIn,
		cryph::AffPoint bottom, cryph::AffVector u,
		double pillowThickness, double pillowRadius);
	virtual ~Pillow();

	void getMCBoundingBox(double* xyzLimits) const; // {xmin, xmax, ymin, ymax, zmin, zmax}
	void render();

private:
	BasicShape* piece;
	BasicShapeRenderer* pieceR;

	double xyz[6];

	void defineInitialGeometry(cryph::AffPoint bottom, cryph::AffVector u,
		double pillowThickness, double pillowRadius);

};

#endif
