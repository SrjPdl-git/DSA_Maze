#pragma once

#include "Shader.h"
#include "Window.h"
#include "Camera2D.h"
#include "MazeGenerator.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include<glm/ext/matrix_transform.hpp>

class Application
{
	private:
		const int WINDOW_WIDTH;
		const int WINDOW_HEIGHT;
		const glm::vec2 WINDOW_POSITION;
		Window window;
		Shader shader;
		glm::mat4 projection;

		int32_t graphWidthSlider;
		int32_t graphHeightSlider;

		int32_t graphWidth;
		int32_t graphHeight;
		int32_t oldGraphHeight;
		int32_t renderingSpeed; // controls the speed at which maze generated is rendered
		bool isGeneratePressed; 

	private:
		void guiSetup();


	private:
		void setup();

		Application();

	public:
		Application(const Application& ) = delete;
		static Application& Get();
		void update();
		~Application();


};

