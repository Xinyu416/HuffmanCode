#pragma once
#ifndef __MAP__
#define __MAP__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define SlotNum 10

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
	struct mapElement* next;//链表结构重复则指向下一个元素
}MapElement;

typedef struct map {
	struct mapElement** data;//元素数组 指向头指针
	//uint32_t slotNum;//槽数量 用于公式计算
	uint32_t mapLen;
	uint32_t valueSize;//元素值的字节大小
}Map;

Map CreateMap(uint32_t slotNum);

void ReleaseMap(Map* map);

void AddMapElement(Map* map, const char* skey, void* value);

bool RemoveMapElement(Map* map, const char* skey);

MapElement* FindMapElement(Map* map, const char* skey);

uint32_t* GetMapKeys(Map* map);

void* GetMapValues(Map* map);

uint32_t GetMapLength(Map* map);

/// <summary>
/// 通过数字key查找元素是否存在
/// </summary>
/// <param name="map"></param>
/// <param name="key"></param>
/// <returns></returns>
MapElement* __ContainsMapElement(Map* map, uint32_t key);

uint32_t GenerateMapIndex(Map* map, uint32_t key);

void PrintMap(Map* map);


#endif // !1