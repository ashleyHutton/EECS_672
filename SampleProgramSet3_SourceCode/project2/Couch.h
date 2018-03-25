// Couch.h

#ifndef Couch_H
#define Couch_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "ModelView.h"
#include "ShaderIF.h"

class Couch : public ModelView
{
public:
	Couch(ShaderIF* sIF, cryph::AffPoint vertices[],
		float R, float G, float B);
	virtual ~Couch();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	ShaderIF* shaderIF;
	float kd[3];
	float ka[3];
	float la[3];
	
	int numVertices = 14;

	GLuint vao[1]; 
	GLuint vbo[1];
	GLuint ebo[4];

	static GLuint indexList[4][4];

	double bounds[6];
	void setBounds(cryph::AffPoint vertices[]);

	cryph::AffVector normal[9]; // normals for 9 faces
	void setNormal(cryph::AffPoint vertices[], GLuint indicies[], int normalIndex); // calculates normal for an individual face

	void defineInitialGeometry(cryph::AffPoint vertices[]);
	void renderCouch();
};

#endif
