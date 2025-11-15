#pragma once

#ifdef __cplusplus
#define DLLTEST_API extern "C" __declspec(dllimport)
#else
#ifdef CODECDLL_EXPORTS
#define CODEC_API __declspec(dllexport)
#else
#define CODEC_API __declspec(dllimport)
#endif
#endif

CODEC_API void Compress(const char* outPath);

CODEC_API void UnCompress(const char* outPath);