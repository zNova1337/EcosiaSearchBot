#pragma once
#include "Includes.h"

int rand(int min, int max) {
  return rand() % (max - min + 1) + min;
}

template <typename T>
std::string GetVect(std::vector<T> vect) {
    std::stringstream ss;
    for (size_t i = 0; i < vect.size(); i++) {
        ss << vect.at(i).name << std::endl;
    }
    return ss.str();
}

struct windowp
{
	windowp(HWND in, std::string v1, std::string v2) : hwnd(in), windowname(v1), classname(v2) {}
	HWND hwnd;
	std::string windowname;
	std::string classname;
};

class WindowMgr {
private:
	std::vector<windowp> window;
	static BOOL CALLBACK enumWindowCallback(HWND hWnd, LPARAM lparam) {
		auto Me = reinterpret_cast<WindowMgr*>(lparam);
		char classbuff[MAX_PATH];
		int length = GetWindowTextLength(hWnd);
		char* buffer = new char[length + 1];
		GetWindowText(hWnd, buffer, length + 1);
		GetClassName(hWnd, classbuff, sizeof(classbuff));
		std::string windowTitle(buffer);

		if (IsWindowVisible(hWnd) && length != 0) {
			Me->window.push_back(windowp(hWnd, buffer, classbuff));
		}
		delete[] buffer;
		return TRUE;
	}
public:
	WindowMgr() {}
	void Add() { EnumWindows(enumWindowCallback, reinterpret_cast<LPARAM>(this)); }
	std::vector<windowp>& get() { return window; }
	bool isChromeOpen(HWND& out) {
		for (size_t i = 0; i < window.size(); i++) {
			auto obj = window.at(i);
			auto v1 = obj.classname.find("Chrome");
			auto v2 = obj.windowname.find("Google Chrome");
			bool isChrome = (v1 != std::string::npos);
			bool isGoogleChrome = (v2 != std::string::npos);
			if(isGoogleChrome && isChrome){
				out = window.at(i).hwnd;
				return true;
			}
			
		}return false;
	}
	void Clear() { window.clear(); }
	bool isReady() {
		HWND hwnd = 0;
		bool ab = isChromeOpen(hwnd);
		return (hwnd == GetForegroundWindow() && GetForegroundWindow() != 0);
	}

}; WindowMgr* pWindow = nullptr;

namespace ApplicationMgr {
	uintptr_t GetPID(std::string name)
	{
		uintptr_t tmpPID = 0;
		HANDLE Snapshot = CreateToolhelp32Snapshot(PROCESS_ALL_ACCESS, 0);
		tagPROCESSENTRY32 processentry;
		if (Process32First(Snapshot, &processentry)) {
			do
			{
				if (strcmp(processentry.szExeFile, name.c_str()) == 0) {
					tmpPID = processentry.th32ProcessID;
					break;
				}
			} while (Process32Next(Snapshot, &processentry));
		}
		return tmpPID;
	}

	uintptr_t GetPID(const char* windowname, const char* classname) {
		DWORD tmpPID = 0;
		HWND hWnd = FindWindowA(classname, windowname);
		GetWindowThreadProcessId(hWnd, &tmpPID);
		return tmpPID;
	}

	bool ChromeOpen() {
		return GetPID("chrome.exe") != 0;
	}
};

class Timer {
public:
	int seconds;
	int minutes;
	int hours;
	static DWORD WINAPI Tick(LPVOID param) {
		auto ptr = reinterpret_cast<Timer*>(param);
		while (true) {
			ptr->seconds++;
			if (ptr->seconds == 60) {
				ptr->minutes++;
				if (ptr->minutes == 60) {
					ptr->hours++;
					ptr->minutes = 0;
				}
				ptr->seconds = 0;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		return 0;
	}
	void Start() {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Tick, reinterpret_cast<LPVOID>(this), 0, 0);
	}
}timer;

struct DelayCtrl
{
	int newtabdelay = 50;
	int randomsearchdelay = 100;
	int enterdelay = 1000;
	int closetabdelay = 0;
}oDelay;