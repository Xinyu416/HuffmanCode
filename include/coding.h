#pragma once
#define _CRT_SECURE_NO_WARNINGS

#ifndef __CODING__
#define __CODING__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "linklist.h"
#include "bitoperate.h"

#define datasize 256
#define XXDATAMAX 536870911
#define APP_VERSION "v0.0.1"

typedef struct unit {
	uint32_t frequency;
	uint32_t childIndex;
	uint16_t data;
	struct unit* preview;
	struct unit* next;
	uint8_t type;				//0：叶节点，1：合并节点
}Unit;

typedef struct node {
	uint32_t frequcey;
	uint8_t data;				//节点数据值
	uint32_t childIndex;		//左子节点下标
	uint32_t parentIndex;		//父节点下标
	uint8_t type;				//0：叶节点，1：合并节点
}Node;

typedef struct code {
	uint32_t len;
	uint32_t code;
}Code;

/// <summary>
/// 自定义文件体数据信息
/// </summary>
struct DataHeader {
	uint16_t nodesNum;
	uint32_t byteCount;
	uint16_t block[1];
};

struct FileHeader {
	uint16_t type;
	uint32_t compressSize;
	uint32_t originSize;
	char ext[16];
};

void GenerateCode(Node* nodes, Node* node, uint32_t bit, Code* codes, Code c, uint32_t indent);

void PrintTree(Node* nodes, Node* node, uint32_t indent);

struct bitArray Coding(const uint8_t* content, uint32_t len);

void _DecodeContentData_Context(Node* inNodes, uint16_t nodesNum, struct bitArray* bitArr, uint32_t inOffset, uint32_t inContentBitLens, uint8_t* outData);

uint8_t* Decoding(struct bitArray* bitArr);

#endif 