// Spark.h

#ifndef SPARK_H
#define SPARK_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "SceneElement.h"
#include "AffPoint.h"
#include "AffVector.h"
#include "BasicShapeRenderer.h"

class Spark : public SceneElement
{
public:
	Spark(ShaderIF* sIF, const PhongMaterial& matlIn,
		cryph::AffPoint bottom, double size);
	virtual ~Spark();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:

	BasicShape* piece;
	BasicShapeRenderer* pieceR;

	double xyz[6];

	void defineInitialGeometry(cryph::AffPoint bottom, double size);
};

#endif
