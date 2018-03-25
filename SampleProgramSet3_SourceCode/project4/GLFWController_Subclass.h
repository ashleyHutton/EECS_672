// GLFWController_Subclass.h

#ifndef GLFWController_Subclass_H
#define GLFWController_Subclass_H

#ifdef __APPLE_CC__
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "GLFWController.h"
#include "ShaderIF.h"

class GLFWController_Subclass : public GLFWController {

	public:
	GLFWController_Subclass(const std::string& windowTitle, int rcFlags) : GLFWController(windowTitle, rcFlags) {}
	~GLFWController_Subclass();

	void handleDisplay();
	void drawAllObjects();

	void recordShader(ShaderIF* sIF);

	protected:
	ShaderIF* shaderIF;

};

#endif 