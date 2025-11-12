#pragma once
#ifndef __FILEREAD__
#define __FILEREAD__
#include "../include/bitoperate.h"

/*制作一个类似WINRAR软件功能*/


/*
* 拆分文件路径，使用者提供输出内容的储存空间，一般遵循_PATH_MAX大小，如果空间不足行为未定义
* @param path 完整文件名称
* @param outExt 扩展名
* @param outName 文件短名称，不包含扩展名
* @param outDir 文件所在目录的路径名，不包含文件名本身
* @param outFilename 文件名称，包括短名称+扩展名
*/
void pathComponents(const char* path, char* outExt, char* outName, char* outDir, char* outFilename);

/*入口*/
void FileReadTest();

void doCompress(const char* outPath);

void doDeCompress(const char* outPath);

#endif