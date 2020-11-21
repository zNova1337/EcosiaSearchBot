#pragma once
#include "Functions.h"

DWORD WINAPI tCheck(LPVOID lpreserved) {
    POINT point;
    while (true) {
        GetCursorPos(&point);
        mousecoord.x = (float)point.x;
        mousecoord.y = (float)point.y;
        Sleep(10);
    }
    return 0;
}

class Mouse {
public:
    Mouse() {}

    void MoveFirst() {
        Move(vector2(500, 420));
    }
    void Move(vector2 newcoord) {
        SetCursorPos((int)newcoord.x,(int) newcoord.y);
    }
    vector2 GetPos() {
        POINT p;
        GetCursorPos(&p);
        return vector2((float)p.x, (float)p.y);
    }

    void Move(int vKey, vector2 newcoord) {
        static bool switcher = false;
        if (GetAsyncKeyState(vKey) && 0x80)switcher = !switcher;
        if (switcher) {
            Move(newcoord);
        }
    }

    void CurrentMouse() {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)tCheck, 0, 0, 0);//To debug the x and y coordinate of the mouse
    }
}; Mouse* vM = nullptr;
