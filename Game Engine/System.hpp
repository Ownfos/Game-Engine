#include "System.h"

namespace engine {

	Vector System::mousePosition;
	Vector System::mousePositionStatic;
	double System::fps;
	double System::deltaTime;
	long long System::previousFpsCheckTime;
	long long System::previousTime;
	long long System::currentTime;
	long long System::accumulator = 0;
	int System::maxIteration = 20;
	int System::frames = 0;
	int System::fpsReal = 0;
	void* System::font;
	double System::windowWidth;
	double System::windowHeight;
	double System::viewWidth;
	double System::viewHeight;
	double System::fovy;
	double System::aspect;
	double System::cameraAngle = 0;
	Vector System::cameraPosition;
	Scene* System::startScene = nullptr;
	Scene* System::prepareScene = nullptr;

	void System::display() {
		currentTime = Clock::getCurrentTime();
		accumulator += currentTime - previousTime;
		previousTime = currentTime;
		if (accumulator > deltaTime*maxIteration) {
			accumulator = deltaTime * maxIteration;
		}
		if (currentTime - previousFpsCheckTime > 1000000) {
			previousFpsCheckTime = currentTime;
			fpsReal = frames;
			frames = 0;
			//std::cout << "fps : " << fpsReal << std::endl;
		}
		while (accumulator >= deltaTime) {
			//keyboard
			Keyboard::updateKeyState();
			//collision and step
			int size = Object::objects.size();
			for (int i = 0; i < size; i++) {
				Object* object1 = Object::objects[i];
				object1->stepEvent();
				if (object1->_checkCollision == false)
					continue;
				for (int j = i + 1; j < size; j++) {
					Object* object2 = Object::objects[j];
					if (object2->_checkCollision == false)
						continue;
					if (Collision::isColliding(object1, object2)) {
						object1->collisionEvent(object2);
						object2->collisionEvent(object1);
					}
				}
				if (prepareScene != nullptr)
					break;
			}
			//load scene
			if (prepareScene != nullptr) {
				for (Object* object : Object::objects) {
					if (!object->_isPersistent) {
						object->destroy();
					}
				}
				prepareScene->load();
				prepareScene = nullptr;
				break;
			}


			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, windowWidth, windowHeight);
			gluPerspective(fovy, aspect, 1, 100);
			glRotated(cameraAngle, 0, 0, 1);
			gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, cameraPosition.x, cameraPosition.y, 0, 0, 1, 0);
			glClear(GL_COLOR_BUFFER_BIT);
			glMatrixMode(GL_MODELVIEW);

			//draw
			for (Object* object : Object::objects) {
				object->drawEvent();
			}
			//draw static
			glLoadIdentity();
			glTranslated(cameraPosition.x, cameraPosition.y, 0);
			glRotated(-cameraAngle, 0, 0, 1);
			for (Object* object : Object::objects) {
				object->drawStaticEvent();
			}

			glutSwapBuffers();
			accumulator -= deltaTime;
			frames++;
		}
	}

	void System::mouse(int button, int state, int x, int y) {
		ClickState clickState = NotPressed;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) clickState = LeftPressed;
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
		//static mouse position(-viewWidth ~ viewWidth, -viewHeight ~ viewHeight)
		mousePositionStatic.x = (x / windowWidth - 0.5)*viewWidth;
		mousePositionStatic.y = (0.5 - y / windowHeight)*viewHeight;
		//non static mouse position
		mousePosition = mousePositionStatic;
		mousePosition.rotate(-cameraAngle);
		mousePosition.x += cameraPosition.x;
		mousePosition.y += cameraPosition.y;
	}

	void System::reshape(int width, int height) {
		if (height == 0)
			height = 1;
		windowWidth = width;
		windowHeight = width;
		aspect = (double)width / height;
		viewHeight = cameraPosition.z * tan(radian(fovy / 2)) * 2;
		viewWidth = viewHeight * aspect;
		std::cout << viewWidth << ", " << viewHeight << std::endl;
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

		glClearColor(1, 1, 1, 1);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glPointSize(4);

		previousTime = Clock::getCurrentTime();
		previousFpsCheckTime = Clock::getCurrentTime();

		Random::randomize();

		startScene->load();

		glutMainLoop();

	}

	void System::setFps(double fps) {
		fps = fps;
		deltaTime = 1000000 / fps;
	}

	void System::setMaxIteration(int iteration) {
		maxIteration = iteration;
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

	void System::setCameraHeight(double z) {
		cameraPosition.z = z;
	}

	void System::setCameraPosition(double x, double y) {
		cameraPosition.x = x;
		cameraPosition.y = y;
	}

	void System::setCameraPosition(double x, double y, double z) {
		cameraPosition.x = x;
		cameraPosition.y = y;
		cameraPosition.z = z;
	}

	void System::setStartScene(Scene* scene) {
		startScene = scene;
	}

	void System::loadScene(Scene* scene) {
		prepareScene = scene;
	}

	double System::getDirection(Vector from, Vector to) {
		Vector direction = to - from;
		double radian = atan2(direction.y, direction.x);
		return degree(radian);
	}

	int System::getFpsReal() {
		return fpsReal;
	}

	template<typename ...Args>
	std::string System::getString(const char* format, Args... args) {
		std::string rtn;
		char buffer[256];
		int len = sprintf_s(buffer, format, args...);
		for (int i = 0; i < len; i++)
			rtn += buffer[i];
		return rtn;
	}

	template<typename ...Args>
	void System::drawText(double x, double y, bool isStatic, const char* format, Args... args) {
		std::string string = getString(format, args...);

		glLoadIdentity();
		if (isStatic) {
			glTranslated(cameraPosition.x, cameraPosition.y, 0);
			glRotated(-cameraAngle, 0, 0, 1);
		}
		glRasterPos2d(x, y);
		for (int i = 0; i < string.length(); i++)
			glutBitmapCharacter(font, string[i]);
	}

	template<typename T, typename... Args>
	T* System::createInstance(Args... args) {
		T* instance = new T(args...);
		instance->createEvent();
		Object::objects.push_back(instance);
		return instance;
	}

}