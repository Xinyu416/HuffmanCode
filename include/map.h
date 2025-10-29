#pragma once
#ifndef __MAP__
#define __MAP__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>


/// <summary>
/// 字符串转数字
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
inline uint32_t BKDRHash(const char* str)
{
	uint32_t hash = 0;
	uint32_t seed = 31;
	for (int i = 0; str[i]; i++)
	{
		hash = hash * seed + str[i];
	}
	return hash & 0x7FFFFFFF;
}


typedef struct mapElement {
	uint32_t key;
	uint8_t* value;//值
	uint8_t* next;//链表结构重复则指向下一个元素
}MapElement;

typedef struct map {
	uint32_t key;
	uint8_t** data;
	uint32_t slotNum;//槽数量 用于公式计算
}Map;

Map CreateMap(uint32_t slotNum);

void ReleaseMap(Map* map);

uint32_t GenerateK(Map* map, const char* str);

void PrintMap(Map* map);

void MapTest();

#endif // !1