#include "main.h"
#include <cstdio>
using namespace Main;

/*
 FL_IN_AIR_STAND                    256
 FL_ON_GROUND                     257
 FL_IN_AIR_MOVING_TO_STAND         258
 FL_ON_GROUND_MOVING_TO_STAND     259
 FL_IN_AIR_MOVING_TO_CROUCH         260
 FL_ON_GROUND_MOVING_TO_CROUCH     261
 FL_IN_AIR_CROUCHED                 262
 FL_ON_GROUND_CROUCHED             263
 FL_IN_WATER                     1280
 FL_IN_PUDDLE                     1281
 FL_IN_WATER_CROUCHED             1286
 FL_IN_PUDDLE_CROUCHED             1287
 */

int p_base;
int flag;

void read_memory() {
	while (true) {
		if (auto_lj_enabled || auto_sw_lj_enabled || bhop_enabled || strafe_hack_enabled) {
			ReadProcessMemory(process, (LPVOID) (module_base + player_base), &p_base, sizeof(int), NULL);
			ReadProcessMemory(process, (LPVOID) (p_base + mflags), &flag, sizeof(int), NULL);
			ReadProcessMemory(process, (LPVOID)(module_base + jump_base), &player.jflag, sizeof(int), NULL);
			//printf("%d", player.jflag);
			/*ReadProcessMemory(process, (LPVOID)(module_base + jump_base_tf2), &jflag, sizeof(char), NULL);*/

			if (player.jflag != 1) {
				if (GetKeyState(VK_XBUTTON1) & 0x8000) {
					Main::inair_override = 1;
				}
			}
			if (GetKeyState(VK_SPACE) & 0x8000) {
				Main::inair_override = 0;
			}
			Sleep(1);
		} else {
			Sleep(1);
		}
	}
}

void Player::start() {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) read_memory, NULL, 0, NULL);
}

bool Player::in_air() {
	if (Main::inair_override)
		return false;
	return player.jflag != 1;
	/*return jflag == -1;*/
}

