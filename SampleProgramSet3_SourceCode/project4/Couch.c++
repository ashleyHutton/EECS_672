// Couch.c++

#include "Couch.h"

Couch::Couch(ShaderIF* sIF, const PhongMaterial& matlIn,
		cryph::AffPoint corner, cryph::AffVector u,
		double couchWidth, double couchDepth, double couchHeight)
		 : SceneElement(sIF, matlIn)
{
	defineInitialGeometry(corner, u, couchWidth, couchDepth, couchHeight);
	xyz[0] = 1.0; xyz[1] = 0.0;
	for (int i=0 ; i<NUM_PIECES ; i++)
		if (pieces[i] == nullptr)
			piecesR[i] = nullptr;
		else
		{
			piecesR[i] = new BasicShapeRenderer(sIF, pieces[i]);
			// accumulate bounding box
			if (xyz[0] > xyz[1]) // not yet initialized
				pieces[i]->getMCBoundingBox(xyz);
			else
			{
				double cur_xyz[6];
				pieces[i]->getMCBoundingBox(cur_xyz);
				for (int j=0 ; j<3 ; j++)
				{
					if (cur_xyz[2*j] < xyz[2*j])
						xyz[2*j] = cur_xyz[2*j];
					if (cur_xyz[2*j+1] > xyz[2*j+1])
						xyz[2*j+1] = cur_xyz[2*j+1];
				}
			}
		}
}

Couch::~Couch()
{
	for (int i=0 ; i<NUM_PIECES ; i++)
	{
		if (pieces[i] != nullptr)
			delete pieces[i];
		if (piecesR[i] != nullptr)
			delete piecesR[i];
	}
}

void Couch::defineInitialGeometry(cryph::AffPoint corner, cryph::AffVector u,
		double couchWidth, double couchDepth, double couchHeight)
{

	cryph::AffVector uu(u[0], u[1], 0.0), ww(0,0,1);
	uu.normalize();
	cryph::AffVector vv = ww.cross(uu);

	double armrestWidth = couchWidth * 0.1;
	double armrestHeight = couchHeight * 0.75;

	// COUCH BACK
	pieces[0] = BasicShape::makeBlock(corner,
		uu, couchWidth, vv, couchDepth/2, ww, couchHeight);
	// COUCH SEAT
	pieces[1] = BasicShape::makeBlock(corner,
		uu, couchWidth, vv, couchDepth, ww, couchHeight/2);
	// COUCH LEFT ARMREST
	pieces[2] = BasicShape::makeBlock(corner,
		uu, armrestWidth, vv, couchDepth, ww, armrestHeight);
	// COUCH RIGHT ARMREST
	pieces[3] = BasicShape::makeBlock(corner + (couchWidth - armrestWidth) * uu,
		uu, armrestWidth, vv, couchDepth, ww, armrestHeight);
}

void Couch::getMCBoundingBox(double* xyzLimits) const
{
	for (int i=0 ; i<6 ; i++)
		xyzLimits[i] = xyz[i];
}

void Couch::prepareForFace(void* caller, int faceIndex)
{
	if (caller == nullptr)
		// No caller passed to "drawShape"; cannot proceed
		return;
	Couch* thisCouch = reinterpret_cast<Couch*>(caller);
	thisCouch->setColorGenerationMode(0); // just light model
	thisCouch->establishTexture();
}


void Couch::render()
{
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	establishLightingEnvironment();
	establishView();
	establishMaterial();

	for (int i=0 ; i<NUM_PIECES ; i++)
		if (piecesR[i] != nullptr)
			piecesR[i]->drawShape(prepareForFace, this);

	glUseProgram(pgm);
}
