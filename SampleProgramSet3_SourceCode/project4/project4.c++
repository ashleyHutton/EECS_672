// project4.c++
// Author: Ashley Hutton
// Date: 12-07-17

#include <vector>

#include "GLFWController_Subclass.h"
#include "Couch.h"
#include "Floor.h"
#include "Wall.h"
#include "Table.h"
#include "Book.h"
#include "Bookshelf.h"
#include "Lamp.h"
#include "Pillow.h"
#include "Fireplace.h"
#include "Spark.h"

void addLamp(Controller& c, ShaderIF* sIF, float cx, float cy, float zmin) {

	PhongMaterial lampMatl(0.3, 0.3, 0.7);

	float lampHeight = 1.5;
	float shadeHeight = 0.4;

	c.addModel(new Lamp(sIF, lampMatl, shadeHeight, lampHeight, 0.2, zmin, cx, cy));
}

void addTables(Controller& c, ShaderIF* sIF) {

	PhongMaterial tableMatl(0.5, 0.5, 0.5, 
		0.5, 0.5, 0.5,
		0.2, 0.2, 0.2,
		10, 0.5);

	float topHeight = 0.2;
	float legHeight = 0.5;

	float topRadius; float cx; float cy;

	// Table #1 - big coffee table
	topRadius = 0.7;
	cx = 0.0;
	cy = -0.5;
	c.addModel(new Table(sIF, tableMatl, topHeight, legHeight, topRadius, cx, cy));
	
	// Table #2 - small end table lhs
	topRadius = 0.4;
	cx = -2.0;
	cy = -2.2;
	c.addModel(new Table(sIF, tableMatl, topHeight, legHeight, topRadius, cx, cy));
	addLamp(c, sIF, cx, cy, topHeight+legHeight);

	// Table #3 - small end table rhs
	topRadius = 0.4;
	cx = 2.0;
	cy = -2.2;
	c.addModel(new Table(sIF, tableMatl, topHeight, legHeight, topRadius, cx, cy));
	addLamp(c, sIF, cx, cy, topHeight+legHeight);
}

void addCouches(Controller& c, ShaderIF* sIF){

	double couchHeight = 1.0;
	double couchDepth = 1.0;
	double couchWidth = 2.6;
	PhongMaterial couchMatl(0.5, 0.5, 0.6);

	// facing east wall
	cryph::AffPoint c1(-2.5, 1.2, 0.0);
	cryph::AffVector u1(0.0, -1.0, 0.0);
	c.addModel(new Couch(sIF, couchMatl, c1, u1, couchWidth, couchDepth, couchHeight));

	// facing west wall
	cryph::AffPoint c2(2.5, -1.4, 0);
	cryph::AffVector u2(0.0, 1.0, 0.0);
	c.addModel(new Couch(sIF, couchMatl, c2, u2, couchWidth, couchDepth, couchHeight));

	PhongMaterial pillow1Matl(0.2, 0.8, 0.2);
	PhongMaterial pillow2Matl(0.2, 0.2, 0.8);
	PhongMaterial pillow3Matl(1.0, 0.1, 0.5);

	cryph::AffPoint pillow1(-1.9, 0.65, 0.55);
	cryph::AffPoint pillow2(-1.8, 0.8, 0.6);
	cryph::AffPoint pillow3(1.8, -1.0, 0.6);

	cryph::AffVector pillow1U(0.5,-0.8,1);
	cryph::AffVector pillow2U(-0.5,0.8,1);

	c.addModel(new Pillow(sIF, pillow1Matl, pillow1, pillow1U, 0.15, 0.2)); 	// small green pillow
	c.addModel(new Pillow(sIF, pillow2Matl, pillow2, pillow1U, 0.15, 0.3)); 	// large blue pillow
	c.addModel(new Pillow(sIF, pillow3Matl, pillow3, pillow2U, 0.1, 0.2)); 		// small pink pillow
}

