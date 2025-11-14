#pragma once
#include "bitoperate.h"
#include "coding.h"
#include "containers.h"
#include "fileRead.h"
#include "linklist.h"
#include "map.h"

#ifdef CODECDLL_EXPORTS
#define CODEC_API __declspec(dllexport)
#else
#define CODEC_API __declspec(dllimport)
#endif


CODEC_API void Compress(const char*outPath);

CODEC_API void UnCompress(const char*outPath);