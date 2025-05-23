// Copyright (c) 2025 F�lix-Olivier Dumas. All rights reserved.
// Licensed under the MIT License. See LICENSE for details.

#pragma once
#include "core/Config.h"
#include "input/InputManager.h"
#include "simulation/SimulationManager.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <core/FramerateManager.h>
#include <tools/Timer.h>
#include <vector>
#include "Shader.h"


class RenderEngine {
	private:
		GLFWwindow* _window;
		const GLFWvidmode *_currentVideoMode;

		Config _configuration;
		InputManager _inputManager;
		SimulationManager _simulationManager;

		Timer _runtimeTimer;
		FramerateManager _framerateManager;

		//Shader _shader;

	public:
		RenderEngine(const Config& config, SimulationManager simulationManager) : _configuration(config), _simulationManager(simulationManager), _window(nullptr) {}
		static void framebufferSizeCallback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
		void initializeComponents();

		
		void initializeGLFWWindowSettings()				 { initializeGLFW(); initializeWindow(); };
			 void initializeWindow()					 { _window = glfwCreateWindow(_configuration.getResolution().getWidth(), _configuration.getResolution().getHeight(), "OpenGL Window", nullptr, nullptr); }
			 bool initializeGLFW()						 { return glfwInit(); }

		void initializeRuntimeComponents()				 { startExecutionTimer(); };
			 void startExecutionTimer()					 { _runtimeTimer.start(); }

		void showStartupInfo()							 { displayHardwareInfo(); }
			 void displayHardwareInfo()					 { _configuration.displayHardwareInfo(); }

			 void initializeRenderSettings() { setCurrentContext(); gladLoadOpenGLFunctions(); setCurrentVideoMode(); applyVSyncSetting(false); setOpenGLRenderSettings(); }
			 void setCurrentContext()					 { glfwMakeContextCurrent(_window); }
			 void setCurrentVideoMode()					 { _currentVideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor()); }
			 void gladLoadOpenGLFunctions()				 { gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); }
			 void applyVSyncSetting(bool enabled = true) { glfwSwapInterval(enabled ? 1 : 0); }
			 void setOpenGLRenderSettings();

		void configureGLFWWindowSettings()				 { setFramebufferCallback(); initializeUserPointer(); setGLFWWindowHints(); };
			 void setFramebufferCallback()				 { glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback); }
			 void initializeUserPointer()				 { glfwSetWindowUserPointer(_window, &_inputManager); }
			 void setGLFWWindowHints();

		void terminateExecution()						 { endExecutionTimer(); destroyWindowAndTerminate(); }
			 void endExecutionTimer()		             { _runtimeTimer.stop(); };
			 void destroyWindowAndTerminate()		     { glfwDestroyWindow(_window); glfwTerminate(); }

			 void handleRenderCycle()					 { processWindowMessages();  swapBuffers(); updateSimulation(); }
			 void swapBuffers()							 { glfwSwapBuffers(_window); }
			 void updateSimulation()					 { _simulationManager.update(); }
			 void processWindowMessages()				 { glfwPollEvents(); }
			 void renderShaderFrame();

			 

			 
		/* Temporary functions for transition purpose */
		GLFWwindow* temporaryWindowGetter() { return _window; };
		FramerateManager temporaryFramerateManagerGetter() { return _framerateManager; };
		void temporarySwapBufferCall() { glfwSwapBuffers(_window); glfwPollEvents(); };
		double_t temporaryGetDeltaTime() { return _simulationManager.getDeltaTime(); };
		GLfloat temporaryGetSimulationSpeed() { return _simulationManager.getSimulationSpeed(); };


		void update();
		void renderFrame();
		void processInput();
};