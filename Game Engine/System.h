/*
-the core engine of the game. it controls fps, renders scene, gets keyboard input, checks mouse click, checks collision, etc...

-every event function of an object is called here

-for now, glClearColor is called at start() function. go there to change it.

-viewWidth is the whole width of view in game size.
 so the left edge of the window to the right edge is the viewWidth.
 however, mousePositionStatic starts from -viewWidth/2 and ends with viewWidth/2.
*/
#pragma once

#include <string>
#include <iostream>

#include "Vector.h"
#include "Clock.h"
#include "Object.h"
#include "Scene.h"
#include "Collision.h"
#include "Radian.h"
#include "Keyboard.h"
#include "Random.h"
#include "Color.h"
#include "Circle.h"
#include "Polygon.h"

namespace engine {

	class System {
	public:
		static void start();
		static void setFps(double fps);
		static void setMaxIteration(int iteration);
		static void setFovy(double fovy);
		static void setFont(void* font);
		static void setWindowSize(int width, int height);
		static void setCameraAngle(double angle);
		static void setCameraHeight(double z);
		static void setCameraPosition(double x, double y);
		static void setCameraPosition(double x, double y, double z);
		static void setStartScene(Scene* scene);
		static void loadScene(Scene* scene);
		static double getDirection(Vector from, Vector to);
		static int getFpsReal();
		template<typename ...Args>
		static void drawText(double x, double y, bool isStatic, const char* format, Args... args);
		template<typename T, typename... Args>
		static T* createInstance(Args... args);

		static Vector mousePosition;
		static Vector mousePositionStatic;
	private:
		static void display();
		static void mouse(int button, int state, int x, int y);
		static void motion(int x, int y);
		static void reshape(int width, int height);
		template<typename ...Args>
		static std::string getString(const char* format, Args... args);

		static double fps;
		static double deltaTime;
		static long long previousFpsCheckTime;
		static long long previousTime;
		static long long currentTime;
		static long long accumulator;
		static int maxIteration;
		static int frames;
		static int fpsReal;
		static void* font;
		static double windowWidth;
		static double windowHeight;
		static double viewWidth;
		static double viewHeight;
		static double fovy;
		static double aspect;
		static double cameraAngle;
		static Vector cameraPosition;
		static Scene* startScene;
		static Scene* prepareScene;
	};

}

#include "System.hpp"