void addBookshelf(Controller& c, ShaderIF* sIF) {

	PhongMaterial shelfMatl(0.8, 0.8, 0.8);

	float shelfHeight = 3.0;
	float shelfWidth = 1.3;
	float shelfDepth = 0.5;
	float cx1 = 1.5; float cx2 = -2.8; float cy = 2.4; float cz = 0.05;
	c.addModel(new Bookshelf(sIF, shelfMatl, cx1, cy, cz, shelfHeight, shelfWidth, shelfDepth));
	c.addModel(new Bookshelf(sIF, shelfMatl, cx2, cy, cz, shelfHeight, shelfWidth, shelfDepth));

	float shelf0Height = 0.06;
	float shelf1Height = (shelfHeight / 4) + (shelfHeight * 0.03);
	float shelf2Height = (shelfHeight / 2) + (shelfHeight * 0.03);
	float shelf3Height = (shelfHeight * (3.0/4.0)) + (shelfHeight * 0.03);

	double bookDepth[10] = {0.3, 0.2, 0.4, 0.35, 0.24, 0.45, 0.3, 0.23, 0.38, 0.35};
	double bookHeight[10] = {0.65, 0.6, 0.65, 0.47, 0.6, 0.5, 0.55, 0.5, 0.62, 0.4};
	double bookWidth[10] = {0.13, 0.1, 0.14, 0.12, 0.16, 0.11, 0.13, 0.14, 0.12, 0.13};
	double R[10] = {0.3, 0.1, 0.8, 1.0, 0.2, 0.7, 0.8, 0.9, 0.1, 0.4};
	double G[10] = {0.8, 1.0, .2, 0.7, 0.8, 0.9, 0.1, 0.4, 0.3, 0.1};
	double B[10] = {1.0, .2, 0.7, 0.8, 0.3, 0.1, 0.8, 0.9, 0.1, 0.4};

	std::vector<PhongMaterial> bookMatl;
	for (int i=0; i<10; i++){
		bookMatl.push_back(PhongMaterial(R[i], G[i], B[i]));
	}

	float bookcase1;
	float bookcase2;

	for (int i=6; i>=0; i--){
		if (i==6){ bookcase1 = cx1 + 0.01; bookcase2 = cx2 + 0.01;}
		else { bookcase1 += bookWidth[i+1] + 0.05; bookcase2 += bookWidth[i+1] + 0.05;}
		c.addModel(new Book(sIF, bookMatl.at(i), bookcase1, cy, shelf0Height, bookHeight[i]-0.1, bookWidth[i]+0.05, bookDepth[i]));
		c.addModel(new Book(sIF, bookMatl.at(i), bookcase2, cy, shelf1Height, bookHeight[i]-0.1, bookWidth[i]+0.05, bookDepth[i]));
	}
	for (int i=0; i<10; i++){
		if (i==0){ bookcase1 = cx1 + 0.01; bookcase2 = cx2 + 0.01;}
		else { bookcase1 += bookWidth[i-1]; bookcase2 += bookWidth[i-1];}
		c.addModel(new Book(sIF, bookMatl.at(i), bookcase1, cy, shelf1Height, bookHeight[i], bookWidth[i], bookDepth[i]));
		c.addModel(new Book(sIF, bookMatl.at(i), bookcase2, cy, shelf3Height, bookHeight[i], bookWidth[i], bookDepth[i]));

	}
	for (int i=9; i>=0; i--){
		if (i==9){ bookcase1 = cx1 + 0.01; bookcase2 = cx2 + 0.01;}
		else { bookcase1 += bookWidth[i+1]; bookcase2 += bookWidth[i+1];}
		c.addModel(new Book(sIF, bookMatl.at(i), bookcase1, cy, shelf2Height, bookHeight[i], bookWidth[i], bookDepth[i]));
		c.addModel(new Book(sIF, bookMatl.at(i), bookcase2, cy, shelf0Height, bookHeight[i], bookWidth[i], bookDepth[i]));
	}
	for (int i=0; i<7; i++){
		if (i==0){ bookcase1 = cx1 + 0.01; bookcase2 = cx2 + 0.01;}
		else { bookcase1 += bookWidth[i-1] + 0.05; bookcase2 += bookWidth[i-1] + 0.05;}
		c.addModel(new Book(sIF, bookMatl.at(i), bookcase1, cy, shelf3Height, bookHeight[i], bookWidth[i]+0.05, bookDepth[i]));
		c.addModel(new Book(sIF, bookMatl.at(i), bookcase2, cy, shelf2Height, bookHeight[i], bookWidth[i]+0.05, bookDepth[i]));
	}
}

