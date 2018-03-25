// Couch.h

#ifndef COUCH_H
#define COUCH_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "SceneElement.h"
#include "AffPoint.h"
#include "AffVector.h"
#include "BasicShapeRenderer.h"

static const int NUM_PIECES = 4;

class Couch : public SceneElement
{
public:
	Couch(ShaderIF* sIF, const PhongMaterial& matlIn,
		cryph::AffPoint corner, cryph::AffVector u,
		double couchWidth, double couchDepth, double couchHeight);
	virtual ~Couch();

	void getMCBoundingBox(double* xyzLimits) const; // {xmin, xmax, ymin, ymax, zmin, zmax}
	void render();

private:
	BasicShape* pieces[NUM_PIECES]; // back, seat, two armrests
	BasicShapeRenderer* piecesR[NUM_PIECES];

	double xyz[6];

	void defineInitialGeometry(cryph::AffPoint corner, cryph::AffVector u,
		double couchWidth, double couchDepth, double couchHeight);
};

#endif
