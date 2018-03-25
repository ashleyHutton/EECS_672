// SceneElement.c++

#include "SceneElement.h"
#include "ImageReader.h"

float SceneElement::lightPos[4*MAX_NUM_LIGHTS] =
	{
		1.0, 1.0, 1.0, 0.0,
		-2.0, -2.2, 2.0, 1.0,  // lamp
		2.0, -2.2, 2.0, 1.0    // lamp
	};

// Are coordinates in "lightPos" stored in MC or EC?
bool SceneElement::posInModelCoordinates[MAX_NUM_LIGHTS] =
	{ true, true, true };
// The following is the buffer actually sent to GLSL. It will contain a copy of
// the (x,y,z,w) for light sources defined in EC; it will contain the coordinates
// after transformation to EC if the position was originally specified in MC.
float posToGLSL[4*MAX_NUM_LIGHTS];

float SceneElement::lightStrength[3*MAX_NUM_LIGHTS] =
	{
		0.6, 0.6, 0.6,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8
	};

float SceneElement::globalAmbient[] = { 0.4, 0.4, 0.4 };

SceneElement::SceneElement(ShaderIF* sIF, const PhongMaterial& matlIn) :
	shaderIF(sIF), matl(matlIn), texID(0), colorGenerationMode(-1),
	textureSource(-1)
{
}

SceneElement::~SceneElement()
{
}

void SceneElement::establishLightingEnvironment()
{
	// This should set:
	// "actualNumLights", "ecLightPosition", "lightStrength", "globalAmbient"
	int numLights = 3;

	cryph::Matrix4x4 mc_ec, ec_lds;
	ModelView::getMatrices(mc_ec, ec_lds);
	cryph::AffPoint transformedPos;

	for (int i=0; i<numLights; i++){

		for (int j=(4*i); j<(4*i)+4; j++){
			posToGLSL[j] = lightPos[j];
		}

		if (posInModelCoordinates[i]){
			if (lightPos[(4*i)+3] == 1) { // positional

				cryph::AffPoint posToTransform(
					lightPos[4*i], 
					lightPos[(4*i)+1], 
					lightPos[(4*i)+2]
				);
				transformedPos = mc_ec * posToTransform;
			}
			else { // directional 

				cryph::AffVector vecToTransform(
					lightPos[4*i], 
					lightPos[(4*i)+1], 
					lightPos[(4*i)+2]
				);
				transformedPos = mc_ec * vecToTransform;
			}

			posToGLSL[4*i] = transformedPos[0];
			posToGLSL[(4*i)+1] = transformedPos[1];
			posToGLSL[(4*i)+2] = transformedPos[2];

		}
	}

	glUniform4fv(shaderIF->ppuLoc("p_ecLightSourcePos"), numLights, posToGLSL);
	glUniform3fv(shaderIF->ppuLoc("lightStrength"), numLights, lightStrength);
	glUniform1i(shaderIF->ppuLoc("actualNumLights"), numLights);
	glUniform3fv(shaderIF->ppuLoc("globalAmbient"), 1, globalAmbient);

}

void SceneElement::establishMaterial()
{
	glUniform3fv(shaderIF->ppuLoc("kd"), 1, matl.kd);
	glUniform3fv(shaderIF->ppuLoc("ka"), 1, matl.ka);
	glUniform3fv(shaderIF->ppuLoc("ks"), 1, matl.ks);
	glUniform1f(shaderIF->ppuLoc("shininess"), matl.shininess);

}

void SceneElement::establishTexture()
{
	// Unless you are texture-mapping onto faces of BasicShape instances,
	// this method should be called from your render method, and it should
	// set texture-related parameters like:
	// "colorGenerationMode", "textureSource", "textureMap"
	// It should also do the appropriate call to glBindTexture.
	// (If you are texture-mapping onto faces of BasicShape instances,
	// you use the "prepareForFace" callback which may or may not be
	// implemented by calling this method.)
}

void SceneElement::establishView()
{
	// Line of sight, dynamic view controls, 3D-2D projection, & mapping to LDS:
	cryph::Matrix4x4 mc_ec, ec_lds;
	ModelView::getMatrices(mc_ec, ec_lds);
	float m[16];
	glUniformMatrix4fv(shaderIF->ppuLoc("mc_ec"), 1, false, mc_ec.extractColMajor(m));
	glUniformMatrix4fv(shaderIF->ppuLoc("ec_lds"), 1, false, ec_lds.extractColMajor(m));
}

bool SceneElement::handleCommand(unsigned char anASCIIChar, double ldsX, double ldsY)
{
	if (anASCIIChar == 'O')
		ModelView::setProjection(ORTHOGONAL);
	else if (anASCIIChar == 'P')
		ModelView::setProjection(PERSPECTIVE);
	else if (anASCIIChar == 'Q')
		ModelView::setProjection(OBLIQUE);
	else
		return ModelView::handleCommand(anASCIIChar, ldsX, ldsY);
	Controller::getCurrentController()->redraw();
	return true;
}

void SceneElement::setColorGenerationMode(int mode, int onFace)
{
	colorGenerationMode = mode;
}

void SceneElement::setTextureImage(const std::string& imgFileName, int onFace)
{
	ImageReader* ir = ImageReader::create(imgFileName.c_str());
	if (ir == nullptr)
	{
		std::cerr << "Could not open '" << imgFileName << "' for texture map.\n";
		return;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	float white[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, white);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //GL_CLAMP_TO_BORDER);
	GLint level = 0;
	int pw = ir->getWidth(), ph = ir->getHeight();
	GLint iFormat = ir->getInternalFormat();
	GLenum format = ir->getFormat();
	GLenum type = ir->getType();
	const GLint border = 0; // must be zero (only present for backwards compatibility)
	const void* pixelData = ir->getTexture();
	glTexImage2D(GL_TEXTURE_2D, level, iFormat, pw, ph, border, format, type, pixelData);
	delete ir;
}

void SceneElement::setTextureSource(int source, int onFace)
{
	textureSource = source;
}
