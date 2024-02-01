#pragma once

#include <windows.h>
#include <windowsx.h>

#undef max
#undef min

#pragma comment(lib, "legacy_stdio_definitions.lib") // cuz unresolved external symbol _vsprintf in glaux.lib
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "Glu32.lib")
#pragma comment(lib, "glaux.lib")

#include <stdint.h>
#include <iostream>
#include <stdio.h>

template<class T> inline T myAbs(const T& v) { return v < 0 ? -v : v; }
template<class T> inline T myMin(const T& a, const T& b) { return a <= b ? a : b; }
template<class T> inline T myMax(const T& a, const T& b) { return a <= b ? b : a; }
