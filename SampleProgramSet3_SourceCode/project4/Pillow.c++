// Pillow.c++

#include "Pillow.h"

Pillow::Pillow(ShaderIF* sIF, const PhongMaterial& matlIn,
		cryph::AffPoint bottom, cryph::AffVector u,
		double pillowThickness, double pillowRadius)
		 : SceneElement(sIF, matlIn)
{
	defineInitialGeometry(bottom, u, pillowThickness, pillowRadius);
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

Pillow::~Pillow()
{
	if (piece != nullptr) delete piece;
	if (pieceR != nullptr) delete pieceR;
}

void Pillow::defineInitialGeometry(cryph::AffPoint bottom, cryph::AffVector u,
		double pillowThickness, double pillowRadius)
{
	piece = BasicShape::makeBoundedCylinder(bottom, bottom + (pillowThickness * u), pillowRadius, 20, 2);
}

void Pillow::getMCBoundingBox(double* xyzLimits) const
{
	for (int i=0 ; i<6 ; i++)
		xyzLimits[i] = xyz[i];
}

void Pillow::render()
{
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	establishLightingEnvironment();
	establishMaterial();
	establishView();
	establishTexture();

	if (pieceR != nullptr)
		pieceR->drawShape();

	setColorGenerationMode(0);

	glUseProgram(pgm);
}