void addFireplace(Controller& c, ShaderIF* sIF){
	
	PhongMaterial fireplaceMatl(1.0, 1.0, 1.0);

	double fireplaceHeight = 1.8;
	double fireplaceWidth = 2.2;
	double fireplaceDepth = 0.7;

	cryph::AffPoint center(1.1, 2.9, 0.0);
	cryph::AffVector u(-1.0, 0.0, 0.0);

	Fireplace* f = new Fireplace(sIF, fireplaceMatl, center, u, fireplaceWidth, fireplaceDepth, fireplaceHeight);
	f->setTextureImage("images/fireplace.jpg");
	c.addModel(f);

	PhongMaterial sparkMatl(0.5, 0.4, 0.2, 
		0.5, 0.4, 0.2,
		0.2, 0.15, 0.05,
		40, 1.0);

	double sparkSize = 0.03;
	cryph::AffPoint sparkCenter(-0.1, 2.2, 1.3);

	c.addModel(new Spark(sIF, sparkMatl, sparkCenter, sparkSize));
}

void addSky(Controller& c, ShaderIF* sIF){

	PhongMaterial starMatl(0.5, 0.2, 0.2, 
		0.5, 0.2, 0.2,
		0.2, 0.05, 0.05,
		40, 1.0);

	double starSize = 0.05;
	cryph::AffPoint c1(-2.0, -2.0, 6.0);
	cryph::AffPoint c2(2.0, 2.0, 6.0);

	c.addModel(new Spark(sIF, starMatl, c1, starSize));
	c.addModel(new Spark(sIF, starMatl, c2, starSize));

}

void roomStructure(Controller& c, ShaderIF* sIF) {

	PhongMaterial floorMatl(0.5, 0.35, 0.35);
	PhongMaterial wallMatl(0.5, 0.6, 0.8);
	PhongMaterial trimMatl(1.0, 1.0, 1.0);
	PhongMaterial tvMatl(0.0, 0.0, 0.0);

	cryph::AffPoint wallWest(-3.0, 3.0, 0.0);
	cryph::AffPoint wallEast(3.0, 3.0, 0.0);
	cryph::AffPoint wallNorth(-3.0, 3.0, 0.0);

	cryph::AffPoint mouldingWest(-2.9, 3.0, 4.7);
	cryph::AffPoint mouldingEast(2.9, 3.0, 4.7);
	cryph::AffPoint mouldingNorth(-3.0, 2.9, 4.7);

	cryph::AffPoint baseboardWest(-2.9, 3.0, 0.0);
	cryph::AffPoint baseboardEast(2.9, 3.0, 0.0);
	cryph::AffPoint baseboardNorth(-3.0, 2.9, 0.0);

	cryph::AffPoint television(-1.0, 2.9, 2.0);

	cryph::AffVector wallWestU(0.0, -1.0, 0.0);
	cryph::AffVector wallEastU(0.0, -1.0, 0.0);
	cryph::AffVector wallNorthU(1.0, 0.0, 0.0);

	c.addModel(new Wall(sIF, wallMatl, wallWest, wallWestU, 5.0, 6.0)); 
	c.addModel(new Wall(sIF, trimMatl, baseboardWest, wallWestU, 0.3, 6.0));
	c.addModel(new Wall(sIF, trimMatl, mouldingWest, wallWestU, 0.3, 6.0));  

	c.addModel(new Wall(sIF, wallMatl, wallEast, wallEastU, 5.0, 6.0)); 
	c.addModel(new Wall(sIF, trimMatl, baseboardEast, wallEastU, 0.3, 6.0)); 
	c.addModel(new Wall(sIF, trimMatl, mouldingEast, wallEastU, 0.3, 6.0)); 	
	
	c.addModel(new Wall(sIF, wallMatl, wallNorth, wallNorthU, 5.0, 6.0)); 
	c.addModel(new Wall(sIF, trimMatl, baseboardNorth, wallNorthU, 0.3, 6.0)); 	
	c.addModel(new Wall(sIF, trimMatl, mouldingNorth, wallNorthU, 0.3, 6.0)); 

	Wall *tv = new Wall(sIF, tvMatl, television, wallNorthU, 1.3, 2.0);
	tv->setTextureImage("images/images.jpeg");
	c.addModel(tv);	

	c.addModel(new Floor(sIF, floorMatl, -3.0, 3.0, -3.0, 3.0));
}

