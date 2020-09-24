#include "debug.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

void DebugOut(const wchar_t *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];	
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}