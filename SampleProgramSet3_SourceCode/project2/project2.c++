// project2.c++
// Author: Ashley Hutton
// Date: 10-20-17

#include "GLFWController.h"
#include "Couch.h"
#include "Floor.h"
#include "Wall.h"
#include "Table.h"
#include "Book.h"
#include "Bookshelf.h"
#include "Lamp.h"

void addCouches(Controller& c, ShaderIF* sIF){

	cryph::AffPoint p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13;

	// COUCH #1 - Faces east wall

	float xmin = -2.5; float xmax = -1.4; float ymin = -1.4; float ymax = 1.2;

	// if you are facing the back of the couch:
	p0.assign(xmin, ymax, 0.0); // bottom left corner
	p1.assign(xmin, ymax, 1.0); // top left corner
	p2.assign(xmin, ymin, 0.0); // bottom right corner
	p3.assign(xmin, ymin, 1.0); // top right corner
	// looking at side of couch
	p4.assign(xmin+0.5, ymin, 0.0); // mid right bottom
	// birdseye
	p5.assign(xmin+0.5, ymin, 1.0); // top right corner of back of couch
	p6.assign(xmin+0.5, ymax, 1.0); // top left corner of back of couch
	// sitting on couch
	p7.assign(xmin+0.5, ymin, 0.5); // right back corner
	p8.assign(xmin+0.5, ymax, 0.5); // left back corner
	// looking at side of couch
	p9.assign(xmin+0.5, ymin, 0.0); // mid left bottom
	// sitting on couch
	p10.assign(xmax, ymax, 0.5); // left front top corner
	p11.assign(xmax, ymax, 0.0); // left front bottom corner
	p12.assign(xmax, ymin, 0.5); // right front top corner
	p13.assign(xmax, ymin, 0.0); // right front bottom corner

	cryph::AffPoint vertices[] = { p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 };
	c.addModel(new Couch(sIF, vertices, 0.5, 0.5, 0.6));

	// COUCH #2 - Faces west wall

	xmin = 1.5; xmax = 2.5; ymin = -1.4; ymax = 1.2;

	// if you are facing the back of the couch:
	p0.assign(xmax, ymin, 0.0); // bottom left corner
	p1.assign(xmax, ymin, 1.0); // top left corner
	p2.assign(xmax, ymax, 0.0); // bottom right corner
	p3.assign(xmax, ymax, 1.0); // top right corner
	// looking at side of couch
	p4.assign(xmax-0.5, ymax, 0.0); // mid right bottom				
	// birdseye
	p5.assign(xmax-0.5, ymax, 1.0); // top right corner of back of couch 	
	p6.assign(xmax-0.5, ymin, 1.0); // top left corner of back of couch 	
	// sitting on couch
	p7.assign(xmax-0.5, ymax, 0.5); // right back corner				
	p8.assign(xmax-0.5, ymin, 0.5); // left back corner				
	// looking at side of couch
	p9.assign(xmax-0.5, ymin, 0.0); // mid left bottom				
	// sitting on couch
	p10.assign(xmin, ymin, 0.5); // left front top corner			
	p11.assign(xmin, ymin, 0.0); // left front bottom corner 		
	p12.assign(xmin, ymax, 0.5); // right front top corner		
	p13.assign(xmin, ymax, 0.0); // right front bottom corner		

	cryph::AffPoint vertices2[] = { p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13 };
	c.addModel(new Couch(sIF, vertices2, 0.5, 0.5, 0.6));

}

void addLamp(Controller& c, ShaderIF* sIF, float cx, float cy, float zmin) {
	// Lamp::Lamp(ShaderIF* sIF, float topHeight, float legHeight, float topRadius, float zmin,
	// 	float cx, float cy, float R, float G, float B) : shaderIF(sIF)

	float lampHeight = 1.5;
	float shadeHeight = 0.4;

	c.addModel(new Lamp(sIF, shadeHeight, lampHeight, 0.2, zmin, cx, cy, 0.3, 0.3, 0.7));
}

