// Wall.c++

#include "Wall.h"

Wall::Wall(ShaderIF* sIF, const PhongMaterial& matlIn,
		cryph::AffPoint bottom, cryph::AffVector u,
		double wallHeight, double wallWidth)
		 : SceneElement(sIF, matlIn)
{
	defineInitialGeometry(bottom, u, wallHeight, wallWidth);
	xyz[0] = 1.0; xyz[1] = 0.0;

	if (piece == nullptr) {
		pieceR = nullptr;
	}
	else
	{
		pieceR = new BasicShapeRenderer(sIF, piece);
		// accumulate bounding box
		if (xyz[0] > xyz[1]) // not yet initialized
			piece->getMCBoundingBox(xyz);
		else
		{
			double cur_xyz[6];
			piece->getMCBoundingBox(cur_xyz);
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

Wall::~Wall()
{
	if (piece != nullptr) delete piece;
	if (pieceR != nullptr) delete pieceR;
}

void Wall::defineInitialGeometry(cryph::AffPoint bottom, cryph::AffVector u,
		double wallHeight, double wallWidth)
{
	cryph::AffVector uu(u[0], u[1], 0.0), ww(0,0,1);
	uu.normalize();
	cryph::AffVector vv = ww.cross(uu);
	piece = BasicShape::makeBlock(bottom, uu, wallWidth, vv, 0.1, ww, wallHeight);
}

void Wall::getMCBoundingBox(double* xyzLimits) const
{
	for (int i=0 ; i<6 ; i++)
		xyzLimits[i] = xyz[i];
}

void Wall::prepareForFace(void* caller, int faceIndex)
{
	if (caller == nullptr)
		// No caller passed to "drawShape"; cannot proceed
		return;
	Wall* thisWall = reinterpret_cast<Wall*>(caller);
	thisWall->setColorGenerationMode(0); // just light model

	if (faceIndex == 0){

		thisWall->pieceR->setTexCoordsForBlock(faceIndex);
		thisWall->setTextureSource(0); // texture map
		thisWall->setColorGenerationMode(20); // light model * texture
	}

	thisWall->establishTexture();
}

void Wall::render()
{
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	establishLightingEnvironment();
	establishMaterial();
	establishView();

	if (pieceR != nullptr)
		pieceR->drawShape(prepareForFace, this);

	setColorGenerationMode(0);

	glUseProgram(pgm);
}
