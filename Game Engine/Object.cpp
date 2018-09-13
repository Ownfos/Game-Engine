

#include "Object.h"

namespace engine {

	int Object::_idCounter = 0;
	std::vector<Object*> Object::objects;

	Object::Object() {
		_isPersistent = false;
		_checkCollision = true;
		_id = getNextId();
		_type = UNDEFINED;
	}

	Object::~Object() {
		destroy();
	}

	//default events
	void Object::createEvent() {

	}

	void Object::destroyEvent() {

	}

	void Object::clickEvent(ClickState clickState) {

	}

	void Object::drawEvent() {

	}

	void Object::drawStaticEvent() {

	}

	void Object::stepEvent() {

	}

	void Object::collisionEvent(Object* other) {

	}

	bool Object::isInside(Vector position) {
		return _shape->isInside((position - _position).rotated(-_angle));
	}

	int Object::getId() {
		return _id;
	}

	void Object::destroy() {
		auto it = std::find(objects.begin(), objects.end(), this);
		if (it != objects.end())
			objects.erase(it);
		destroyEvent();
	}

	void Object::drawSelf() {
		glLoadIdentity();
		glTranslated(_position.x, _position.y, _position.z);
		glRotated(_angle, 0, 0, 1);
		_shape->draw(false);
	}

	Object* Object::getObjectById(int id) {
		auto it = std::find_if(objects.begin(), objects.end(), [id](Object * object)->bool {
			return object->_id == id;
		});
		if (it != objects.end())
			return *it;
		else
			return nullptr;
	}

	std::vector<Object*> Object::getObjectsByType(int type) {
		std::vector<Object*> rtn;
		for (int i = 0; i < objects.size(); i++)
			if (objects[i]->_type == type)
				rtn.push_back(objects[i]);
		return rtn;
	}

	int Object::getNextId() {
		return _idCounter++;
	}

}