// Wall.h

#ifndef Wall_H
#define Wall_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "SceneElement.h"
#include "AffPoint.h"
#include "AffVector.h"
#include "BasicShapeRenderer.h"

class Wall : public SceneElement
{
public:
	Wall(ShaderIF* sIF, const PhongMaterial& matlIn,
		cryph::AffPoint bottom, cryph::AffVector u,
		double wallHeight, double wallWidth);
	virtual ~Wall();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:

	BasicShape* piece;
	BasicShapeRenderer* pieceR;

	double xyz[6];

	void defineInitialGeometry(cryph::AffPoint bottom, cryph::AffVector u,
		double wallHeight, double wallWidth);

	static void prepareForFace(void* caller, int faceIndex);

};

#endif
