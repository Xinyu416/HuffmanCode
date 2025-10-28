#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef __LINKLIST__
#define __LINKLIST__

struct ListUnit {
	struct ListUnit* preview;
	struct ListUnit* next;
	uint32_t id;
	uint32_t count;
	uint8_t data;
	uint8_t type; //0 叶子节点, 1 合并节点
	uint8_t block[6];
};


struct LinkList {
	struct ListUnit* units;
	struct ListUnit* firstunit;
	struct ListUnit* endunit;
	uint32_t maxSize;//最大容量
	uint32_t len;//当前数据量
	uint32_t idmax;
	uint8_t block[4];
};

/*创建List块*/
struct LinkList CreateList(const uint32_t maxsize);

/*创建新链表元素*/
struct ListUnit* CreateListUnit(struct LinkList* list, uint32_t count, uint8_t data, uint8_t type);

/*移除元素*/
void RemoveListUnit(struct LinkList* list, struct ListUnit* unit);

/*元素插入到头*/
void InsertListUnitToHead(struct LinkList* list, struct ListUnit* unit);

/*元素插入到尾*/
void InsertListUnitToEnd(struct LinkList* list, struct ListUnit* unit);

/*在target元素之前插入新元素*/
void InsertListUnitPreview(struct LinkList* list,struct ListUnit* target, struct ListUnit* unit);

/*在target元素之后插入新元素*/
void InsertListUnitNext(struct LinkList* list, struct ListUnit* target, struct ListUnit* unit);

/*是第一个元素*/
bool IsFirstListUnit(struct ListUnit* unit);

/*是最后一个元素*/
bool IsLastListUnit(struct ListUnit* unit);

void MultiPrintList(struct LinkList* list);

void test();



#endif // __LINKLIST__

