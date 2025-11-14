#include "codec.h"

#include "pch.h"

__declspec(dllexport) void Compress(const char* outPath) {
	doCompress(outPath);
}

__declspec(dllexport) void UnCompress(const char* outPath) {
	doDeCompress(outPath);
}