void addTables(Controller& c, ShaderIF* sIF) {

	// ShaderIF* sIF, float topHeight, float legHeight, float topRadius, 
	// float cx, float cy, float R, float G, float B) : shaderIF(sIF)

	float topHeight = 0.2;
	float legHeight = 0.5;

	float topRadius; float cx; float cy;

	// Table #1 - big coffee table
	topRadius = 0.7;
	cx = 0.0;
	cy = -0.5;
	c.addModel(new Table(sIF, topHeight, legHeight, topRadius, cx, cy, 1.0, 1.0, 1.0));
	c.addModel(new Book(sIF, cx-0.2, cy+0.2, legHeight+topHeight, 0.1, 0.2, 0.3, 0.0, 0.0, 1.0));
	
	// Table #2 - small end table lhs
	topRadius = 0.4;
	cx = -2.0;
	cy = -2.2;
	c.addModel(new Table(sIF, topHeight, legHeight, topRadius, cx, cy, 1.0, 1.0, 1.0));
	addLamp(c, sIF, cx, cy, topHeight+legHeight);

	// Table #3 - small end table rhs
	topRadius = 0.4;
	cx = 2.0;
	cy = -2.2;
	c.addModel(new Table(sIF, topHeight, legHeight, topRadius, cx, cy, 1.0, 1.0, 1.0));
	addLamp(c, sIF, cx, cy, topHeight+legHeight);
}

void addBookshelf(Controller& c, ShaderIF* sIF) {
	float shelfHeight = 3.0;
	float shelfWidth = 1.3;
	float shelfDepth = 0.5;
	float cx1 = 1.5; float cx2 = -2.8; float cy = 2.5; float cz = 0.0;
	c.addModel(new Bookshelf(sIF, cx1, cy, cz, shelfHeight, shelfWidth, shelfDepth, 0.8, 0.8, 0.8));
	c.addModel(new Bookshelf(sIF, cx2, cy, cz, shelfHeight, shelfWidth, shelfDepth, 0.8, 0.8, 0.8));

	float shelf0Height = shelfHeight * 0.06;
	float shelf1Height = (shelfHeight / 4) + (shelfHeight * 0.03);
	float shelf2Height = (shelfHeight / 2) + (shelfHeight * 0.03);
	float shelf3Height = (shelfHeight * (3.0/4.0)) + (shelfHeight * 0.03);

	double bookDepth[10] = {0.3, 0.2, 0.4, 0.35, 0.24, 0.45, 0.3, 0.23, 0.38, 0.35};
	double bookHeight[10] = {0.65, 0.6, 0.65, 0.47, 0.6, 0.5, 0.55, 0.5, 0.62, 0.4};
	double bookWidth[10] = {0.13, 0.1, 0.14, 0.12, 0.16, 0.11, 0.13, 0.14, 0.12, 0.13};
	double R[10] = {0.3, 0.1, 0.8, 1.0, .2, 0.7, 0.8, 0.9, 0.1, 0.4};
	double G[10] = {0.8, 1.0, .2, 0.7, 0.8, 0.9, 0.1, 0.4, 0.3, 0.1};
	double B[10] = {1.0, .2, 0.7, 0.8, 0.3, 0.1, 0.8, 0.9, 0.1, 0.4};

	float bookcase1;
	float bookcase2;

	for (int i=6; i>=0; i--){
		if (i==6){ bookcase1 = cx1 + 0.01; bookcase2 = cx2 + 0.01;}
		else { bookcase1 += bookWidth[i+1] + 0.05; bookcase2 += bookWidth[i+1] + 0.05;}
		c.addModel(new Book(sIF, bookcase1, cy, shelf0Height, bookHeight[i]-0.1, bookWidth[i]+0.05, bookDepth[i], R[i]-0.1, G[i]-0.1, B[i]-0.1));
		c.addModel(new Book(sIF, bookcase2, cy, shelf1Height, bookHeight[i]-0.1, bookWidth[i]+0.05, bookDepth[i], R[i]-0.1, G[i]-0.1, B[i]-0.1));
	}
	for (int i=0; i<10; i++){
		if (i==0){ bookcase1 = cx1 + 0.01; bookcase2 = cx2 + 0.01;}
		else { bookcase1 += bookWidth[i-1]; bookcase2 += bookWidth[i-1];}
		c.addModel(new Book(sIF, bookcase1, cy, shelf1Height, bookHeight[i], bookWidth[i], bookDepth[i], R[i], G[i], B[i]));
		c.addModel(new Book(sIF, bookcase2, cy, shelf3Height, bookHeight[i], bookWidth[i], bookDepth[i], R[i], G[i], B[i]));

	}
	for (int i=9; i>=0; i--){
		if (i==9){ bookcase1 = cx1 + 0.01; bookcase2 = cx2 + 0.01;}
		else { bookcase1 += bookWidth[i+1]; bookcase2 += bookWidth[i+1];}
		c.addModel(new Book(sIF, bookcase1, cy, shelf2Height, bookHeight[i], bookWidth[i], bookDepth[i], R[i], G[i], B[i]));
		c.addModel(new Book(sIF, bookcase2, cy, shelf0Height, bookHeight[i], bookWidth[i], bookDepth[i], R[i], G[i], B[i]));
	}
	for (int i=0; i<7; i++){
		if (i==0){ bookcase1 = cx1 + 0.01; bookcase2 = cx2 + 0.01;}
		else { bookcase1 += bookWidth[i-1] + 0.05; bookcase2 += bookWidth[i-1] + 0.05;}
		c.addModel(new Book(sIF, bookcase1, cy, shelf3Height, bookHeight[i], bookWidth[i]+0.05, bookDepth[i], R[i]-0.1, G[i]-0.1, B[i]-0.1));
		c.addModel(new Book(sIF, bookcase2, cy, shelf2Height, bookHeight[i], bookWidth[i]+0.05, bookDepth[i], R[i]-0.1, G[i]-0.1, B[i]-0.1));
	}
}

