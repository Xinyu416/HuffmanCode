#include "codec.h"
#include "bitoperate.h"
#include "coding.h"
#include "containers.h"
#include "fileRead.h"
#include "linklist.h"
#include "map.h"

__declspec(dllexport) void Compress(const char* outPath) {
	doCompress(outPath);
}

__declspec(dllexport) void UnCompress(const char* outPath) {
	doDeCompress(outPath);
}