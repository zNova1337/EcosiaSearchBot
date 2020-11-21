#pragma once
#include <stdint.h>
#include <sstream>
#include <time.h>
#include <vector>
#include <map>
#include <string>
#include <Windows.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <TlHelp32.h>
#include <chrono>
#include <thread>
struct vector2 {
    vector2() : x(0), y(0) {}
    vector2(float inx, float iny) : x(inx), y(iny) {}
    float x;
    float y;
};

vector2 mousecoord;
class VirtualKey {
public:
    VirtualKey(int xcode, std::string xname) : code(xcode), name(xname) {}
    VirtualKey() {}
    int code;
    std::string name;
    bool equals(VirtualKey v1) {
        auto curObj = this;
        return (v1.code == curObj->code && v1.name == curObj->name);
    }
};
VirtualKey oVirtualKey;
std::vector<VirtualKey> rng;
std::vector<VirtualKey> Logger;

std::map<int, std::string> VK =
{
   // {0x1,"L-CLICK"},
   // {0x2,"R-CLICK"},
   /* {0x3,"CANCEL"},
    {0x4,"MBUTTON"},
    {0x5,"XBUTTON1"},
    {0x6,"XBUTTON2"},
    {0x7,"Undefined"},
    {0x8,"BACKSPACE"},
    {0x9,"TAB"},
    {0xA,"RESERVED"},
    {0xB,"RESERVED2"},
    {0xC,"CLEAR"},*/
    //{0xD, "ENTER"},
    //{0x10,"SHIFT"},
    //{0x11,"CONTROL"},
    //{0x12,"MENU"},
    {0x30, "ZERO"},
    {0x31, "ONE"},
    {0x32, "TWO"},
    { 0x33, "THREE"},
    { 0x34, "FOUR"},
    { 0x35, "FIVE"},
    { 0x36, "SIX"},
    { 0x37, "SEVEN"},
    { 0x38, "EIGHT"},
    { 0x39, "NINE"},
    { 0x41, "A"},
    { 0x42, "B"},
    { 0x43, "C" },
    { 0x44, "D" },
    { 0x45, "E" },
    { 0x46, "F" },
    { 0x47, "G" },
    { 0x48, "H" },
    { 0x49 , "I" },
    { 0x4A, "J" },
    { 0x4B , "K" },
    { 0x4C, "L" },
    { 0x4D, "M" },
    { 0x4E, "N" },
    { 0x4F, "O" },
    { 0x50, "P" },
    { 0x51, "Q" },
    { 0x52, "R" },
    { 0x53, "S" },
    { 0x54, "T" },
    { 0x55, "U" },
    { 0x56, "V" },
    { 0x57, "W" },
    { 0x58, "X" },
    { 0x59, "Y" },
    { 0x5A, "Z" }
};

