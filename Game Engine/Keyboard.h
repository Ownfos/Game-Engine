/*
-handles keyboard input

-System calls updateKeyState() every frame.

-to get key state, use ketState[virtual key code].
-alphabets : 'A'
-arrow key : VK_LEFT
-space : VK_SPACE
-tab : VK_TAB
-go to msdn document for complete virtual key table
*/
#pragma once

#include <Windows.h>

namespace engine {

	enum KeyState {
		Unpressed,
		Pressed,
		Pressing,
		Released
	};

	class Keyboard {
	public:
		static void updateKeyState();

		static KeyState keyState[256];
	private:
		static void checkKeyState(int key);

		static int previousKeyState[256];

	};

}
