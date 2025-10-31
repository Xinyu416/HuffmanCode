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
	struct mapElement* next;//指向下一个链表元素
}MapElement;

typedef struct map {
	struct mapElement** data;//元素数组 指向头指针
	uint32_t mapLen;
	uint32_t valueSize;//元素值的字节大小
}Map;

/// <summary>
/// 创建map
/// </summary>
/// <param name="valueSize">元素的字节数</param>
/// <returns></returns>
Map CreateMap(uint32_t valueSize);

/// <summary>
/// 释放数组
/// </summary>
/// <param name="map"></param>
void ReleaseMap(Map* map);

/// <summary>
/// 添加map元素
/// </summary>
/// <param name="map"></param>
/// <param name="skey">传入的元素skey</param>
/// <param name="value">传入的元素value</param>
void AddMapElement(Map* map, const char* skey, void* value);

/// <summary>
/// 移除map内元素
/// </summary>
/// <param name="map">传入的map</param>
/// <param name="skey">元素的skey</param>
/// <returns>是否移除成功</returns>
bool RemoveMapElement(Map* map, const char* skey);

/// <summary>
/// 通过skey寻找元素
/// </summary>
/// <param name="map"></param>
/// <param name="skey">传入的skey</param>
/// <returns>找到的元素指针</returns>
MapElement* FindMapElement(Map* map, const char* skey);

/// <summary>
/// 获取map的所有key
/// </summary>
/// <param name="map"></param>
/// <param name="mapKeys"></param>
/// <returns>key总数</returns>
uint32_t GetMapKeys(Map* map, uint32_t* mapKeys);

/// <summary>
/// 获取map所有values
/// </summary>
/// <param name="map"></param>
/// <param name="mapValues">外部传入接收的容器</param>
/// <returns>values所有个数</returns>
uint32_t GetMapValues(Map* map, void* mapValues);

/// <summary>
/// 获取map长度
/// </summary>
/// <param name="map"></param>
/// <returns></returns>
uint32_t GetMapLength(Map* map);

/// <summary>
/// 通过数字key查找元素是否存在
/// </summary>
/// <param name="map"></param>
/// <param name="key"></param>
/// <returns></returns>
MapElement* __ContainsMapElement(Map* map, uint32_t key);

/// <summary>
/// 通过数字key生成map槽的index
/// </summary>
/// <param name="map"></param>
/// <param name="key">skey转成的数字key</param>
/// <returns>map槽的index</returns>
uint32_t GenerateMapIndex(Map* map, uint32_t key);

void PrintMap(Map* map);

#endif // !1