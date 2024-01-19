#pragma once
#include <iostream>
#include <ctime>
#include<Windows.h>
#include "resource.h"
#pragma comment(lib,"winmm.lib")
#define Amthanh(fileName) (PlaySound(MAKEINTRESOURCE(fileName), GetModuleHandle(NULL),SND_RESOURCE|SND_ASYNC));
#define phimQ 0x51
#define phimW 0x57
#define ConsoleWidth 120
#define ConsoleHeight 35

struct CauTrucBang {
	short Dong = 0;
	short Cot = 0;
	short SoBom = 0;
	short SoODaMo = 0;
	short SoCoDaMo = 0;
};
struct CauTrucO {
	short BCoBom = 0;
	short BDaMo = 0;
	short BCamCo = 0;
	short SoBomLanCan = 0;
};
