/*
#include "System.h"

namespace engine {

	Vector System::mousePosition;
	double System::fps;
	double System::deltaTime;
	long long System::previousTime;
	long long System::currentTime;
	long long System::accumulator;
	int System::maxIteration;
	void* System::font;
	int System::windowWidth;
	int System::windowHeight;
	int System::viewWidth;
	int System::viewHeight;
	double System::fovy;
	double System::aspect;
	double System::cameraAngle;
	Vector System::cameraPosition;

	void System::display() {
		currentTime = Clock::getCurrentTime();
		accumulator += currentTime - previousTime;
		previousTime = currentTime;
		if (accumulator > deltaTime*maxIteration)
			accumulator = deltaTime * maxIteration;
		while (accumulator >= deltaTime) {
			for (int i = 0; i < Object::objects.size(); i++) {
				Object* object1 = Object::objects[i];
				for (int j = i + 1; j < Object::objects.size(); j++) {
					Object* object2 = Object::objects[j];
					if (Collision::isColliding(object1, object2)) {
						object1->collisionEvent(object2);
						object2->collisionEvent(object1);
					}
				}
				object1->stepEvent();
			}

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, windowWidth, windowHeight);
			gluPerspective(fovy, aspect, 1, 100);
			gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, cameraPosition.x, cameraPosition.y, 0, 0, 1, 0);
			glRotated(cameraAngle, 0, 0, 1);
			glMatrixMode(GL_MODELVIEW);

			glClear(GL_COLOR_BUFFER_BIT);
			for (Object* object : Object::objects) {
				object->drawEvent();
			}
			glutSwapBuffers();
			accumulator -= deltaTime;
		}
	}

	void System::mouse(int button, int state, int x, int y) {
		ClickState clickState = NotPressed;
		if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN) clickState = LeftPressed;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) clickState = LeftReleased;
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) clickState = RightPressed;
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) clickState = RightReleased;
		if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) clickState = MiddlePressed;
		if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) clickState = MiddleReleased;
		if (clickState != NotPressed) {
			for (Object* object : Object::objects) {
				object->clickEvent(clickState);
			}
		}
	}

	void System::motion(int x, int y) {
		mousePosition.x = (x / windowWidth - 0.5)*viewWidth;
		mousePosition.y = (0.5 - y / windowHeight)*viewHeight;
		mousePosition.rotate(-cameraAngle);
	}

	void System::reshape(int width, int height) {
		if (height == 0)
			height = 1;
		windowWidth = width;
		windowHeight = width;
		aspect = (double)width / height;
		viewHeight = cameraPosition.z * tan(radian(fovy / 2)) * 2;
		viewWidth = viewHeight * aspect;
	}

	void System::start() {
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(windowWidth, windowHeight);
		glutCreateWindow("");

		glutDisplayFunc(display);
		glutIdleFunc(display);
		glutMouseFunc(mouse);
		glutMotionFunc(motion);
		glutPassiveMotionFunc(motion);
		glutReshapeFunc(reshape);

		glutMainLoop();

		accumulator = 0;
		previousTime = Clock::getCurrentTime();
	}

	void System::setPerspective() {
	}

	void System::setFps(double fps) {
		fps = fps;
		deltaTime = 1000 / fps;
	}

	void System::setFovy(double fovy) {
		System::fovy = fovy;
	}

	void System::setFont(void* font) {
		System::font = font;
	}

	void System::setWindowSize(int width, int height) {
		windowWidth = width;
		windowHeight = height;
	}

	void System::setCameraAngle(double angle) {
		cameraAngle = angle;
	}

	void System::setCameraPosition(double x, double y, double z) {
		cameraPosition.x = x;
		cameraPosition.y = y;
		cameraPosition.z = z;
		setPerspective();
	}

	template<typename ...Args>
	void System::drawText(double x, double y, const char* format, Args... args) {
		std::string string;
		char buffer[256];
		int len = sprintf_s(buffer, format, args...);
		for (int i = 0; i < len; i++)
			string += buf[i];
		glRotated(-cameraAngle, 0, 0, 1);
		glRasterPos2d(x, y);
		for (int i = 0; i < string.length(); i++)
			glutBitmapCharacter(font, string[i]);
		glRotated(cameraAngle, 0, 0, 1);
	}

	template<typename T, typename... Args>
	T* System::createInstance(Args... args) {
		T* instance = new T(args...);
		instance->createEvent();
		return instance;
	}

}
*/