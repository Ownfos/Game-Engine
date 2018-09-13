/*
-every class in this engine is inside 'engine' namespace

-glLoadIdentity call before drawing something, not after

-all game object class should inherit engine::Object and override virtual functions
-only drawEvent() is not a pure virtual function. it draws the shape of the object with drawSelf() by default.

-all object instances should be created by engine::System::createInstance<Type>();
-or else, the instance created will not be simulated.

-to destroy and instance, call its destroy() function.

-for now, making non-square window will make everyting look stretched... 

-engine::System::drawText(...) will start from global origin if isStatic is true.
-when false, it will start from camera position and ignore camera rotation.
-note that glRotated() will not affect text itself. it only rotates the position vector where the text will be placed.

-to use this engine, include System.h
-and set some options like fps, camera position, etc...
-after you call engine::System::start(), the engine will initialize and go into opengl main loop.

-fps, cameraPosition, fovy, windowSize must be set before starting the game!
*/
#include "System.h"

#include <iostream>


class testScene :public engine::Scene {
public:
	virtual void load();
};

class testParticle1 :public engine::Object {
public:
	int maxLife;
	int life;
	double size;
	double initialSize;
	int segment;

	testParticle1(double x, double y) {
		_type = 2;
		life = 0;
		maxLife = engine::Random::irandomRange(30, 40);
		_angle = engine::Random::random(360);
		double range = 0.5;
		_position.x = x + engine::Random::randomRange(-range, range);
		_position.y = y + engine::Random::randomRange(-range, range);
		_checkCollision = false;
		segment = 4;
		initialSize = 0.4;
	}

	virtual void stepEvent() override {
		life++;
		if (life > maxLife)
			destroy();
		size = initialSize * log10(life + 1);
	}

	virtual void drawEvent() override {
		glLoadIdentity();
		glTranslated(_position.x, _position.y, 0);
		glRotated(_angle, 0, 0, 1);
		glColor4d(0, 0, 0, 0.3 - (double)life / maxLife * 0.3);
		engine::Vector point(size, 0);
		glBegin(GL_POLYGON);
		//glBegin(GL_LINE_LOOP);
		for (int i = 0; i < segment; i++) {
			glVertex2d(point.x, point.y);
			point.rotate(360 / segment);
		}
		glEnd();
	}
};

class testParticle2 :public engine::Object {
public:
	int maxLife;
	int life;
	double speed;
	engine::Vector move;
	engine::Vector initialPosition;

	testParticle2(double x, double y) {
		_type = 3;
		life = 0;
		maxLife = engine::Random::irandomRange(30, 40);
		speed = engine::Random::randomRange(1, 1.5);
		_angle = engine::Random::random(360);
		move = engine::Vector(speed, 0);
		move.rotate(_angle);
		initialPosition = engine::Vector(x, y);
		_position = initialPosition;
		_checkCollision = false;
	}

	virtual void stepEvent() override {
		life++;
		if (life > maxLife)
			destroy();
		_position = initialPosition + move * log10(life + 1);
		engine::System::createInstance<testParticle1>(_position.x, _position.y);
	}
};

class TestObject :public engine::Object {
public:
	double angle = 0;
	bool drag = false;
	double shake = 0;

	TestObject() {
		_type = 1;
	}

