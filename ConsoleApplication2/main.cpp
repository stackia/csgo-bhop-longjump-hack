#include "main.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace Main;
using namespace std;

DWORD Main::player_base = 0x53BFC8;
DWORD Main::mflags = 0x34C;
DWORD Main::jump_base = 0xA7814C;
DWORD Main::jump_base_tf2 = 0xC5C94C;
Player Main::player;
Longjump Main::longjump;
Bunnyhop Main::bhop;
Util Main::util;
HWND Main::window;
DWORD Main::pid;
DWORD Main::module_base;
HANDLE Main::process;
bool Main::auto_lj_enabled;
bool Main::auto_sw_lj_enabled;
bool Main::strafe_hack_enabled;
POINT Main::center;
POINT Main::cursor_pos;
bool Main::bhop_enabled;
bool Main::legit_bhop_enabled;

struct Config {
	int width;
	int height;
};

bool load_config(Config& cfg) {
	ifstream fin("kihop.cfg");
	if (fin.good()) {
		string line;
		while (getline(fin, line)) {
			istringstream sin(line);
			string key;
			if (getline(sin, key, '=')) {
				if (key == "width") {
					sin >> cfg.width;
				} else if (key == "height") {
					sin >> cfg.height;
				}
			}
		}
		fin.close();
		return true;
	} else {
		printf("Enter your in-game resolution width: ");
		cin >> cfg.width;
		printf("Enter your in-game resolution height: ");
		cin >> cfg.height;
		ofstream fout("kihop.cfg");
		if (fout.is_open()) {
			fout << "width=" << cfg.width << "\n";
			fout << "height=" << cfg.height << "\n";
			fout.close();
			return true;
		} else {
			printf("Unabled to create config file.\n");
			return false;
		}
	}
}

int main() {
	Config config;
	load_config(config);
	const wchar_t* processname = L"Counter-Strike: Global Offensive";
	/*const wchar_t* processname = L"Team Fortress 2";*/
	printf("Waiting for %ls.\n", processname);
	window = FindWindow(NULL, processname);
	while (window == NULL) {
		Sleep(1000);
		window = FindWindow(NULL, processname);
	}
	printf("%ls was found.\n", processname);
	GetWindowThreadProcessId(window, &pid);
	process = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
	module_base = util.get_module_base_extern(pid, L"client.dll");
	player.start();
	longjump.start();
	bhop.start();
	while (true) {
		if (GetAsyncKeyState(VK_NUMPAD0)) {
			auto_lj_enabled = false;
			auto_sw_lj_enabled = false;
			bhop_enabled = false;
			legit_bhop_enabled = false;
			strafe_hack_enabled = false;
		} else if (GetAsyncKeyState(VK_NUMPAD1)) {
			auto_lj_enabled = true;
			auto_sw_lj_enabled = false;
		} else if (GetAsyncKeyState(VK_NUMPAD2)) {
			auto_sw_lj_enabled = true;
			auto_lj_enabled = false;
		} else if (GetAsyncKeyState(VK_NUMPAD3)) {
			bhop_enabled = true;
		} else if (GetAsyncKeyState(VK_NUMPAD4)) {
			bhop_enabled = true;
			legit_bhop_enabled = true;
		} else if (GetAsyncKeyState(VK_NUMPAD5)) {
			center.x = config.width / 2;
			center.y = config.height / 2;
			auto_lj_enabled = false;
			auto_sw_lj_enabled = false;
			strafe_hack_enabled = true;
		} else {
			Sleep(1);
		}
	}
	return 0;
}
