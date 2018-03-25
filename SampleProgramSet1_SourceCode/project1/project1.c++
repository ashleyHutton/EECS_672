// project1.c++

// Name: Ashley Hutton
// KUID: 2764001
// Date: 9/20/2017
// EECS 672 Project 1 F2017

#include "GLFWController.h"
#include "ModelView.h"
#include <fstream>
#include <math.h>

void makeCurve(Controller& c, ShaderIF* sIF, float a[], float b[], float tmin, float tmax, int nPoints){

	float dt = (tmax-tmin) / (nPoints - 1);
	float xt;
	float yt;
	vec2 vertexPositions[nPoints];

	// evaluate each curve at the specified number of points ("nPoints") for that curve
	// tmin, tmin+dt, tmin+2*dt, …, tmax, where dt=(tmax-tmin)/(nPoints-1)
	// (x(t), y(t)) = (a0 + a1t + a2t2 + a3t3, b0 + b1t + b2t2 + b3t3)
	// the four ai and the four bi are constants that define the shape of the curve. 
	// The parameter, t, varies across some parametric range: tmin ≤ t ≤ tmax.
	for(int i=0; i<nPoints; i++){
		float t = tmin + (i*dt);
		xt = a[0] + (a[1] * t) + (a[2] * pow(t,2.0)) + (a[3] * pow(t,3.0));
		yt = b[0] + (b[1] * t) + (b[2] * pow(t,2.0)) + (b[3] * pow(t,3.0));
		vertexPositions[i][0] = xt;
		vertexPositions[i][1] = yt;
	}

	c.addModel( new ModelView(sIF, vertexPositions, nPoints) );
}

int main(int argc, char* argv[])
{
	GLFWController c(argv[0]);
	c.reportVersions(std::cout);

	if (argc > 1) {

		ShaderIF* sIF = new ShaderIF("shaders/project1.vsh", "shaders/project1.fsh");

		// float a[] = {
		// 	7.69375, 1.89999, -1.99686 , -0.20626
		// };
		// float b[] = {
		// 	-11.7812 , 4.19375, 2.89376, -2.62501
		// };
		// float tmin = 0.0;
		// float tmax = 1.0;
		// int nPoints = 30;
		// makeCurve(c, sIF, a, b, tmin, tmax, nPoints);
		
		float a[4];
		float b[4];
		float tmin = 0.0;
		float tmax = 0.0;
		int nPoints = 0;

		// read from input file an arbitrary number of curves
		std::ifstream inputFile;
		std::string filename = argv[1];
		inputFile.open(filename);
		while(inputFile){
			inputFile >> a[0] >> a[1] >> a[2] >> a[3];
			inputFile >> b[0] >> b[1] >> b[2] >> b[3];
			inputFile >> tmin;
			inputFile >> tmax;
			inputFile >> nPoints;

			makeCurve(c, sIF, a, b, tmin, tmax, nPoints);
		}

		// TODO: one or more ModelView dynamic allocations, adding
		//       each to the Controller using "c.addModel(...);" DONE
		//
		//       NOTE: You will likely want to modify the ModelView
		//             constructor to take additional parameters.

		// initialize 2D viewing information:
		// Get the overall scene bounding box in Model Coordinates:
		double xyz[6]; // xyz limits, even though this is 2D
		c.getOverallMCBoundingBox(xyz);
		// Tell class ModelView we initially want to see the whole scene:
		ModelView::setMCRegionOfInterest(xyz);

		glClearColor(1.0, 1.0, 1.0, 1.0);
		c.run();

		delete sIF;
	}
	else {
		std::cout << "\nError. No filename given.\n";
	}

	return 0;
}