void roomStructure(Controller& c, ShaderIF* sIF) {

	c.addModel(new Floor(sIF, -3.0, 3.0, -3.0, 3.0));

	float R = 0.5; float G = 0.6; float B = 0.8;

	c.addModel(new Wall(sIF, -3.0, 3.0, 3.0, 3.0, 0.0, 5.0, R, G, B)); // north wall
	c.addModel(new Wall(sIF, -3.0, 3.0, 2.9, 2.9, 0.0, 0.3, 1.0, 1.0, 1.0)); // north baseboard
	c.addModel(new Wall(sIF, -3.0, 3.0, 2.9, 2.9, 4.7, 5.1, 1.0, 1.0, 1.0)); // north crown moulding

	c.addModel(new Wall(sIF, -3.0, -3.0, -3.0, 3.0, 0.0, 5.0, R, G, B)); // west wall
	c.addModel(new Wall(sIF, -2.95, -2.95, -3.0, 3.0, 0.0, 0.3, 1.0, 1.0, 1.0)); // west baseboard
	c.addModel(new Wall(sIF, -2.95, -2.95, -3.0, 3.0, 4.7, 5.1, 1.0, 1.0, 1.0)); // west crown moulding

	c.addModel(new Wall(sIF, -1.0, 1.0, 2.95, 2.95, 2.2, 3.5, 0.0, 0.0, 0.0)); // television -- not a wall but it's the same idea
	c.addModel(new Wall(sIF, -0.9, 0.9, 2.9, 2.9, 2.35, 3.4, 0.2, 0.2, 0.2)); // television -- not a wall but it's the same idea
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
	cryph::AffPoint center(xmid - (xmid / 2), ymid, zmid);
	
	double distEyeCenter = 2.0 * maxDelta;
	cryph::AffPoint eye(xmid - (xmid / 2), 3 * xyz[2], zmid + distEyeCenter);
	
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
	GLFWController c("A Living Room", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	ShaderIF* sIF = new ShaderIF("shaders/basic.vsh", "shaders/phong.fsh");

	// create your scene, adding things to the Controller....
	roomStructure(c, sIF);
	addCouches(c, sIF);
	addTables(c, sIF);
	addBookshelf(c, sIF);

	glClearColor(1.0, 1.0, 1.0, 1.0);

	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	c.run();

	delete sIF;

	return 0;
}
