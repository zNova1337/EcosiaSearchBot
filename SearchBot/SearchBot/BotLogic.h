#pragma once
#include "MouseHandler.h"
#include "KeyHandler.h"

void CreateNewTab() {
	vK->PressCombine({ VK_CONTROL,'T' });
}

void Enter() {
	vK->PressOnce(VK_RETURN);
}

void CloseTab() {
	vK->PressCombine({ VK_CONTROL,'W' });
}

int counter = 0;
void RandomSearch() {
	counter++;
	vK->PressRandom();
	if (counter < 10) {
		RandomSearch();
	}
}
int searchcount = 0;

bool activate = false;
void Bot() {
	pWindow = new WindowMgr();
	pWindow->Add();
	while (true) {
		if (!ApplicationMgr::ChromeOpen()) { activate = false; }
		if (vK->KeyPressed(VK_F10, 1000) && pWindow->isReady() && ApplicationMgr::ChromeOpen()) { activate = !activate; }
		if (activate) {
			CreateNewTab();
			std::this_thread::sleep_for(std::chrono::milliseconds(oDelay.newtabdelay));
			RandomSearch();
			std::this_thread::sleep_for(std::chrono::milliseconds(oDelay.randomsearchdelay));
			Enter();
			std::this_thread::sleep_for(std::chrono::milliseconds(oDelay.enterdelay));
			CloseTab();
			counter = 0;
			std::this_thread::sleep_for(std::chrono::milliseconds(oDelay.closetabdelay));
			searchcount++;
		}
	}
}