	virtual void createEvent() {
		std::cout << "created" << std::endl;
	}
	virtual void destroyEvent() {
		std::cout << "destroyed" << std::endl;
	}
	virtual void clickEvent(engine::ClickState clickState) {
		/*
		if (isInside(engine::System::mousePosition) && clickState == engine::LeftPressed)
			drag = true;
		if (clickState == engine::LeftReleased)
			drag = false;

		if (isInside(engine::System::mousePosition) && clickState == engine::RightPressed)
			destroy();
		//*/
		///*
		engine::Vector mouse = engine::System::mousePosition;
		if (clickState == engine::LeftPressed) {
			for(int i=0;i<10;i++)
				engine::System::createInstance<testParticle2>(mouse.x, mouse.y);
		}
		//*/
	}
	virtual void drawEvent() {
		glColor3d(0, 0, 0);
		glLoadIdentity();
		//engine::System::drawText(-5, 5, true, "real fps:%d", engine::System::getFpsReal());
		//engine::System::drawText(-5, 5, false, "real fps:%d", engine::System::getFpsReal());
		//engine::Vector ms = engine::System::mousePositionStatic;
		//engine::Vector m = engine::System::mousePosition;
		//engine::System::drawText(-5, 0, true, "mouse position static : %lf, %lf", ms.x, ms.y);
		//engine::System::drawText(-5, -1, true, "mouse position : %lf, %lf", m.x, m.y);
		engine::System::drawText(-10, -10, true, "total Objects : %d", engine::Object::objects.size());
		
		glLoadIdentity();
		engine::Vector mouse = engine::System::mousePosition;
		glBegin(GL_POINTS);
		glVertex2d(mouse.x, mouse.y);
		glEnd();

		glBegin(GL_LINES);
		glColor3d(1, 0, 0);
		glVertex2d(0, 0);
		glVertex2d(4, 0);
		glColor3d(0, 0, 1);
		glVertex2d(0, 0);
		glVertex2d(0, 4);
		glEnd();

		glColor4d(0, 0, 0, 0.5);
		drawSelf();
	}
	virtual void drawStaticEvent() {
		glBegin(GL_LINES);
		glColor3d(1, 0, 0);
		glVertex2d(0, 0);
		glVertex2d(4, 0);
		glColor3d(0, 0, 1);
		glVertex2d(0, 0);
		glVertex2d(0, 4);
		glEnd();
	}
	virtual void stepEvent() {
		///*
		_angle = engine::System::getDirection(_position, engine::System::mousePosition);
		//*/
		/*
		shake *= 0.9;
		if (shake < 0.1)
			shake = 0;

		engine::System::setCameraAngle(engine::Random::randomRange(-shake,shake)*10);
		engine::System::setCameraPosition(engine::Random::randomRange(-shake, shake), engine::Random::randomRange(-shake, shake));
		engine::System::setCameraHeight(20 + engine::Random::randomRange(-shake, shake) * 5);
		//*/

		if (drag) {
			_position = engine::System::mousePosition;
		}
		///*
		if (engine::Keyboard::keyState['A'] == engine::Pressing) {
			_position.x -= 0.001;
		}
		if (engine::Keyboard::keyState['D'] == engine::Pressing) {
			_position.x += 0.001;
		}
		if (engine::Keyboard::keyState[VK_SPACE] == engine::Released) {
			engine::System::setCameraAngle(angle);
			angle += 10;
		}
		if (engine::Keyboard::keyState['W']) {
			_position.y += 0.1;
		}
		if (engine::Keyboard::keyState['S']) {
			_position.y -= 0.1;
		}
		if (engine::Keyboard::keyState['R'] == engine::Pressed) {
			_angle += 5;
		}
		if (engine::Keyboard::keyState['Q'] == engine::Pressed) {
			//std::cout << "load scene" << std::endl;
			engine::System::loadScene(new testScene());
		}
		if (engine::Keyboard::keyState[VK_TAB]) {
			shake = 2;
		}
		switch (engine::Keyboard::keyState['P']) {
		case engine::Pressed:
			std::cout << "Pressed" << std::endl;
			break;
		case engine::Pressing:
			std::cout << "Pressing" << std::endl;
			break;
		case engine::Released:
			std::cout << "Released" << std::endl;
			break;
		}
	}
	virtual void collisionEvent(Object* other) {
		//std::cout << "collision" << std::endl;
	}
};

class TestBullet :public engine::Object {
public:
	engine::Vector speed;

	TestBullet(double x, double y) {
		_type = 4;
		_position = engine::Vector(x, y);
		_shape = new engine::Polygon(0.3, 0.3);
	}

	virtual void stepEvent() override {
		_position += speed;
	}

	virtual void collisionEvent(engine::Object* other) override {
		if (other->_type == 5) {
			for (int i = 0; i<10; i++)
				engine::System::createInstance<testParticle1>(_position.x, _position.y);
			destroy();
		}
	}

	virtual void drawEvent() override {
		glLoadIdentity();
		glColor3d(0, 0, 0);
		drawSelf();
	}
};

class TestEnemy :public engine::Object {
public:
	TestEnemy() {
		_type = 5;
	}

	virtual void clickEvent(engine::ClickState clickState) {
		if (clickState == engine::LeftPressed) {
			engine::Vector mouse = engine::System::mousePosition;
			TestBullet* b = engine::System::createInstance<TestBullet>(mouse.x, mouse.y);
			b->speed = engine::Vector(0.1, 0);
			b->_angle = engine::System::getDirection(b->_position, _position);
			b->speed.rotate(b->_angle);
		}
	}

	virtual void collisionEvent(engine::Object* other) {
		if (other->_type == 4) {
			for (int i = 0; i<10; i++)
				engine::System::createInstance<testParticle2>(_position.x, _position.y);
			destroy();
		}
	}

	virtual void drawEvent() {
		glLoadIdentity();
		glColor4d(0, 0, 0, 1);
		drawSelf();
	}
};


