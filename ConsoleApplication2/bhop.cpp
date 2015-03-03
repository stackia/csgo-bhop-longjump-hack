#include "main.h"
#include <cstdio>

using namespace Main;

bool jumped;
int c;
POINT cp;

void bhop_tick() {
	while (true) {
		if (bhop_enabled) {
			if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && !player.in_air()) {
				if (legit_bhop_enabled) {
					Sleep(rand() % 10);
				}
				//SendMessage(window, WM_KEYDOWN, VK_SPACE, 0x390000);
				GetCursorPos(&cp);
				SendMessage(window, WM_MOUSEWHEEL, MAKEWPARAM(0, WHEEL_DELTA * -1), MAKELPARAM(cp.x, cp.y));
				jumped = true;
				c = 0;
			} else if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && player.in_air()) {
				//SendMessage(window, WM_KEYUP, VK_SPACE, 0x390000);
				/**
				 * SMAC Bypass
				 */
				if (jumped) {
					if (c < 6){
						Sleep(16);
						GetCursorPos(&cp);
						SendMessage(window, WM_MOUSEWHEEL, MAKEWPARAM(0, WHEEL_DELTA * -1), MAKELPARAM(cp.x, cp.y));
						/*SendMessage(window, WM_KEYDOWN, VK_SPACE, 0x390000);
						SendMessage(window, WM_KEYUP, VK_SPACE, 0x390000);*/
						++c;
						if (!bhop_natural) {
							jumped = false;
							c = 0;
						}
					} else {
						jumped = false;
						c = 0;
					}
				}
			} else {
				Sleep(1);
			}
		} else {
			Sleep(1);
		}
	}
}

void Bunnyhop::start() {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) bhop_tick, NULL, 0, NULL);
}

