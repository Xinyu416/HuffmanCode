//#pragma once
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <stdint.h>
//#include <stdbool.h>
//
////#define datasize 255
////
////typedef struct unit {
////	uint8_t frequency;
////	uint8_t childIndex;
////	uint8_t data;
////	struct unit* preview;
////	struct unit* next;
////	uint8_t type;		//0：叶节点，1：合并节点
////}Unit;
////
////typedef struct node {
////	uint8_t frequcey;
////	uint8_t data;			//节点数据值
////	uint8_t childIndex;		//左子节点下标
////	uint8_t parentIndex;	//父节点下标
////	uint8_t type;			//0：叶节点，1：合并节点
////}Node;
////
////typedef struct code {
////	uint8_t len;
////	uint32_t code;
////}Code;
//
///*判断是否为最后一个元素*/
//bool IsLastUnit(Unit* u);
//
///*判断是否为第一个元素*/
//bool IsFirstUnit(Unit* u);
//
///*创建新链表元素*/
//Unit* CreateUnit(Unit* units, uint8_t len,uint8_t frequecy,uint8_t data,uint8_t type);
//
///*将current元素插入在target之前*/
//void InsertUnitPreview(Unit* current, Unit* target);
//
///*将current元素插入在target之后*/
//void InsertUnitNext(Unit* current, Unit* target);
//
///*元素排序*/
//void UnitSort(Unit* u, uint8_t data[]);
//
///*元素移除 斩断链接*/
//void RemoveUnit(Unit* unit);
//
///*元素置空*/
//void ResetUnit(Unit* unit);
//
///*从数组中获取空闲元素*/
//uint8_t GetEmptyUnit(Unit* units);
//
///*元素摘到Node树结构中*/
//void GetUnitPushToNode(Unit* unit, Node* node);
//
///*元素打印*/
//void PrintList(Unit* head);