void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);

	double maxDelta = xyz[1] - xyz[0];
	double delta = xyz[3] - xyz[2];
	if (delta > maxDelta)
		maxDelta = delta;
	delta = xyz[5] - xyz[4];
	if (delta > maxDelta)
		maxDelta = delta;
	double xmid = 0.5 * (xyz[0] + xyz[1]);
	double ymid = 0.5 * (xyz[2] + xyz[3]);
	double zmid = 0.5 * (xyz[4] + xyz[5]);

	// Set values for eye-center-up to produce a reasonable off-axis
	// view of your scene:
	cryph::AffPoint center(xmid, ymid, zmid);
	
	double distEyeCenter = 2.0 * maxDelta;
	cryph::AffPoint eye(xmid, ymid, zmid + distEyeCenter);
	
	cryph::AffVector up = cryph::AffVector::yu;

	ModelView::setEyeCenterUp(eye, center, up);

	// Set values for ecZpp, ecZmin, ecZmax that make sense in the context of
	// the EC system established above:
	double ecZpp, ecZmin, ecZmax;

	ecZpp = -(distEyeCenter - 0.5*maxDelta);
	ecZmin = ecZpp - (2 * maxDelta);
	ecZmax = ecZpp + 0.5*maxDelta;

	// Notify the ModelView of our MC->EC viewing requests:
	ModelView::setProjection(PERSPECTIVE);
	ModelView::setProjectionPlaneZ(ecZpp);
	ModelView::setECZminZmax(ecZmin, ecZmax);
}

int main(int argc, char* argv[])
{
	GLFWController_Subclass c("A Living Room", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	static ShaderIF::ShaderSpec vertexShader = {"shaders/basic.vsh",  GL_VERTEX_SHADER};
	static ShaderIF::ShaderSpec fragmentShader = {"shaders/phong.fsh",  GL_FRAGMENT_SHADER};
	static ShaderIF::ShaderSpec geometryShader = {"shaders/room.gsh",  GL_GEOMETRY_SHADER};

	ShaderIF::ShaderSpec shaders [3] = {vertexShader, geometryShader, fragmentShader};
	ShaderIF* sIF = new ShaderIF(shaders, 3);
	// ShaderIF* sIF = new ShaderIF("shaders/basic.vsh", "shaders/phong.fsh");
	c.recordShader(sIF);

	roomStructure(c, sIF);
	addCouches(c, sIF);
	addTables(c, sIF);
	addBookshelf(c, sIF);
	addFireplace(c, sIF);
	// addSky(c, sIF);

	glClearColor(0.0, 0.0, 0.0, 1.0);

	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	c.run();

	delete sIF;

	return 0;
}
