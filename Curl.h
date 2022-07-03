#pragma once
#pragma comment(lib,"shell32.lib")
#include <Windows.h>

class Curl {
public:
	static void recieveBeforeMatch() {
		ShellExecute(NULL, "open", "cmd.exe", "/c before.bat", "", SW_HIDE);
	}

	static void recieveMatchState() {
		ShellExecute(NULL, "open", "cmd.exe", "/c recieve.bat", "", SW_HIDE);
	}

	static void sendAction() {
		ShellExecute(NULL, "open", "cmd.exe", "/c send.bat", "", SW_HIDE);
	}
};