void testScene::load() {
	//적 쏴서 없애는 부분
	//TestEnemy* e = engine::System::createInstance<TestEnemy>();
	//o->_shape = new engine::Circle(1);
	/*
	o->_shape = new engine::Polygon({
		engine::Vector(1,0),
		engine::Vector(2,2),
		engine::Vector(0,1),
		engine::Vector(0,-1)
		});
	//*/
	//e->_shape = new engine::Polygon(2, 2);
	/*
	e->_position.x = 0;
	e->_position.y = 0;
	//o->_isPersistent = true;
	//*/

	//폭발 이펙트 테스트 부분
	///*
	TestObject* o2 = engine::System::createInstance<TestObject>();
	o2->_shape = new engine::Polygon({
		engine::Vector(0,0),
		engine::Vector(1,0),
		engine::Vector(2,2),
		engine::Vector(0,1)
		});
	//*/
	/*
	o2->_shape = new engine::Circle(1.5);
	o2->_position.x = 5;
	o2->_position.y = 2;
	o2->_angle = 60;
	//*/

	//룸 로드될 때 남을 놈 잘 남고 사라질 놈 잘 사라지는지 확인하는 부분
	//std::vector<engine::Object*> list = engine::Object::getObjectsByType(1);
	//std::cout << "number of type 1 objects : " << list.size() << std::endl;
	//std::cout << "number of total objects : " << engine::Object::objects.size() << std::endl;

	//engine::System::setCameraAngle(0);
}

int main() {
	//speed test
	/*
	std::vector<int> vec;
	for (int i = 0; i < 1000000; i++) {
		vec.push_back(i);
	}
	long long start = engine::Clock::getCurrentTime();
	int s = vec.size();
	for (int i = 0; i < vec.size();i++) {}
	for (int i = 0; i < s; i++) {}
	for (int i : vec) {}
	long long end = engine::Clock::getCurrentTime();
	std::cout << end - start << std::endl;
	//*/

	engine::Random::randomize();

	engine::System::setMaxIteration(5);
	engine::System::setFps(60);
	engine::System::setFovy(60);
	engine::System::setFont(GLUT_BITMAP_HELVETICA_12);
	engine::System::setCameraPosition(10, 7, 20);
	engine::System::setWindowSize(800, 800);
	engine::System::setStartScene(new testScene());

	engine::System::start();
}

/*
해야할 일들
-Object의 _type을 static으로 만들어서 Object::type 이런 식으로 쓰게 하자. 지금은 거의 매직 넘버급 가독성(?)을 보인다. 뭐가 뭔지 구별이 전혀 안된다.
-Object에 visible 속성을 넣자.
-drawText의 static 속성을 없애고 그냥 drawStaticEvent에서 그리게 하자. 중복되는 기능을 넣을 필요는 없어 보인다.
-void System::drawRectangle(double x1, double y1, double x2, double y2, bool isFilled) 추가
-void System::drawCirlce(double x, double y, bool isFilled) 추가
-Object Destroy()부를때 그 오브젝트를 delete해주는게 지금 없음. 방식을 System에서 호출하는걸로 바꾸거나 다른 방법을 생각해야할듯
-mouse position을 static으로도 저장해놓는게 좋을듯. 나중에 좀비오펜스같은 시점을 만들때 필요함. 윈도우 기준인지 뷰 기준인지는 고민해보자
-이미지 로딩, 애니메이션 추가. 겜스처럼 image_index랑 sprite형식으로 하면 될듯. 또 원점 설정하는것도 만들어야 함.
-오디오 로딩, 재생 추가
-빛, 그림자 효과 추가
-충돌 검사를 할지 말지 결정하는걸 넣자. 지금 너무 성능이 안좋다. 특히 폴리곤 vs 폴리곤이 완전 심각함.
 비트마스크나 단순 bool로 해보자.
 -AABB랑 OBB도 shape에 추가하자. polygon은 계산 비용이 지나치게 높은 것 같다.
 -SAT검사에서 마지막 분리축을 저장해놓는 기능을 넣자.

고민 거리
-변수랑 함수 이름이 접근하기에 너무 길다. 어떻게 하는게 좋을까?
-glClearColor나 glColor가 main함수에서 설정하면 안먹힘. 뭐가 원인인지 찾아야 하고, 사용자가 설정할 수 있는 방법을 찾아야 함.
-오브젝트 좌표의 z값을 쓸것인지 결정하자. 아마 쓰는게 좋을듯.
-Projection 에서 삼각함수를 미리 계산해서 재사용하면 빨라질 줄 알았는데 별로 차이가 없다...?
-debug모드에서는 Projection의 double projection = axis * (p->vertices[i].rotated(cos, sin));의
 std::vector::operator[]가 연산 시간의 반을 차지한다! 뭐야 이거
 정확한 값
 isColliding 72.58%
 polygonToPolygon 72.33%
 Projection 63.62%
 std::vector::operator[] 45.01%
 std::vector::size() 37.33%

현재 상황
-아무 오브젝트 없이 엔진만 돌리면 최대 3200프레임정도 나옴
-지금 가장 자원 많이 먹는게 충돌 검사임. broad phase를 아무래도 넣어야할듯.
-debug랑 release에서 충돌 검사 시간이 차이가 꽤 난다! release에서는 충돌보다 키보드 상태 가져오는게 더 오래걸린다고 나왔다.
*/