#pragma once
#include "Functions.h"

DWORD WINAPI Listener(LPVOID v1) {
    while (true) {
        for (size_t i = 0; i < rng.size(); i++) {
            auto c = rng.at(i);
            if (GetAsyncKeyState(c.code)) {
                Logger.push_back(VirtualKey(c.code, "Pressed Key : " + c.name));
            }
        }
        Sleep(20);
    }
    return 0;
}

class KeyEvent {
public:
    KeyEvent() {
        auto it = VK.begin();
        while (it != VK.end()) {
            rng.push_back(VirtualKey(it->first, it->second));
            it++;
        }
    }

    struct m_pKey
    {
        bool Press;
        DWORD StartTime;
    }m_Key[256];

    bool KeyPressed(int vKey) {
        return (GetAsyncKeyState(vKey) && 0x80);
    }

    bool KeyPressed(int Key, DWORD Delay)
    {
        if (KeyPressed(Key))
        {
            if (!m_Key[Key].Press || (m_Key[Key].StartTime && (m_Key[Key].StartTime + Delay) <= GetTickCount()))
            {
                m_Key[Key].Press = true;
                if (Delay > 0)m_Key[Key].StartTime = GetTickCount();
                return true;
            }
        }
        else m_Key[Key].Press = false;
        return false;
    }

    void PressOnce(int vKey) {
        keybd_event(vKey, 0, 0, 0);//Key down
        keybd_event(vKey, 0, KEYEVENTF_KEYUP, 0);//Release the key
    }

    void PressCombine(std::vector<int>vKey) {
        for (size_t i = 0; i < vKey.size(); i++) {
            keybd_event(vKey.at(i), 0, 0, 0);
        }
        for (size_t i = 0; i < vKey.size(); i++) {
            keybd_event(vKey.at(i), 0, KEYEVENTF_KEYUP, 0);
        }
        vKey.clear();
    }

    void listen() {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Listener, 0, 0, 0);
    }

    void PressRandom() {
        auto res = rand(rng.front().code, rng.back().code);
        auto name = VK.find(res);
        if (name != VK.end()) {
            PressOnce(name->first);
        }
    }
}; KeyEvent* vK = nullptr;