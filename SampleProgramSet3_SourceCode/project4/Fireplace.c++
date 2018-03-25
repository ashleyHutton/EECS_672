// Fireplace.c++

#include "Fireplace.h"

Fireplace::Fireplace(ShaderIF* sIF, const PhongMaterial& matlIn,
		cryph::AffPoint corner, cryph::AffVector u,
		double fireplaceWidth, double fireplaceDepth, double fireplaceHeight)
		 : SceneElement(sIF, matlIn)
{
	num_pieces = 4;

	defineInitialGeometry(corner, u, fireplaceWidth, fireplaceDepth, fireplaceHeight);
	xyz[0] = 1.0; xyz[1] = 0.0;
	for (int i=0 ; i<num_pieces ; i++)
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

Fireplace::~Fireplace()
{
	for (int i=0 ; i<num_pieces ; i++)
	{
		if (pieces[i] != nullptr)
			delete pieces[i];
		if (piecesR[i] != nullptr)
			delete piecesR[i];
	}
}

void Fireplace::defineInitialGeometry(cryph::AffPoint corner, cryph::AffVector u,
		double fireplaceWidth, double fireplaceDepth, double fireplaceHeight)
{

	cryph::AffVector uu(u[0], u[1], 0.0), ww(0,0,1);
	uu.normalize();
	cryph::AffVector vv = ww.cross(uu);

	double mantleHeight = 0.2;
	double baseHeight = 0.5;

	// FIREPLACE MANTLE
	pieces[0] = BasicShape::makeBlock(corner + (fireplaceHeight - mantleHeight) * ww,
		uu, fireplaceWidth, vv, fireplaceDepth - 0.05, ww, mantleHeight);
	// FIREPLACE BASE
	pieces[1] = BasicShape::makeBlock(corner,
		uu, fireplaceWidth, vv, fireplaceDepth, ww, baseHeight);
	// FIREPLACE BODY
	pieces[2] = BasicShape::makeBlock(corner + (0.1 * uu),
		uu, fireplaceWidth - 0.2, vv, fireplaceDepth - 0.1, ww, fireplaceHeight);
	// FIREPLACE FIRE
	pieces[3] = BasicShape::makeBlock(corner + (fireplaceWidth/4) * uu + (baseHeight * ww), 
		uu, fireplaceWidth/2, vv, fireplaceDepth - 0.05, ww, fireplaceHeight/2);
}

void Fireplace::getMCBoundingBox(double* xyzLimits) const
{
	for (int i=0 ; i<6 ; i++)
		xyzLimits[i] = xyz[i];
}

void Fireplace::prepareForFace(void* caller, int faceIndex)
{
	if (caller == nullptr)
		// No caller passed to "drawShape"; cannot proceed
		return;
	Fireplace* thisFireplace = reinterpret_cast<Fireplace*>(caller);
	thisFireplace->setColorGenerationMode(0); // just light model

	thisFireplace->piecesR[3]->setTexCoordsForBlock(faceIndex);
	thisFireplace->setTextureSource(0); // texture map
	thisFireplace->setColorGenerationMode(20);

	thisFireplace->establishTexture();
}

void Fireplace::render()
{
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	establishLightingEnvironment();
	establishView();
	establishMaterial();

	for (cur_piece=0 ; cur_piece<num_pieces ; cur_piece++) {
		if (piecesR[cur_piece] != nullptr) {
			if (cur_piece == 3) {
				glUniform1i(shaderIF->ppuLoc("isUsingTexture"), 1);
				piecesR[cur_piece]->drawShape(prepareForFace, this);
				glUniform1i(shaderIF->ppuLoc("isUsingTexture"), 0);
			}
			else  {
				piecesR[cur_piece]->drawShape(NULL, this);
			}
		}
	}

	setColorGenerationMode(0);

	glUseProgram(pgm);
}
