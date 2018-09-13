/*
-the base class of all game objects.

-every objects has its own id(starts from 0 and +1 for each Object instance created)
-use engine::Object::getObjectById(id) to get specific instance with id

-each game object classes may have their own _type.
 use engine::Object::getObjectsByType(type) to get all instances with specific type
 if you don't set it, it will be UNDEFINED by default.

-call destroy() to delete this instance

-every object should be created using engine::System::createInstance<type>(parameters)

-drawSelf() is a defalut drawing function.
-it draws its shape at its position rotated by its angle

-_angle is in degree, not radian.

-if _checkCollision is false, system will skip its collision check phase.
*/
#pragma once

#include <vector>
#include <algorithm>

#include "Vector.h"
#include "Shape.h"

#define UNDEFINED -99999

namespace engine {

	enum ClickState {
		NotPressed,
		LeftPressed,
		LeftReleased,
		RightPressed,
		RightReleased,
		MiddlePressed,
		MiddleReleased
	};

	class Object {
	protected:
		Object();
		~Object();
	public:
		virtual void createEvent();
		virtual void destroyEvent();
		virtual void clickEvent(ClickState clickState);
		virtual void drawEvent();
		virtual void drawStaticEvent();
		virtual void stepEvent();
		virtual void collisionEvent(Object* other);
		int getId();
		void destroy();
		void drawSelf();
		bool isInside(Vector position);
		static Object* getObjectById(int id);
		static std::vector<Object*> getObjectsByType(int type);

		Shape* _shape;
		Vector _position;
		double _angle;
		bool _isPersistent;
		bool _checkCollision;
		int _type;
		static std::vector<Object*> objects;
	private:
		static int getNextId();

		int _id;
		static int _idCounter;
	};

}
