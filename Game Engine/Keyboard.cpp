#include "Keyboard.h"

namespace engine {

	KeyState Keyboard::keyState[256];
	int Keyboard::previousKeyState[256] = { 0 };

	void Keyboard::checkKeyState(int key) {
		int result = GetAsyncKeyState(key);
		if (!previousKeyState[key] && !result) keyState[key] = Unpressed;
		if (!previousKeyState[key] && result) keyState[key] = Pressed;
		if (previousKeyState[key] && result) keyState[key] = Pressing;
		if (previousKeyState[key] && !result) keyState[key] = Released;
		previousKeyState[key] = result;
	}

	void Keyboard::updateKeyState() {
		for (int i = 0; i < 256; i++) {
			checkKeyState(i);
		}
	}

}