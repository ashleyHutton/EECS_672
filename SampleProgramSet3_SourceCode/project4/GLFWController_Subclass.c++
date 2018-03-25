// GLFWController_Subclass

#include "GLFWController_Subclass.h"
#include "ModelView.h"

GLFWController_Subclass::~GLFWController_Subclass() {}

void GLFWController_Subclass::handleDisplay(){
	if (theWindow == nullptr)
		return;
	glfwMakeContextCurrent(theWindow);
	int width, height;
	glfwGetFramebufferSize(theWindow, &width, &height);
	glViewport(0, 0, width, height);

	// clear the frame buffer
	glClear(glClearFlags);

	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // glClear(glClearFlags);
	glUseProgram(shaderIF->getShaderPgmID());
	glUniform1i(shaderIF->ppuLoc("sceneHasTranslucentObjects"), 1);

	// draw opaque objects
	glDisable(GL_BLEND);
	glUniform1i(shaderIF->ppuLoc("drawingOpaqueObjects"), 1);
	drawAllObjects();

	// draw translucent objects
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glUniform1i(shaderIF->ppuLoc("drawingOpaqueObjects"), 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawAllObjects();

	glfwSwapBuffers(theWindow);

	checkForErrors(std::cout, "GLFWController::handleDisplay");
}

void GLFWController_Subclass::drawAllObjects(){
	// draw the collection of models
	for (std::vector<ModelView*>::iterator it=models.begin() ; it<models.end() ; it++)
		(*it)->render();
}

void GLFWController_Subclass::recordShader(ShaderIF* sIF){
	shaderIF = sIF;
}