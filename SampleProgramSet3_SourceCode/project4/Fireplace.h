// Fireplace.h

#ifndef FIREPLACE_H
#define FIREPLACE_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "SceneElement.h"
#include "AffPoint.h"
#include "AffVector.h"
#include "BasicShapeRenderer.h"

class Fireplace : public SceneElement
{
public:
	Fireplace(ShaderIF* sIF, const PhongMaterial& matlIn,
		cryph::AffPoint corner, cryph::AffVector u,
		double fireplaceWidth, double fireplaceDepth, double fireplaceHeight);
	virtual ~Fireplace();

	void getMCBoundingBox(double* xyzLimits) const; // {xmin, xmax, ymin, ymax, zmin, zmax}
	void render();

private:
	BasicShape* pieces[4]; // mantle, base, body, and fire
	BasicShapeRenderer* piecesR[4];

	double xyz[6];
	int num_pieces;
	int cur_piece; // for prepare for face function

	static void prepareForFace(void* caller, int faceIndex);

	void defineInitialGeometry(cryph::AffPoint corner, cryph::AffVector u,
		double fireplaceWidth, double fireplaceDepth, double fireplaceHeight);
};

#endif
