#ifndef ENGINE_H
#define ENGINE_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "callbacks.h"

class Engine {
private:
	Engine() { };
public:
	static Engine& getInstance()
	{
		static Engine instance; // thread-safe in C++ 11
		return instance;
	}

	Engine(Engine const&)		  = delete;
	void operator=(Engine const&) = delete;

	// calls initialization, rendering, and basic setup functions 
	void run();
};

#endif
