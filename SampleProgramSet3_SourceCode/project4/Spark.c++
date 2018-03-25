// Spark.c++

#include "Spark.h"

Spark::Spark(ShaderIF* sIF, const PhongMaterial& matlIn,
		cryph::AffPoint bottom, double size)
		 : SceneElement(sIF, matlIn)
{
	defineInitialGeometry(bottom, size);
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

Spark::~Spark()
{
	if (piece != nullptr) delete piece;
	if (pieceR != nullptr) delete pieceR;
}

void Spark::defineInitialGeometry(cryph::AffPoint bottom, double size)
{
	cryph::AffVector uu(-1.0, 0.0, 0.0), ww(0,0,1);
	cryph::AffVector vv = ww.cross(uu);
	piece = BasicShape::makeBlock(bottom, uu, size, vv, size, ww, size);
}

void Spark::getMCBoundingBox(double* xyzLimits) const
{
	for (int i=0 ; i<6 ; i++)
		xyzLimits[i] = xyz[i];
}

void Spark::render()
{
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderIF->getShaderPgmID());

	establishLightingEnvironment();
	establishMaterial();
	establishView();
	establishTexture();

	if (pieceR != nullptr)
		glUniform1i(shaderIF->ppuLoc("makeALot"), 1);
		pieceR->drawShape();
		glUniform1i(shaderIF->ppuLoc("makeALot"), 0);

	glUseProgram(pgm);
}
